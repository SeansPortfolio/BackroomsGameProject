#pragma once

#include <GL\glew.h>

class VertexBuffer
{
public:

	VertexBuffer();
	~VertexBuffer();

	void Create(const void*, unsigned int);

	void Bind();
	void Unbind();

	inline unsigned int GetElementsCount() const { return ElementsCount; }

private:


	unsigned int VertexBufferObject;

	unsigned int ElementsCount;


};

