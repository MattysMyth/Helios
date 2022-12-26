#include <Engine.h>
#include "Triangle1.h"
#include "Triangle2.h"

int main()
{
	Engine* engine = new Engine();
	Triangle1* triangle1 = new Triangle1();
	Triangle2* triangle2 = new Triangle2();

	std::vector<Entity*> entities;

	entities.push_back(triangle1);
	entities.push_back(triangle2);

	engine->loadEntities(entities);

	engine->render();
	
	return 0;
}