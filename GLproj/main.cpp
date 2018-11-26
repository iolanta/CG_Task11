#include <GL/glut.h>
#include <SOIL2.h>
#include <cmath>
#include "Lorry.h"
#include <utility>
int w = 0, h = 0;
GLfloat xrotate, yrotate, zrotate;

Lorry car;

void Init(void)
{
	car.z += 1;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// рассчет освещения
	//glEnable(GL_LIGHTING);

	// двухсторонний расчет освещения
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// автоматическое приведение нормалей к
	// единичной длине
	glEnable(GL_NORMALIZE);
}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;

	w = x;
	h = y;

	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, (GLdouble)w / h, 0.1, 10);

}

void draw_wheel(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat of_x, GLfloat of_y, GLfloat of_z) {
	glPushMatrix();
	glTranslatef(size*(x + of_x), size*(y + of_y), size*(z + of_z));
	glutSolidTorus(size * 0.03, size * 0.04, size * 10, size * 10);
	glPopMatrix();
}


void draw_light(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat of_x, GLfloat of_y, GLfloat of_z, GLenum num_light, int dir) {
	GLfloat px = size * (x + of_x), py = size * (y + of_y), pz = size * (z + of_z);
	glPushMatrix();
	glTranslatef(px, py, pz);

	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5 };
	GLfloat light_position[] = { 1,0,0 };
	GLfloat light_spot_direction[] = { 0, 1, 0 };
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1 };
	//glEnable(num_light);
	glLightfv(num_light, GL_AMBIENT, light_ambient);
	glLightfv(num_light, GL_DIFFUSE, light_diffuse);
	glLightfv(num_light, GL_POSITION, light_position);
	glLightf(num_light, GL_SPOT_CUTOFF, 30);
	glLightfv(num_light, GL_SPOT_DIRECTION, light_spot_direction);
	glutSolidSphere(size * 0.03, size * 10, size * 10);
	glPopMatrix();
}
void draw_car(GLfloat x, GLfloat y, GLfloat z,GLdouble turn, int size) {
	glPushMatrix();
	
	glTranslatef(x, y, z);
	glRotatef(turn, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glColor3f(1.0f, 0, 0);
	glutSolidCube(size * 0.3f);

	glPushMatrix();
	glColor3f(0, 0, 1.0f);
	glTranslatef(size * ( + 0.25), size * ( - 0.05),0);
	glutSolidCube(size * 0.2f);
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	draw_wheel(0, 0, 0, size, 0.25, -0.15, 0.07);
	draw_wheel(0, 0, 0, size, 0.25, -0.15, -0.07);
	draw_wheel(0, 0, 0, size, -0.08, -0.15, -0.07);
	draw_wheel(0, 0, 0, size, -0.08, -0.15, 0.07);

	glColor3f(1.0f, 1.0f, 0.0f);
	draw_light(0, 0, 0, size, 0.35, -0.1, -0.07, GL_LIGHT1, 1);
	draw_light(0, 0, 0, size, 0.35, -0.1, 0.07, GL_LIGHT2, 1);
	draw_light(0, 0, 0, size, -0.15, -0.1, -0.09, GL_LIGHT3, -1);
	draw_light(0, 0, 0, size, -0.15, -0.1, 0.09, GL_LIGHT4, -1); 
	glPopMatrix();
}

void draw_lamp(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat angle) {
	glPushMatrix();
	//glTranslatef(x, y, z);
	glRotatef(angle, 0.0, 1.0, 0.0);

	glColor3f(0.0f, 0.0f, 0.0f);
	GLUquadricObj *quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.2, size * 15, size * 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size * (x + 0.035), size * (y + 0.03), size * z);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.05, size * 15, size * 15);
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(size * (x + 0.11), size * (y + 0.025), size * z);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.08, size * 15, size * 15);
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(size * (x + 0.12), size * (y + 0.025), size * z);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.01, size * 15, size * 15);
	glPopMatrix();

	glPopMatrix();
}

void draw_ground() {
	glColor3f(0.0f, 0.0f, 0.5f);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(-20, -20, 0.0f);
	glVertex3f(-20, 20, 0.0f);
	glVertex3f(20, 20, 0.0f);
	glVertex3f(20, -20, 0.0f);
	glEnd();

}

void set_cam() {
	
	glLoadIdentity();
	GLfloat params[4] = {0.1,0.1,0.1,0 };
	GLfloat params1[4] = { 0.0,0.0,0.0,0 };
	GLfloat params2[4] = { 0.5,0.5,0.5,1 };
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, params);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, params1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, params2);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, params);

	GLdouble up[3]{-3.0, 0 ,3.0 };
	GLdouble len = std::sqrt(up[0] + up[1] + up[2]);
	for (size_t i = 0; i < 3; i++)
		up[i] /= len;
	//GLdouble right[3]{ -up[2], 0, up[0] }; 
	GLdouble newup[3]{ -up[0] * up[1], up[0] * up[0] + up[2] * up[2], -up[2] * up[1] };
	
	//gluLookAt(car.x - 3.0, 0, car.z+3.0, car.x, car.y, car.z,newup[0], newup[1] ,newup[2]);
	//gluLookAt(car.x-2*std::cos(car.angle), car.y -2 * std::sin(car.angle), 2, car.x, car.y, car.z,0, 0, 1);
	gluLookAt(car.x, car.y, 4, car.x, car.y, car.z, 1, 0, 0);
}


void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	set_cam();
	glPushMatrix();
	draw_ground();
	draw_car(car.x, car.y, car.z, car.get_ang(),1);
	
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)	
{
	switch (key)
	{
	case 'a':	// A
		
		car.Turn(-5);
		break;
	case 'd':	// D
		
		car.Turn(5);
		break;
	case 'w':	// W
		
		car.Move(0.3);
		break;
	case 's':	// S
		
		car.Move(-0.3);
		break;
	default:
		break;

	}

	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(Update);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	Init();
	glutMainLoop();
	return 0;         
}