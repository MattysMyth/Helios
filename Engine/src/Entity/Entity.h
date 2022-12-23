#ifndef ENTITY_H
#define ENTITY_H

#include "../Renderer/Vertex.h"
#include <vector>

extern int entityCount;

class Entity
{
public:

	struct Position
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	struct Rotation
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	struct Scale
	{
		float x = 1.0f;
		float y = 1.0f;
		float z = 1.0f;
	};

	struct Transform
	{
		Position position;
		Rotation rotation;
		Scale scale;
	};

	Entity();
	~Entity();

	Transform transform;
	std::vector<Vertex> verticies;

	virtual void update();

private:
	
};

#endif // !ENTITY_H
