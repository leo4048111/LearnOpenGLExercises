#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

int main()
{
	const unsigned int wWidth = 980, wHeight = 560;
	//initialization
	if (!glfwInit())
	{
		return 0;
	}

	GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "Assignment1", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return 0;
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(nullptr);
	ImGui::StyleColorsDark();
	ImGui::GetIO().WantSaveIniSettings = false;

	//vertices
	float vertices[] = {
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
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
	VertexBuffer vb(6 * sizeof(float) * 8, vertices);
	vb.bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));

	IndexBuffer ib(36, indices);
	ib.bind();

	Shader shader("src/shaders/Basic.glsl");
	shader.use();

	glEnable(GL_DEPTH_TEST);

	//mainloop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//menu
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowSize({ 500, 200 });
		ImGui::Begin("Menu");
		static int projType;
		ImGui::RadioButton("Perspective", &projType, 0); ImGui::SameLine();
		ImGui::RadioButton("Ortho", &projType, 1);
		static bool isAutoRotate = false;
		ImGui::Checkbox("Auto rotate", &isAutoRotate); ImGui::SameLine();
		static bool isNeonLight = false;
		ImGui::Checkbox("Neon light mode", &isNeonLight);
		static float modelOffsets[3] = { 0.0f, 0.0f, 0.296f };
		ImGui::SliderFloat3("Model offsets", modelOffsets, -10.f, 10.f);
		static float viewOffsets[3] = { 0.225f, 0.0f, -3.f };
		ImGui::SliderFloat3("View offsets", viewOffsets, -10.f, 10.f);
		static float viewAngles[3] = { 34.383f, -32.360f, 0.0f };
		ImGui::SliderFloat3("View angles", viewAngles, -90.f, 90.f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(modelOffsets[0], modelOffsets[1], modelOffsets[2]));
		if(isAutoRotate)
			model = glm::rotate(model, (float)glfwGetTime() * (float)glm::radians(45.f), glm::vec3(0.3f, 1.0f, 0.8f));

		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(viewOffsets[0], viewOffsets[1], viewOffsets[2]));
		view = glm::rotate(view, glm::radians(viewAngles[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, glm::radians(viewAngles[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(viewAngles[2]), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 projection(1.0f);
		if (projType == 0)
			projection = glm::perspective(glm::radians(45.f), (float)wWidth / (float)wHeight, 0.1f, 100.f);
		else
			projection = glm::ortho(-1.f, 1.0f, -1.f, 1.f, -1.f, 1.f);

		glm::mat4 mvp = projection * view * model;
		shader.setUniformMat4f("u_mvp", mvp);

		glm::mat4 colorModelTransform(1.0f);

		if (isNeonLight) {
			colorModelTransform = glm::rotate(colorModelTransform, (float)glfwGetTime() * (float)glm::radians(90.f), glm::vec3(1.0f, 1.0f, 1.0f));
		}

		shader.setUniformMat4f("u_colorModelTransform", colorModelTransform);

		//gl draw calls
		glBindVertexArray(va);
		glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}