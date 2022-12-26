#ifndef TRIANGLE1_H
#define TRIANGLE1_H

#include "Entity/Entity.h"

class Triangle1 : public Entity
{
public:
	Triangle1();
	~Triangle1();

	void update() override;

};

#endif // !TRIANGLE1_H
