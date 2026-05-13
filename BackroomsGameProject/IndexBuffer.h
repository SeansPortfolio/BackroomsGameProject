#pragma once

#include <GL\glew.h>

class IndexBuffer
{
public:

	IndexBuffer();
	~IndexBuffer();

	void Create(const unsigned int*, unsigned int);
	void Bind();
	void Unbind();

	inline unsigned int GetElementsCount() const { return ElementsCount; }


private:

	unsigned int IndexBufferObject;

	unsigned int ElementsCount;

};

