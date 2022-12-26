#include "Triangle1.h"

Triangle1::Triangle1()
{
    Vertex vert1, vert2, vert3, vert4;

    vert1.position.x = -0.5f;
    vert1.position.y = -0.5f;

    vert2.position.x = -0.5f;
    vert2.position.y = 0.5f;

    vert3.position.x = 0.5f;
    vert3.position.y = 0.5f;

    vert4.position.x = 0.5f;
    vert4.position.y = -0.5f;

    verticies.push_back(vert1);
    verticies.push_back(vert2);
    verticies.push_back(vert3);
    verticies.push_back(vert4);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
}

Triangle1::~Triangle1()
{

}

void Triangle1::update()
{
	
}