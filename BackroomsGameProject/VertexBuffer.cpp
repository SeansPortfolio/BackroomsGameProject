#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	VertexBufferObject = 0;
	ElementsCount = 0;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &VertexBufferObject);
}

void VertexBuffer::Create(const void* data, unsigned int size)
{
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
