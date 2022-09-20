#include <GL/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

#include "stb_image/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Camera.h"

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera camera(glm::vec3(0.0f, 0.0f, -5.f));

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static float sensitivity = 0.2f;
	static float lastX = 320.f, lastY = 240.f;
	float offsetX = xpos - lastX, offsetY = ypos - lastY;
	static bool firstMouse = true;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	lastX = xpos, lastY = ypos;
	float pitch = camera.getPitch();
	float yaw = camera.getYaw();
	pitch -= offsetY * sensitivity;
	yaw += offsetX * sensitivity;
	if (pitch > 89.f)
		pitch = 89.f;
	if (pitch < -89.f)
		pitch = -89.f;

	camera.setPitch(pitch);
	camera.setYaw(yaw);
}

void keyboard_handler(GLFWwindow* window)
{
	static float deltaTime = 0.0f;
	static float lastFrame = 0.0f;
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;

	auto cameraPos = camera.getPosition();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += camera.getDirection() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= camera.getDirection() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += camera.getRight() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= camera.getRight() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += camera.getUp() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraPos -= camera.getUp() * cameraSpeed;

	camera.setPosition(cameraPos);
}

static GLFWwindow* initialization()
{
	if (!glfwInit())
	{
		return 0;
	}

	GLFWwindow* window = glfwCreateWindow(920, 560, "Hello world", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return 0;
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

int main()
{
	GLFWwindow* window = initialization();

	if (!window) return 0;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 0, 3,
		1, 5, 2,
		2, 5, 6,
		4, 5, 6,
		4, 6, 7,
		0, 4, 7,
		0, 7, 3,
		2, 3, 6,
		3, 6, 7,
		0, 1, 4,
		4, 1, 5
	};

	unsigned int va;
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	unsigned int vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, 6 * 36 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));

	//unsigned int ib;
	//glGenBuffers(1, &ib);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	Shader shader("res/shaders/Basic.glsl");
	shader.bind();

	//unsigned int lightVa;
	//glGenVertexArrays(1, &lightVa);
	//glBindVertexArray(lightVa);

	//unsigned int lightVb;
	//glGenBuffers(1, &lightVb);
	//glBindBuffer(GL_ARRAY_BUFFER, lightVb);
	//glBufferData(GL_ARRAY_BUFFER, 3 * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

	//unsigned int lightIb;
	//glGenBuffers(1, &lightIb);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightIb);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBindVertexArray(0);

	Shader lightShader("res/shaders/Light.glsl");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		keyboard_handler(window);

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(-45.f) * (float)glfwGetTime(), glm::vec3(-1.0f, 1.0f, 0.25f));
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.f), 920.f / 560.f, 0.1f, 100.f);

		shader.bind();
		shader.setUniformMatrix4fv("u_model", model);
		shader.setUniformMatrix4fv("u_view", view);
		shader.setUniformMatrix4fv("u_projection", projection);
		shader.setUniform4f("u_objectColor", 1.0f, 0.5f, 0.31f, 1.0f);
		shader.setUniform4f("u_lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
		shader.setUniform3f("u_lightPos", lightPos.x, lightPos.y, lightPos.z);
		shader.setUniform3f("u_viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		shader.setUniform3f("u_material.ambient", 1.0f, 0.5f, 0.31f);
		shader.setUniform3f("u_material.deffuse", 1.0f, 0.5f, 0.31f);
		shader.setUniform3f("u_material.specular", 0.5f, 0.5f, 0.5f);
		shader.setUniform1f("u_material.shininess", 32.0f);
		glBindVertexArray(va);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		int radius = (lightPos - glm::vec3(0.0, 0.0, 0.0)).length();
		static float angle = 0.0f;
		lightPos.x = radius * cos(glm::radians(angle));
		lightPos.z = radius * sin(glm::radians(angle));
		angle += 0.01f;

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		glm::mat4 mvp = projection * view * model;

		lightShader.bind();
		lightShader.setUniformMatrix4fv("u_mvp", mvp);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}