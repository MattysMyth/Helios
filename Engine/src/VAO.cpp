#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

VAO::~VAO()
{
	glDeleteBuffers(1, &id);
}

void VAO::bind()
{
	glBindVertexArray(id);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

unsigned int VAO::getID()
{
	return id;
}