#include "Entity.h"

int entityCount;

Entity::Entity()
{
	entityCount++;
}

Entity::~Entity()
{
	entityCount--;
}

void Entity::update()
{

}