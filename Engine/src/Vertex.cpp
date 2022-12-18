#include "Vertex.h"

Vertex::Vertex()
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	color.red = 1.0f;
	color.green = 1.0f;
	color.blue = 1.0f;
	color.alpha = 1.0f;
}

Vertex::Vertex(Position position, Color color)
{
	this->position = position;
	this->color = color;
}