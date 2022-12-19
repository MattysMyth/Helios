#ifndef VERTEX_H
#define VERTEX_H

struct Position
{
	float x, y, z;
};

struct Color
{
	float red, green, blue, alpha;
};

struct Vertex
{

	Position position;
	Color color;

	Vertex();
	Vertex(Position position, Color color);

};

#endif // !VERTEX_H
