#include "Camera.h"

Camera::Camera(glm::vec3 position)
	:_pos(position), _up(glm::vec3(0.0f, 1.0f, 0.0f)), _direction(glm::vec3(0.0f, 0.0f, -1.0f))
{

}

Camera::~Camera()
{
}

void Camera::setPosition(glm::vec3 position)
{
	_pos = position;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(_pos, _pos + _direction, _up);
}

void Camera::setPitch(float pitch)
{
	this->_pitch = pitch;
	updateVectors();
}

void Camera::setYaw(float yaw)
{
	this->_yaw = yaw;
	updateVectors();
}

void Camera::updateVectors()
{
	this->_direction.x = cosf(glm::radians(_pitch)) * cosf(glm::radians(_yaw));
	this->_direction.y = sinf(glm::radians(_pitch));
	this->_direction.z = cosf(glm::radians(_pitch)) * sinf(glm::radians(_yaw));
	this->_direction = glm::normalize(this->_direction);
}
