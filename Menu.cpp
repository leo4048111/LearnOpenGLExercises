#include "Menu.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Menu::Menu(GLFWwindow* window, Controller* controller):
	_controller(controller), _window(window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(nullptr);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
}

void Menu::mainloop()
{
	return;
}

void Menu::render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize({ 300, 300 });
	ImGui::Begin("Menu");

	float sensitivity = _controller->getMouseSensitivity();
	float camSpeed = _controller->getCameraSpeed();
	ImGui::SliderFloat("Sensitivity", &sensitivity, 0.1f, 1.0f, "%.1lf");
	ImGui::SliderFloat("Camera Speed", &camSpeed, 0.1f, 1.0f, "%.1lf");
	_controller->setCameraSpeed(camSpeed);
	_controller->setMouseSensitivity(sensitivity);

	ImGui::End();

	int display_w, display_h;
	glfwGetFramebufferSize(_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


