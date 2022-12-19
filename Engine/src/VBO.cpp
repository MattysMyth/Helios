#include "VBO.h"

VBO::VBO()
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(
        GL_ARRAY_BUFFER,
        0,
        NULL,
        GL_STATIC_DRAW
    );
}

VBO::VBO(std::vector<Vertex> verticies)
{
    std::vector<float> positions;

    for (size_t i = 0; i < 3; i++)
    {
        positions.push_back(verticies[i].position.x);
        positions.push_back(verticies[i].position.y);
        positions.push_back(verticies[i].position.z);
    }

    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * positions.size(),
        static_cast<void*>(positions.data()),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
        index,
        3, // Corresponding to x, y and z values
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 3, // 3 being the size of each set of x, y and z values
        0
    );
}

VBO::~VBO()
{

}

void VBO::update(std::vector<Vertex> verticies)
{
    std::vector<float> positions;

    for (size_t i = 0; i < 3; i++)
    {
        positions.push_back(verticies[i].position.x);
        positions.push_back(verticies[i].position.y);
        positions.push_back(verticies[i].position.z);
    }

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * positions.size(),
        static_cast<void*>(positions.data()),
        GL_STATIC_DRAW
    );
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VBO::getID()
{
    return id;
}