#pragma once

#include "sdk/VertexArray.hpp"
#include "sdk/Shader.hpp"
#include "sdk/Renderer.hpp"

class Planet
{
private:
	std::shared_ptr<VertexArray> _va;
	std::shared_ptr<Shader> _shader;
	glm::mat4 _model;

public:
	Planet(std::shared_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader):
		_va(va), _shader(shader), _model(glm::mat4(1.0f))
	{
		_model = glm::translate(_model, glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void draw(GLenum mode);

	void moveTo(glm::vec3 pos);
};

void Planet::draw(GLenum mode)
{
	_shader->uniformMatrix4fv("u_model", _model);
	Renderer::getInstance()->draw(*_va, *_shader, mode);
}

void Planet::moveTo(glm::vec3 pos)
{
	_model = glm::translate(glm::mat4(1.0f), pos);
}

