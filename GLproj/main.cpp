#include <GL/glut.h>
#include <SOIL2.h>
#include <cmath>
#include "Lorry.h"
#include <utility>

int w = 0, h = 0;
GLfloat xrotate, yrotate, zrotate;
bool front_lights = false, back_lights = false;

Lorry car;

void Init(void)
{
	car.z += 1;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// ������� ���������
	glEnable(GL_LIGHTING);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
	// �������������� ���������� �������� �
	// ��������� �����
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


void draw_light(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat of_x, GLfloat of_y, GLfloat of_z, GLenum num_light, bool dir) {
	GLfloat px = size * (x + of_x), py = size * (y + of_y), pz = size * (z + of_z);
	glPushMatrix();
	glTranslatef(px, py, pz);
	GLfloat light_diffuse[4];
	GLfloat light_position[4];
	GLfloat light_spot_direction[3];
	GLfloat color_light[4];
	if(dir){
		light_diffuse[0] = 1;
		light_diffuse[1] = 1;
		light_diffuse[2] = 0;
		light_diffuse[3] = 1;
		light_position[0] = 0.01;
		light_position[1] = 0;
		light_position[2] = 0;
		light_position[3] = 1;
		light_spot_direction[0] = 1;
		light_spot_direction[1] = 0;
		light_spot_direction[2] = 0;
		color_light[0] = 1; 
		color_light[1] = 1;
		color_light[2] = 0.4;
		color_light[3] = 1;
		glLightf(num_light, GL_LINEAR_ATTENUATION, 0.5);
	}
	else {
		light_diffuse[0] = 1;
		light_diffuse[1] = 0;
		light_diffuse[2] = 0;
		light_diffuse[3] = 1;
		light_position[0] = -0.01;
		light_position[1] = 0;
		light_position[2] = 0;
		light_position[3] = 1;
		light_spot_direction[0] = -1;
		light_spot_direction[1] = 0;
		light_spot_direction[2] = 0;
		color_light[0] = 1;
		color_light[1] = 0;
		color_light[2] = 0;
		color_light[3] = 1;
		glLightf(num_light, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(num_light, GL_QUADRATIC_ATTENUATION, 1.5);
	}
	GLfloat light_ambient[] = { 0, 0, 0, 1 };

	glLightfv(num_light, GL_AMBIENT, light_ambient);
	glLightfv(num_light, GL_DIFFUSE, light_diffuse);
	glLightfv(num_light, GL_POSITION, light_position);
	glLightfv(num_light, GL_SPECULAR, light_diffuse);
	glLightf(num_light, GL_SPOT_CUTOFF, 50);
	glLightf(num_light, GL_SPOT_EXPONENT, 5); 
	glLightfv(num_light, GL_SPOT_DIRECTION, light_spot_direction);
	glLightf(num_light, GL_CONSTANT_ATTENUATION, 3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color_light);
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
	draw_light(0, 0, 0, size, 0.35, -0.1, -0.07, GL_LIGHT1, true);
	draw_light(0, 0, 0, size, 0.35, -0.1, 0.07, GL_LIGHT2, true);
	draw_light(0, 0, 0, size, -0.15, -0.1, -0.09, GL_LIGHT3, false);
	draw_light(0, 0, 0, size, -0.15, -0.1, 0.09, GL_LIGHT4, false); 
	glPopMatrix();
}

void draw_lamp(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat angle) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 0.0, 0.0, 1);

	glColor3f(0.0f, 0.0f, 0.0f);
	GLUquadricObj *quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.2, size * 15, size * 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size * (0.035), size * (0.03),0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.05, size * 15, size * 15);
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(size * ( 0.11), size * ( 0.025), 0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.08, size * 15, size * 15);
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(size * (0.12), size * ( 0.025), 0 );
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(quadObj, size * 0.01, size * 0.01, size * 0.01, size * 15, size * 15);
	glPopMatrix();

	glPopMatrix();
}

void draw_ground(GLdouble x0, GLdouble x1, GLdouble y0, GLdouble y1, int divx, int divy ) {
	GLfloat light_position[] = { 1,1,1,1 };
	GLfloat material_diffuse[] = { 1, 1, 1, 1 };
	GLfloat material_emission[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_position);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	glColor3f(0.0f, 0.0f, 0.0f);
	glNormal3f(0, 0, 1);
	
	
	GLdouble stepx = (x1 - x0) / divx;
	GLdouble stepy = (y1 - y0) / divy;

	GLdouble x, y;
	y = y0;
	x = x0;
	glBegin(GL_QUADS);
	for (size_t i = 0; i < divx; i++)
	{
		y = y0;
		for (size_t j = 0; j < divy; j++)
		{
			glVertex3f(x, y, 0.0f);
			glVertex3f(x, y - stepy, 0.0f);
			glVertex3f(x - stepx, y - stepy, 0.0f);
			glVertex3f(x - stepx, y, 0.0f);
			y += stepy;
		}
		x += stepx;
	}
	glEnd();

}

void cross(GLdouble a[], GLdouble b[], GLdouble res[]) {
	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];

}

void norm(GLdouble a[]) {
	GLdouble len = std::sqrt(a[0] + a[1] + a[2]);
	for (size_t i = 0; i < 3; i++)
		a[i] /= len;
}

void set_cam() {
	
	glLoadIdentity();

	GLfloat light_diffuse[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat light_position[] = {0,0,0,1 };
	GLfloat light_ambient[] = { 0, 0, 0, 1 };
	GLfloat light_specular[] = { 0.1, 0.1, 0.1, 1 };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);

	/*GLfloat params[4] = {0,0,0,1};
	GLfloat params1[4] = { 0.0,0.0,0.0,0 };
	GLfloat params2[4] = { 0.5,0.5,0.5,1 };
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, params1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, params2);
	glLightfv(GL_LIGHT0, GL_AMBIENT, params);*/


	
	GLdouble cam_offset = -2;


	GLdouble fwd[3]{ -cam_offset * std::cos(car.angle),   -cam_offset * std::sin(car.angle) ,  -cam_offset };
	GLdouble tmp[3]{ 0,0,1 };
	GLdouble right[3], up[3];
	norm(fwd);
	norm(tmp);
	cross(tmp, fwd,right);
	cross(fwd, right, up);
	
	

	gluLookAt(car.x - cam_offset *std::cos(car.angle), car.y - cam_offset * std::sin(car.angle), car.z - cam_offset, car.x, car.y, car.z, up[0], up[1], up[2]);
	//gluLookAt(car.x, car.y, 4, car.x, car.y, car.z, 1, 0, 0);
}


void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	set_cam();
	glPushMatrix();
	draw_ground(-10,10,-10,10,100,100);
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
		
		car.Turn(5);
		break;
	case 'd':	// D
		
		car.Turn(-5);
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

void specialKeys(int key, int x, int y) {
	switch (key)
	{ 
	case GLUT_KEY_PAGE_UP:
		if(front_lights){
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			front_lights = false;
		}
		else {
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			front_lights = true;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (back_lights) {
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
			back_lights = false;
		}
		else {
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			back_lights = true;
		}
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
	glutSpecialFunc(specialKeys);

	Init();
	glutMainLoop();
	return 0;         
}