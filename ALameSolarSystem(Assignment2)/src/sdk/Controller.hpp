#pragma once

#include "def.hpp"
#include "Camera.hpp"

#include <thread>

class Controller
{
public:
	~Controller() = default;
	Controller(const Controller&) = delete;
	Controller& operator= (const Controller&) = delete;

private:
	Controller() = default;

private:
	Camera* _camera { nullptr };
	GLFWwindow* _window{ nullptr };

	float _mouseSensitivity{ 0.25f };
	float _cameraSpeed{ 25.f };

	std::unique_ptr<std::thread> _tController;
	bool isInstalled{ false };

public:
	static std::unique_ptr<Controller>& getInstance() {
		if (_inst.get() == nullptr) _inst.reset(new Controller);
		return _inst;
	};

	void install(GLFWwindow* window, Camera* camera);
	void uninstall();

	const float getMouseSensitivity() const { return _mouseSensitivity; };
	const float getCameraSpeed() const { return _cameraSpeed; };

	void setMouseSensitivity(float ms) { _mouseSensitivity = ms; };
	void setCameraSpeed(float cs) { _cameraSpeed = cs; };

private:
	static std::unique_ptr<Controller> _inst;

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	void mouseHandler(double xpos, double ypos);

	void keyboardHandler();

	inline void registerCallbacks();
};

std::unique_ptr<Controller> Controller::_inst;

void Controller::install(GLFWwindow* window, Camera* camera)
{
	_window = window;
	_camera = camera;
	if (!window) return;

	registerCallbacks();

	isInstalled = true;
}

void Controller::uninstall()
{
	isInstalled = false;
	_window = nullptr;
	_camera = nullptr;
}

inline void Controller::registerCallbacks()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(_window, Controller::mouseCallback);
	_tController = std::make_unique<std::thread>(&Controller::keyboardHandler, Controller::getInstance().get());
	_tController->detach();
}

void Controller::keyboardHandler()
{
	while (isInstalled)
	{
		static float deltaTime = 0.0f;
		static float lastFrame = 0.0f;
		float currentFrame = glfwGetTime();
		if (!lastFrame) lastFrame = currentFrame;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float cameraSpeed = _cameraSpeed * deltaTime;

		if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
			_camera->move(Camera::Direction::FORWARD, cameraSpeed);
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
			_camera->move(Camera::Direction::BACKWARD, cameraSpeed);
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
			_camera->move(Camera::Direction::RIGHT, cameraSpeed);
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
			_camera->move(Camera::Direction::LEFT, cameraSpeed);
		if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			_camera->move(Camera::Direction::UP, cameraSpeed);
		if (glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			_camera->move(Camera::Direction::DOWN, cameraSpeed);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Controller::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Controller::getInstance()->mouseHandler(xpos, ypos);
}

void Controller::mouseHandler(double xpos, double ypos)
{
	static double lastPosX = 0.0f;
	static double lastPosY = 0.0f;
	static bool isFirstEntry = true;

	if (isFirstEntry)
	{
		lastPosX = xpos;
		lastPosY = ypos;
		isFirstEntry = false;
	}

	double deltaX = 0.0f, deltaY = 0.0f;
	deltaX = xpos - lastPosX;
	deltaY = ypos - lastPosY;
	lastPosX = xpos;
	lastPosY = ypos;

	_camera->rotate(Camera::Rotation::UP, -deltaY * _mouseSensitivity);
	_camera->rotate(Camera::Rotation::CW, deltaX * _mouseSensitivity);
}