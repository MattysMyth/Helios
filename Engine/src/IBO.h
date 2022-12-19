#ifndef IBO_H
#define IBO_H

#include <glad/glad.h>

#include <vector>

struct IBO
{
	IBO();
	IBO(std::vector<unsigned int> indices);
	~IBO();

	void update(std::vector<unsigned int> indices);

	void bind();
	void unbind();

	unsigned int getID();

private:
	unsigned int id;
	unsigned int index = 0;
};

#endif // !IBO_H
