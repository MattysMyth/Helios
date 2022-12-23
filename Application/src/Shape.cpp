#include "Shape.h"

Shape::Shape()
{
    Vertex vert1, vert2, vert3;

    vert1.position.x = -0.5f;
    vert1.position.y = -0.5f;

    vert2.position.x = 0.0f;
    vert2.position.y = 0.5f;

    vert3.position.x = 0.5f;
    vert3.position.y = -0.5f;

    verticies.push_back(vert1);
    verticies.push_back(vert2);
    verticies.push_back(vert3);
}

Shape::~Shape()
{

}

void Shape::update()
{
	
}