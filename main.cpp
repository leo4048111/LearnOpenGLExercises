#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Windows.h>
#include <memory>

#include "Dependencies/stb_image/stb_image.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include "Shader.hpp"
#include "Camera.h"
#include "Menu.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float pitch = 0, yaw = 0;

int main()
{
	if (!glfwInit())
	{
		return 0;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);

	if (window == nullptr)
	{
		glfwTerminate();
		return 0;
	}

	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	auto controller = std::make_unique<Controller>(window);
	auto menu = std::make_unique<Menu>(window, controller.get());

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return 0;
	}

	float triangle1[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
		 //0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 //0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
		 //0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	//float triangle1[] = {
	//-0.5f, -0.5f,
	// 0.5f, -0.5f, 
	// 0.0f,  0.5f
	// //0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	// //0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
	// //0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	//};

	unsigned int va[2];
	glGenVertexArrays(2, &va[0]);
	glBindVertexArray(va[0]);

	unsigned int buffer[2];
	glGenBuffers(2, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float) * 5, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

	unsigned int ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBindVertexArray(va[1]);
	//unsigned int buffer2;
	//glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &triangle1[6], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glBindVertexArray(0);

	Shader shader("res/shaders/Basic.glsl");
	shader.bind();

	unsigned int texture[2];
	glGenTextures(2, &texture[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, channels;
	const unsigned char* data = stbi_load("res/textures/awesomeface.png", &width, &height, &channels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texture[0]);
	stbi_image_free((void*)data);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	data = stbi_load("res/textures/wall.jpg", &width, &height, &channels, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texture[1]);
	stbi_image_free((void*)data);

	shader.setUniform1i("u_texture1", 0);
	shader.setUniform1i("u_texture2", 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float visibility = 1.0;

	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.bind();

		glBindVertexArray(va[0]);

		//glBindVertexArray(va[1]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		if (GetAsyncKeyState(VK_UP) & 0x01) visibility += 0.1;

		if (GetAsyncKeyState(VK_DOWN) & 0x01) visibility -= 0.1;
		if (visibility >= 1.0f || visibility <= 0.0f) visibility = 1.0f;
		shader.setUniform1f("u_visibility", visibility);
		glm::mat4 trans(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setUniformMatrix4fv("u_transform", trans);

		static float offsetX = 0.f, offsetY = 0.f;

		if (GetAsyncKeyState(VK_NUMPAD8) & 0x01) offsetY += 0.1;

		if (GetAsyncKeyState(VK_NUMPAD2) & 0x01) offsetY -= 0.1;

		if (GetAsyncKeyState(VK_NUMPAD4) & 0x01) offsetX -= 0.1;

		if (GetAsyncKeyState(VK_NUMPAD6) & 0x01) offsetX += 0.1;

		controller->keyboardHandler(window);

		glm::mat4 view = controller->getCamera().getViewMatrix();

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);

		shader.setUniformMatrix4fv("u_view", view);
		shader.setUniformMatrix4fv("u_projection", projection);
		for (unsigned int j = 1; j <= 50; j++)
		{
			for (unsigned int i = 1; i <= 50; i++)
			{
				glm::mat4 model(1.0f);
				model = glm::translate(model, cubePositions[0]);
				float angle = 20.0f * i;
				//model = glm::rotate(model, glm::radians(angle) *(float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
				model = glm::translate(model, glm::vec3(1.0f * i, 0.0f, 1.0f * j));
				shader.setUniformMatrix4fv("u_model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		//render menu at last to make sure it stays on topmost
		menu->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

}