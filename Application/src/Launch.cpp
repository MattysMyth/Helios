#include <Engine.h>
#include "Shape.h"

int main()
{
	Engine* engine = new Engine();
	Shape* shape = new Shape();

	engine->loadModel(shape);

	engine->render();
	
	return 0;
}