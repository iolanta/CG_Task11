#pragma once
#include <GL/glut.h>
class Lorry
{
	const GLdouble pid = 3.14159265359/180;
	const GLdouble pi2 = 2*3.14159265359;
public:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble angle;
	GLdouble get_ang();
	void Move(GLdouble d);
	void Turn(GLdouble ang);
	Lorry();
	~Lorry();
};

