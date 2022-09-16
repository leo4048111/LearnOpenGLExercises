#pragma once
#include <GLFW/glfw3.h>

#include <memory>

#include "Controller.h"

class Menu
{
public:
	Menu(GLFWwindow* window, Controller* controller);
	~Menu() = default;

	void mainloop();

	void render();

private:
	GLFWwindow* _window{ nullptr };
	std::unique_ptr<Controller> _controller;

};