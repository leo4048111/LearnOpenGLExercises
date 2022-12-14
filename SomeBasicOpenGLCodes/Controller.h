#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "glm/glm.hpp"

#include "Camera.h"

class Controller
{
public:
	Controller(GLFWwindow* window);
	~Controller() = default;
	void keyboardHandler(GLFWwindow* window);
	void mouseHandler(GLFWwindow* window, double xpos, double ypos);

private:
	void registerMouseCallback(GLFWwindow* window);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

public:
	const Camera& getCamera() const { return *_camera; };

	const double getMouseSensitivity() const { return _mouseSensitivity; };
	const double getCameraSpeed() const { return _cameraSpeed; };

	void setMouseSensitivity(double ms) { _mouseSensitivity = ms; };
	void setCameraSpeed(double cs) { _cameraSpeed = cs; };

private:
	double _mouseSensitivity{0.25f};
	double _cameraSpeed{ 2.5f };
	std::unique_ptr<Camera> _camera;

	glm::vec3 _cameraOrigin;

	bool isCursorHidden{ true };
};

