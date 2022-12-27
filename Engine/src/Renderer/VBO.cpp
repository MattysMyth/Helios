#include "VBO.h"

#include <iostream>

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

    setVertexAttributes();
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

    setVertexAttributes();
}

VBO::~VBO()
{
    glDeleteBuffers(1, &id);
}

void VBO::update(std::vector<Vertex> verticies)
{
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(Vertex) * verticies.size(),
        &verticies.front(),
        GL_STATIC_DRAW
    );

    setVertexAttributes();
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setVertexAttributes()
{
    // Position attribute
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(
        positionIndex,
        3, // Corresponding to x, y and z values
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 7, // 3 being the size of each set of x, y and z values
        0
    );

    // Color attribute
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(
        colorIndex,
        4, // Corresponding to r, g, b and a values
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 7, // 4 being the size of each set of r, g, b and a values
        (void*)(sizeof(float) * 3) // Offset by 3 floats. The order of bytes in the VBO is 3 position float followed by 4 color floats. 
    );
}

unsigned int VBO::getID()
{
    return id;
}