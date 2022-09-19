#include "Controller.h"
#include <functional>

Controller::Controller(GLFWwindow* window):
	_cameraOrigin(glm::vec3(0.0f, 0.0f, 3.0f))
{
	this->_camera = std::make_unique<Camera>(_cameraOrigin);

	registerMouseCallback(window);
}

void Controller::keyboardHandler(GLFWwindow* window)
{
	static float deltaTime = 0.0f;
	static float lastFrame = 0.0f;
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;

	const float mass = 50.0f;
	const float g = 9.8f;
	auto cameraPos = _camera->getPosition();
	bool grounded = (cameraPos.y == 1.0f);
	static float velocity = 0.f;
	const float frameTime = 0.01f;

	cameraPos.y += velocity * frameTime;
	velocity -= g * frameTime;
	if (cameraPos.y <= 1.0f) cameraPos.y = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += _camera->getDirection() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= _camera->getDirection() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += _camera->getRight() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= _camera->getRight() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		velocity = 2.f;
	}

	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
	{
		if (isCursorHidden)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL), isCursorHidden = false;
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN), isCursorHidden = true;
	}

	_camera->setPosition(cameraPos);
}

void Controller::mouseHandler(GLFWwindow* window, double xpos, double ypos)
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

	double nextPitch = _camera->getPitch() - deltaY * _mouseSensitivity;
	double nextYaw = _camera->getYaw() + deltaX * _mouseSensitivity;
	if (nextPitch > 89.0f) nextPitch = 89.f;
	if (nextPitch < -89.0f) nextPitch = -89.0f;
	_camera->setPitch(nextPitch);
	_camera->setYaw(nextYaw);
}

inline void Controller::registerMouseCallback(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->isCursorHidden = true;
	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));
	glfwSetCursorPosCallback(window, Controller::mouseCallback);
}

void Controller::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Controller* p_this = static_cast<Controller*>(glfwGetWindowUserPointer(window));
	p_this->mouseHandler(window, xpos, ypos);
}
