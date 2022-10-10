#pragma once

#include "Headers.hpp"

class IndexBuffer
{
private:
	GLuint _id;
	const unsigned int _count;
public:
	IndexBuffer(const void* data, const unsigned int count);
	~IndexBuffer();
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

public:
	void bind() const;
	void unbind() const;
	const unsigned int count() const { return _count; };
};

IndexBuffer::IndexBuffer(const void* data, const unsigned int count) :
	_count(count)
{
	glGenBuffers(1, &_id);
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	this->unbind();
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &_id))
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
