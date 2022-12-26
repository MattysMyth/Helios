#ifndef TRIANGLE2_H
#define TRIANGLE2_H

#include "Entity/Entity.h"

class Triangle2 : public Entity
{
public:
	Triangle2();
	~Triangle2();

	void update() override;

};

#endif // !TRIANGLE2_H