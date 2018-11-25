#include <GL/glut.h>
#include <SOIL2.h>

int w = 0, h = 0;
GLfloat xrotate, yrotate, zrotate;

void Init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// рассчет освещения
	glEnable(GL_LIGHTING);

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
}

void draw_wheel(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat of_x, GLfloat of_y, GLfloat of_z) {
	glPushMatrix();
	glTranslatef(size*(x + of_x), size*(y + of_y), size*(z + of_z));
	glutSolidTorus(size * 0.03, size * 0.04, size * 10, size * 10);
	glPopMatrix();
}

void draw_light(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat of_x, GLfloat of_y, GLfloat of_z) {
	glPushMatrix();
	glTranslatef(size * (x + of_x), size * (y + of_y), size * (z + of_z));
	glutSolidSphere(size * 0.03, size * 10, size * 10);
	glPopMatrix();
}
void draw_car(GLfloat x, GLfloat y, GLfloat z, int size) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1.0f, 0, 0);
	glutSolidCube(size * 0.3f);

	glPushMatrix();
	glColor3f(0, 0, 1.0f);
	glTranslatef(size * (x + 0.25), size * (y - 0.05), size * z);
	glutSolidCube(size * 0.2f);
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	draw_wheel(x, y, z, size, 0.25, -0.15, 0.07);
	draw_wheel(x, y, z, size, 0.25, -0.15, -0.07);
	draw_wheel(x, y, z, size, -0.08, -0.15, -0.07);
	draw_wheel(x, y, z, size, -0.08, -0.15, 0.07);

	glColor3f(1.0f, 1.0f, 0.0f);
	draw_light(x, y, z, size, 0.35, -0.1, -0.07);

	GLfloat light3_diffuse[] = { 0.4, 0.7, 0.2 };
	GLfloat light3_position[] = { size * (x + 0.35), size * (y - 0.1), size * (z - 0.07), 1.0 };
	GLfloat light3_spot_direction[] = { 1.0, 1.0, 0.0 };
	glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light3_position);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light3_spot_direction);

	draw_light(x, y, z, size, 0.35, -0.1, 0.07);
	draw_light(x, y, z, size, -0.15, -0.1, -0.09);
	draw_light(x, y, z, size, -0.15, -0.1, 0.09);
	glPopMatrix();
}

void draw_lamp(GLfloat x, GLfloat y, GLfloat z, int size, GLfloat angle) {
	glPushMatrix();
	glTranslatef(x, y, z);
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

void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glRotatef(xrotate, 1.0, 0.0, 0.0);
	glRotatef(yrotate, 0.0, 1.0, 0.0);

	draw_car(0, 0, 0, 1);
	//draw_lamp(0, 0, 0, 1, 180);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)	
{
	switch (key)
	{
	case 'a':	// A
		yrotate -= 5;
		break;
	case 'd':	// D
		yrotate += 5;
		break;
	case 'w':	// W
		xrotate += 5;
		break;
	case 's':	// S
		xrotate -= 5;
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