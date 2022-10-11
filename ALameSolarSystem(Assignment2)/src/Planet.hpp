#pragma once

#include "sdk/VertexArray.hpp"
#include "sdk/Shader.hpp"
#include "sdk/Renderer.hpp"

class Planet
{
private:
	// some renderer stuff
	std::shared_ptr<VertexArray> _va;
	std::shared_ptr<Shader> _shader;

	// attribs
	glm::vec3 _pos;
	glm::vec3 _scale;
	glm::vec4 _color;
	float _mass;

public:
	Planet(std::shared_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader, 
		float mass = 1.0f, glm::vec3 pos = {0.0f, 0.0f, 0.0f}, glm::vec3 scale = {1.0f, 1.0f, 1.0f}, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f}) :
		_va(va), _shader(shader), _pos(pos), _scale(scale), _color(color), _mass(mass)
	{
	}

	void draw(GLenum mode = GL_FILL);

	void update(const glm::vec3 center, const float centerMass, const float eccentricity, const float focalDistance);

	void scale(const glm::vec3 scale);

	void moveTo(const glm::vec3 pos);

	const glm::vec3 position() { return _pos; };

	const float mass() { return _mass; };
};

void Planet::update(const glm::vec3 center, const float centerMass, const float eccentricity, const float focalDistance)
{
	float distance = glm::length(_pos - center);
	float centralForce = 10000000 * centerMass * _mass / (distance * distance);
	float angularVelocity = sqrtf(centralForce / (_mass * distance));

	static float degreeDelta = 0.f;
	static float lastFrame = 0.f;
	static bool isFirstEntry = true;
	if (isFirstEntry)
	{
		lastFrame = glfwGetTime();
		isFirstEntry = false;
		return;
	}

	float currentFrame = (float)glfwGetTime();
	degreeDelta += (currentFrame - lastFrame) * angularVelocity;
	lastFrame = currentFrame;

	float e = eccentricity;
	CLAMP(e, 0.01f, 0.99f);
	float ratio = sqrtf(1 - e * e);
	_pos.x = center.x + cosf(glm::radians(degreeDelta)) * focalDistance;
	_pos.y = center.y;
	_pos.z = center.z + ratio * sinf(glm::radians(degreeDelta)) * focalDistance;
}

void Planet::draw(GLenum mode)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), _pos);
	model = glm::scale(model, _scale);
	_shader->uniformMatrix4fv("u_model", model);
	_shader->uniform4fv("u_color", _color);
	Renderer::getInstance()->draw(*_va, *_shader, mode);
}

void Planet::scale(const glm::vec3 scale)
{
	_scale = scale;
}

void Planet::moveTo(const glm::vec3 pos)
{
	_pos = pos;
}

