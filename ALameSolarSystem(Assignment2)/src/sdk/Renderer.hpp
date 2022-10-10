#pragma once

#include "Headers.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

class Renderer
{
public:
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

private:
	Renderer() = default;

public:
	static std::unique_ptr<Renderer>& getInstance() {
		if (_inst.get() == nullptr) _inst.reset(new Renderer);
		return _inst;
	}

	void draw(const VertexArray& va, const Shader& shader, const GLenum mode) const;

private:
	static std::unique_ptr<Renderer> _inst;
};

std::unique_ptr<Renderer> Renderer::_inst;

void Renderer::draw(const VertexArray& va, const Shader& shader, const GLenum mode) const
{
	va.bind();
	shader.enable();
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, mode));
	GLCall(glDrawElements(GL_TRIANGLES, va.count(), GL_UNSIGNED_INT, nullptr));
	va.unbind();
	shader.disable();
}