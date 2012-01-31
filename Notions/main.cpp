// compilation control defines
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// includes
#include <iomanip>
using std::setw;

#include "global.h"
#include <windows/common.h>
#include <Direct Input/DirectInput Wrapper.h>
#include <Direct Input/Keyboard Wrapper.h>
#include <Direct Input/Mouse Wrapper.h>
#include <CPU clock.h>
#include <StopWatch.h>

// handler prototypes.
void paint(void);
void drag(int x ,int y);
void keyPress(unsigned char key , int x , int y);
void keyPressSpecial(int key , int x , int y);
void mouseClick(int button, int state, int x, int y);


static ofstream output("test.txt");
static StopWatch gTimer("ms");
unsigned int gN;
static StopWatch timer("ms");

InstanceHandle thisInstance;


void deviceLoop()
{
	StopWatch timer("μs");
	unsigned int n;
	CHAR oldKey[256] = {0};
	CHAR oldButton0 = 0;
	CHAR oldButton1 = 0;

	WindowHandle mainWindow = FindWindow(0,"Free-Curve to Line convertion");

	DirectInput directInput(thisInstance);
	DIKeyboard keyboard(directInput,mainWindow);
	DIMouse mouse(directInput,mainWindow);

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
			keyPress('\r',mouse.absolute.x,mouse.absolute.y);
		if((keyboard.key[DIK_BACK] & 0x80) && !(oldKey[DIK_BACK] & 0x80))
			keyPress('\b',mouse.absolute.x,mouse.absolute.y);
		if((keyboard.key[DIK_ESCAPE] & 0x80) && !(oldKey[DIK_ESCAPE] & 0x80))
		{
			keyPress('\33',mouse.absolute.x,mouse.absolute.y);
			break;
		} // end if

		if((keyboard.key[DIK_RIGHT] & 0x80) && !(oldKey[DIK_RIGHT] & 0x80))
			keyPressSpecial(GLUT_KEY_RIGHT,mouse.absolute.x,mouse.absolute.y);
		if((keyboard.key[DIK_LEFT] & 0x80) && !(oldKey[DIK_LEFT] & 0x80))
			keyPressSpecial(GLUT_KEY_LEFT,mouse.absolute.x,mouse.absolute.y);
		if((keyboard.key[DIK_UP] & 0x80) && !(oldKey[DIK_UP] & 0x80))
			keyPressSpecial(GLUT_KEY_UP,mouse.absolute.x,mouse.absolute.y);
		if((keyboard.key[DIK_DOWN] & 0x80) && !(oldKey[DIK_DOWN] & 0x80))
			keyPressSpecial(GLUT_KEY_DOWN,mouse.absolute.x,mouse.absolute.y);

		memcpy(oldKey,keyboard.key,sizeof(oldKey));

		if((mouse.button[0] & 0x80) && !(oldButton0 & 0x80))				// left button changed state
			mouseClick(GLUT_LEFT_BUTTON,GLUT_DOWN,mouse.absolute.x,mouse.absolute.y);
		else if(!(mouse.button[0] & 0x80) && (oldButton0 & 0x80))
			mouseClick(GLUT_LEFT_BUTTON,GLUT_UP,mouse.absolute.x,mouse.absolute.y);

		if((mouse.button[1] & 0x80) && !(oldButton1 & 0x80))				// right button changed state
			mouseClick(GLUT_RIGHT_BUTTON,GLUT_DOWN,mouse.absolute.x,mouse.absolute.y);
		else if(!(mouse.button[1] & 0x80) && (oldButton1 & 0x80))
			mouseClick(GLUT_RIGHT_BUTTON,GLUT_UP,mouse.absolute.x,mouse.absolute.y);

		if((mouse.button[0] & 0x80) && (oldButton0 & 0x80) && (mouse.X || mouse.Y))
			drag(mouse.absolute.x,mouse.absolute.y);


		oldButton0 = mouse.button[0];
		oldButton1 = mouse.button[1];				
	} // end while

	output << setw(15) << timer.pop()/n << timer.getUnit() << endl;
	output << setw(15) << gTimer.pop()/gN << gTimer.getUnit() << endl;
	output.close();
	system("start test.txt");
	exit(0);
} // end function deviceLoop


void always()
{
	++gN;
	timer.pop();
	timer.push();
	paint();			
}

void initialize()
{
	// the mouse coordinates will be mapped correctly to window coordinates only in full-screen anyway...
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	glViewport(0,0,windowWidth,windowHeight);

	boost::thread events(deviceLoop);

	gTimer.push();
	gN = 0;
	timer.push();

	glutIdleFunc(always);
}

// main
int WINAPI WinMain(InstanceHandle currentInstance , InstanceHandle notUsed , CHAR *commandLineArguments , int howToShow)
{
	// glut initialization
	int argc = 1;
	char *dummy = "Mark III";
	char **argv = &dummy;
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Free-Curve to Line convertion");
	glutFullScreen();
	
	// application initialization
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	multiplier = 1.0e6 / freq.QuadPart;

	thisInstance = currentInstance;

	// OpenGL initialization
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1,0,1);

	// main loop
	glutIdleFunc(initialize);
	glutMainLoop();
	return 0;
} // end function WinMain