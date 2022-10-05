#include "IndexBuffer.h"
#include "Helper.hpp"

IndexBuffer::IndexBuffer(const unsigned int count, const void* data):
	_count(count)
{
	GLCall(glGenBuffers(1, &_id));
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	this->unBind();
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &_id))
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::unBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
