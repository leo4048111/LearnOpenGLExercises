#pragma once

#include "pch.h"

class VertexBuffer
{
private:
	GLuint _id;

public:
	VertexBuffer(const void* data, const size_t size);
	~VertexBuffer() = default;

public:
	void bind() const;
	void unbind() const;
};

VertexBuffer::VertexBuffer(const void* data, const size_t size)
{
	GLCall(glGenBuffers(1, &_id));
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	this->unbind();
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}