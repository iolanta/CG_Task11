#include "Lorry.h"
#include <cmath>



GLdouble Lorry::get_ang()
{
	return angle / pid;
}

void Lorry::Move(GLdouble d)
{
	x += std::cos(angle)*d;
	y += std::sin(angle)*d;
}

void Lorry::Turn(GLdouble ang)
{
	ang *= pid;
	angle += ang;
	if (angle < -pi2)
		angle += pi2;
	else if (angle > pi2)
		angle -= pi2;
}

Lorry::Lorry()
{

	x = 0;
	y = 0;
	z = 0;
	angle = 0;
}


Lorry::~Lorry()
{
}
