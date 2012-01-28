// includes
#include "global.h"

// prototypes.
void paint(void);
void resize(int width , int height);
void drag(int x ,int y);
void keyPress(unsigned char key , int x , int y);
void keyPressSpecial(int key , int x , int y);

// main
int main(int argc , char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Free-Curve to Line convertion");
	
	/*freePoints.push_back(pair<int,int>(10,5));
	freePoints.push_back(pair<int,int>(1,2));*/
	/*LARGE_INTEGER time;
	LARGE_INTEGER freq;
	QueryPerformanceCounter(&time);
	QueryPerformanceFrequency(&freq);
	cout<<time.QuadPart<<endl;
	cout<<freq.QuadPart<<endl;*/


	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1,0,1);
	glutDisplayFunc(paint);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(keyPressSpecial);
	glutMotionFunc(drag);
	glutMainLoop();
	return 0;
} // end main
