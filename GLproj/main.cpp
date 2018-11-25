#include <GL/glut.h>
#include <SOIL2.h>

int w = 0, h = 0;
GLfloat xrotate, yrotate, zrotate;

void Init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;

	w = x;
	h = y;
}

void draw_wheel(GLfloat x, GLfloat y, GLfloat z, GLfloat of_x, GLfloat of_y, GLfloat of_z) {
	glPushMatrix();
	glTranslatef(x + of_x, y - of_y, z - of_z);
	glutSolidTorus(0.03, 0.04, 10, 10);
	glPopMatrix();
}

void draw_light(GLfloat x, GLfloat y, GLfloat z, GLfloat of_x, GLfloat of_y, GLfloat of_z) {
	glPushMatrix();
	glTranslatef(x + of_x, y - of_y, z - of_z);
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();
}
void draw_car(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1.0f, 0, 0);
	glutSolidCube(0.3f);

	glPushMatrix();
	glColor3f(0, 0, 1.0f);
	glTranslatef(x + 0.25, y - 0.05, z);
	glutSolidCube(0.2f);
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	draw_wheel(x, y, z, 0.25, 0.15, -0.07);
	draw_wheel(x, y, z, 0.25, 0.15, 0.07);
	draw_wheel(x, y, z, -0.08, 0.15, 0.07);
	draw_wheel(x, y, z, -0.08, 0.15, -0.07);

	glColor3f(1.0f, 1.0f, 0.0f);
	draw_light(x, y, z, 0.35, 0.1, 0.07);
	draw_light(x, y, z, 0.35, 0.1, -0.07);
	draw_light(x, y, z, -0.15, 0.1, 0.09);
	draw_light(x, y, z, -0.15, 0.1, -0.09);
	glPopMatrix();
}

void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glRotatef(xrotate, 1.0, 0.0, 0.0);
	glRotatef(yrotate, 0.0, 1.0, 0.0);

	draw_car(0, 0, 0);
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