#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

struct VAO
{
	VAO();
	~VAO();

	void bind();
	void unbind();

	unsigned int getID();

private:
	unsigned int id;
};

#endif // !VAO_H
