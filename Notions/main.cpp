// compilation control defines
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// includes
#include "global.h"
#include "../../unsorted/windows common.h"
#include "../../unsorted/DirectInput Wrapper.h"
#include "../../unsorted/Keyboard Wrapper.h"
#include "../../unsorted/Mouse Wrapper.h"
#include "../../unsorted/CPU clock.h"
#include "../../unsorted/StopWatch.h"
#include <boost/thread.hpp>

// prototypes.
void paint(void);
void resize(int width , int height);
void drag(int x ,int y);
void keyPress(unsigned char key , int x , int y);
void keyPressSpecial(int key , int x , int y);
void mouseClick(int button, int state, int x, int y);


ofstream output("c:/output/test.txt");
StopWatch gTimer("ms");
unsigned int gN;


void intTrower()
{
	throw 0;
} // end function intThrower

void displayLoop()
{
} // end function displayLoop


void deviceLoop(InstanceHandle currentInstance , WindowHandle mainWindow)
{

	StopWatch timer("ìs");
	unsigned int n;
	CHAR oldKey[256] = {0};
	CHAR oldButton0 = 0;
	CHAR oldButton1 = 0;

	DirectInput directInput(currentInstance);
	DIKeyboard keyboard(directInput.iObject,mainWindow);
	DIMouse mouse(directInput.iObject,mainWindow);

	keyboard.acquire();
	mouse.acquire();
	timer.push();
	n = 0;
	while(1)
	{
		++n;
		keyboard.getState();
		mouse.getState();

		
		if((keyboard.key[DIK_RETURN] & 0x80) && !(oldKey[DIK_RETURN] & 0x80))
			keyPress('\r',mouse.absX,mouse.absY);
		if((keyboard.key[DIK_BACK] & 0x80) && !(oldKey[DIK_BACK] & 0x80))
			keyPress('\b',mouse.absX,mouse.absY);
		if((keyboard.key[DIK_ESCAPE] & 0x80) && !(oldKey[DIK_ESCAPE] & 0x80))
		{
			keyPress('\33',mouse.absX,mouse.absY);
			break;
		} // end if

		if((keyboard.key[DIK_RIGHT] & 0x80) && !(oldKey[DIK_RIGHT] & 0x80))
			keyPressSpecial(GLUT_KEY_RIGHT,mouse.absX,mouse.absY);
		if((keyboard.key[DIK_LEFT] & 0x80) && !(oldKey[DIK_LEFT] & 0x80))
			keyPressSpecial(GLUT_KEY_LEFT,mouse.absX,mouse.absY);
		if((keyboard.key[DIK_UP] & 0x80) && !(oldKey[DIK_UP] & 0x80))
			keyPressSpecial(GLUT_KEY_UP,mouse.absX,mouse.absY);
		if((keyboard.key[DIK_DOWN] & 0x80) && !(oldKey[DIK_DOWN] & 0x80))
			keyPressSpecial(GLUT_KEY_DOWN,mouse.absX,mouse.absY);

		memcpy(oldKey,keyboard.key,sizeof(oldKey));

		if((mouse.button[0] & 0x80) && !(oldButton0 & 0x80))				// left button changed state
			mouseClick(GLUT_LEFT_BUTTON,GLUT_DOWN,mouse.absX,mouse.absY);
		else if(!(mouse.button[0] & 0x80) && (oldButton0 & 0x80))
			mouseClick(GLUT_LEFT_BUTTON,GLUT_UP,mouse.absX,mouse.absY);

		if((mouse.button[1] & 0x80) && !(oldButton1 & 0x80))				// right button changed state
			mouseClick(GLUT_RIGHT_BUTTON,GLUT_DOWN,mouse.absX,mouse.absY);
		else if(!(mouse.button[1] & 0x80) && (oldButton1 & 0x80))
			mouseClick(GLUT_RIGHT_BUTTON,GLUT_UP,mouse.absX,mouse.absY);

		if((mouse.button[0] & 0x80) && (oldButton0 & 0x80) && (mouse.X || mouse.Y))
			drag(mouse.absX,mouse.absY);


		oldButton0 = mouse.button[0];
		oldButton1 = mouse.button[1];				
	} // end while

	output << setw(15) << timer.pop()/n << timer.getUnit() << endl;
	output << setw(15) << gTimer.pop()/gN << gTimer.getUnit() << endl;
	output.close();
	system("start c:/output/test.txt");
	exit(0);
} // end function deviceLoop



// main
int WINAPI WinMain(InstanceHandle currentInstance , InstanceHandle PreviusInstance , CHAR *commandLineArguments , int windowMode)
{
	int argc = 1;
	char *dummy = "Mark III";
	char **argv = &dummy;
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Free-Curve to Line convertion");

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	multiplier = 1.0e6 / freq.QuadPart;

	glutFullScreen();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1,0,1);
	glutDisplayFunc(intTrower);
	try
	{
		glutMainLoop();
	}
	catch(int)
	{
		// do nothing
	} // end catch

	WindowHandle mainWindow = FindWindow(0,"Free-Curve to Line convertion");

	boost::thread events(deviceLoop,currentInstance,mainWindow);

	StopWatch timer("ms");

	gTimer.push();
	gN = 0;
	timer.push();
	while(1)
	{
		//if(timer.peek() > 12)
		//{
			++gN;
			timer.pop();
			timer.push();
			paint();			
		//} // end if
	} // end while




	return 0;
} // end function WinMain
