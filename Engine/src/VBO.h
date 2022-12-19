#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <vector>
#include "Vertex.h"

// Structure to hold all data relating to a generated Vertex Buffer Object in OpenGL
struct VBO
{
	VBO();
	VBO(std::vector<Vertex> verticies);
	~VBO();

	void update(std::vector<Vertex> verticies);

	void bind();
	void unbind();

	unsigned int getID();

private:
	unsigned int id;
	unsigned int index = 0;

};

#endif // !VBO_H
