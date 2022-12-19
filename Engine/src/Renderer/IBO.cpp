#include "IBO.h"

IBO::IBO()
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		0, 
		NULL, 
		GL_STATIC_DRAW
	);
}

IBO::IBO(std::vector<unsigned int> indices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		sizeof(unsigned int) * indices.size(),
		static_cast<void*>(indices.data()), 
		GL_STATIC_DRAW
	);
}

IBO::~IBO()
{
	glDeleteBuffers(1, &id);
}

void IBO::update(std::vector<unsigned int> indices)
{
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * indices.size(),
		static_cast<void*>(indices.data()),
		GL_STATIC_DRAW
	);
}

void IBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IBO::getID()
{
	return id;
}