#pragma once

class VertexBuffer
{
private:
	unsigned int _id{0};

public:
	VertexBuffer(const unsigned int size, const void* data);
	~VertexBuffer();

	void bind() const;
	void unBind() const;
};