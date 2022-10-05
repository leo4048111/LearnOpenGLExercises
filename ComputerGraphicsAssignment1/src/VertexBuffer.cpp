#include "VertexBuffer.h"
#include "Helper.hpp"

VertexBuffer::VertexBuffer(const unsigned int size, const void* data)
{
	GLCall(glGenBuffers(1, &_id));
	this->bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	this->unBind();
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &_id));
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

void VertexBuffer::unBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
