#include "IndexBuffer.h"

#include <iostream>

IndexBuffer::IndexBuffer()
{
	IndexBufferObject = 0;
	ElementsCount = 0;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &IndexBufferObject);
}

void IndexBuffer::Create(const unsigned int* data, unsigned int count)
{
	ElementsCount = count;
	glGenBuffers(1, &IndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}


void IndexBuffer::Bind()
{
	glDrawElements(GL_TRIANGLES, ElementsCount, GL_UNSIGNED_INT, 0);
}

void IndexBuffer::Unbind()
{

}

