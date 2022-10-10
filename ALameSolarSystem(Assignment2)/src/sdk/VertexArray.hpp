#pragma once

#include "Headers.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"
#include "IndexBuffer.hpp"

class VertexArray
{
private:
	GLuint _id;
	const VertexBuffer& _vbo;
	const IndexBuffer& _ibo;
	const BufferLayout& _layout;

public:
	VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const BufferLayout& layout);
	~VertexArray();
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;

public:
	void bind() const;
	void unbind() const;
	const unsigned int count() const { return _ibo.count(); };
};

VertexArray::VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const BufferLayout& layout) :
	_vbo(vbo), _ibo(ibo), _layout(layout)
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