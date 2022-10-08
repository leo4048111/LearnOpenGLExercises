#pragma once

#include "def.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"
#include "IndexBuffer.hpp"

class VertexArray
{
private:
	GLuint _id;

public:
	VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const BufferLayout& layout);
	~VertexArray();

public:
	void bind() const;
	void unbind() const;
};

VertexArray::VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const BufferLayout& layout)
{
	GLCall(glGenVertexArrays(1, &_id));
	this->bind();
	vbo.bind();
	ibo.bind();
	auto& elements = layout.elements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride(), (const void*)offset));
		offset += element.count * BufferLayout::getTypeSize(element.type);
	}
	this->unbind();
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &_id));
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(_id));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}