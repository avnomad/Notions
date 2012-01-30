// includes
#include "global.h"

// handler prototypes.
void paint(void);
void resize(int width , int height);
void drag(int x ,int y);
void keyPress(unsigned char key , int x , int y);
void keyPressSpecial(int key , int x , int y);

// main
int main(int argc , char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Free-Curve to Line convertion");
	
	// application initialization
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	multiplier = 1.0e6 / freq.QuadPart;

	// OpenGL initialization
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1,0,1);

	// glut main loop initialization
	glutDisplayFunc(paint);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(keyPressSpecial);
	glutMotionFunc(drag);
	glutMainLoop();
	return 0;
} // end main
