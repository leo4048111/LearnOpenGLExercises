#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position);
	~Camera();

private:
	glm::vec3 _up;
	glm::vec3 _direction;
	glm::vec3 _pos;

	float _pitch{0};
	float _yaw{0};

public:
	void setPosition(glm::vec3);
	glm::vec3 getPosition() const { return _pos; };
	glm::vec3 getDirection() const { return glm::normalize(_direction); };
	glm::vec3 getUp() const { return glm::normalize(_up); };
	glm::vec3 getRight() const { return glm::normalize(glm::cross(_up, _direction)); };

	glm::mat4 getViewMatrix() const;

	float getPitch() const { return _pitch; };
	float getYaw() const { return _yaw; };

	void setPitch(float pitch);
	void setYaw(float yaw);

private:
	void updateVectors();
};