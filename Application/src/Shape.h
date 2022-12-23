#ifndef SHAPE_H
#define SHAPE_H

#include "Entity/Entity.h"

class Shape : public Entity
{
public:
	Shape();
	~Shape();

	void update() override;

};

#endif // !SHAPE_H
