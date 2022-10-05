#pragma once

class IndexBuffer
{
private:
	unsigned int _id{ 0 };
	unsigned int _count{ 0 };

public:
	IndexBuffer(const unsigned int count, const void* data);
	~IndexBuffer();

	void bind() const;
	void unBind() const;

	const unsigned int count() const { return _count; }
};