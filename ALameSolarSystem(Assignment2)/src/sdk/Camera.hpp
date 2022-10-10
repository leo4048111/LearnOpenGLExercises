#pragma once

#include "Headers.hpp"

#define CLAMP(x, min, max) if(x < min) x = min; else if(x > max) x = max

class Camera
{
public:
	enum class Rotation
	{
		UP = 0,
		DOWN,
		CW,
		ACW
	};

	enum class Direction
	{
		FORWARD = 0,
		BACKWARD,
		LEFT,
		RIGHT,
		UP, 
		DOWN
	};

private:
	glm::vec3 _up;
	glm::vec3 _forward;
	glm::vec3 _position;

	GLfloat _pitch{ 0.0f };
	GLfloat _yaw{ -90.f };

public:
	Camera(glm::vec3 position);
	~Camera() = default;

public:
	const glm::mat4 viewMatrix() const { return glm::lookAt(_position, _forward + _position, _up); };
	void rotate(Rotation rotation, float angle);
	void move(Direction direction, float offset);

private:
	void update();
};

Camera::Camera(glm::vec3 position) :
	_position(position), _up(glm::vec3(0.0f, 1.0f, 0.0f)), _forward(glm::vec3(0.0f, 0.0f, -1.0f))
{
	update();
}

void Camera::rotate(Rotation rotation, float angle)
{
	switch (rotation)
	{
	case Camera::Rotation::UP:
		_pitch += angle;
		break;
	case Camera::Rotation::DOWN:
		_pitch -= angle;
		break;
	case Camera::Rotation::CW:
		_yaw += angle;
		break;
	case Camera::Rotation::ACW:
		_yaw -= angle;
		break;
	default:
		break;
	}
	
	CLAMP(_pitch, -89, 89);
	update();
}

void Camera::move(Direction direction, float offset)
{
	glm::vec3 right = glm::normalize(glm::cross(_up, _forward));
	switch (direction)
	{
	case Camera::Direction::FORWARD:
		_position += _forward * offset;
		break;
	case Camera::Direction::BACKWARD:
		_position -= _forward * offset;
		break;
	case Camera::Direction::LEFT:
		_position -= right * offset;
		break;
	case Camera::Direction::RIGHT:
		_position += right * offset;
		break;
	case Camera::Direction::UP:
		_position += _up * offset;
		break;
	case Camera::Direction::DOWN:
		_position -= _up * offset;
		break;
	default:
		break;
	}
}

void Camera::update()
{
	_forward.x = cosf(glm::radians(_pitch)) * cosf(glm::radians(_yaw));
	_forward.y = sinf(glm::radians(_pitch));
	_forward.z = cosf(glm::radians(_pitch)) * sinf(glm::radians(_yaw));
	_forward = glm::normalize(_forward);
}

