
#include <cmath>
#include <graphics/glut window.h>
#include <graphics/OpenGL engine.h>
#include <direct input/DirectInput Wrapper.h>
#include <direct input/mouse and keyboard/EventDispatcher.h>
#include <windows/common.h>
#include <CPU clock.h>

#include "global variables.h"
#include "event handlers.h"

int WINAPI WinMain(InstanceHandle currentInstance , InstanceHandle PreviusInstance , CHAR *commandLineArguments , int windowMode)
{
	// create core components
	GLUT::Window window("notions");	// window
	correction.x = window.getWidth()/2;					// store these values in a global variable
	correction.y = window.getHeight()/2;				// for later use by the event handlers.
	correction.maxY = window.getHeight()-1;
	DirectInput directInput(currentInstance);	// direct input
	MouseAndKeyboard::EventDispatcher dispatcher(directInput);	// event dispatcher
	OpenGL::Engine engine(-correction.x , correction.x-1 , -correction.y , correction.y-1);	// open GL

	// change viewport
		// not needed at this time because the input device and the screen have the same size.

	// prepare input devices
	dispatcher.mouse.setCooperativeLevel(window.getHandle(),DISCL_EXCLUSIVE|DISCL_FOREGROUND);
	dispatcher.mouse.setBufferSize(100).acquire();
	dispatcher.initializeClock();	// get the first time outside the loop
	dispatcher.keyboard.setCooperativeLevel(window.getHandle(),DISCL_NONEXCLUSIVE|DISCL_BACKGROUND);
	dispatcher.keyboard.setBufferSize(100).acquire();

	dispatcher.setLocalMouseBuffer().setLocalKeyboardBuffer();	// set dispatcher buffers to the sizes of device buffers

	// initialize input device state
	dispatcher.mouse.absolute.x = correction.x;
	dispatcher.mouse.absolute.y = correction.y;
	dispatcher.mouse.X = 0;
	dispatcher.mouse.Y = 0;
	dispatcher.mouse.Z = 0;
	memset(dispatcher.mouse.button,0,sizeof(dispatcher.mouse.button));
	memset(dispatcher.keyboard.key,0,sizeof(dispatcher.keyboard.key));

	// compile display lists
	DisplayLists displayLists;	// for some reason glGenLists doesn't work for global objects
	::displayLists = &displayLists;	// so we make use of yet another trick...
	double temp = sqrt((double)window.getWidth()*window.getWidth()+window.getHeight()*window.getHeight());
	displayLists.grid.compile(10,temp);
	temp = std::min(window.getWidth(),window.getHeight()) / 2;	// the values used in gluOrtho2D should be used.
	displayLists.rotationIndicator.compile(0.85*temp,0.95*temp);

	// set initial event handlers
	paint = defaultPainter;
	dispatcher.key[DIK_ESCAPE].down = escape;
	Conversion::setHandlers(dispatcher);

	// set initial drawing settings
	current.curveColor = khaki;
	current.curveWidth = 1;
	current.lineColor = gold;
	current.fillColor = 0.5*green;
	current.fillColor.setAlpha(0.25);
	current.lineWidth = 1;


	//shapes.shapes.push_back(new LineStrip(1,gold));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(50,50,1,red));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(150,100,1,red));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(150,50,1,red));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(250,70,1,red));

	//shapes.shapes.push_back(new LineStrip(1,green));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(-50,-50,1,red));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(-150,-100,1,red));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(-150,-50,1,red));
	//dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(-250,-70,1,red));

	//LineLoop *p;
	//shapes.regions.push_back(p = new LineLoop(1,orange));
	//Socket *s1,*s2,*s3,*s4,*s5;
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s1 = &(new Socket(75,120,1,red))->setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s2 = &(new Socket(120,75,1,red))->setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s3 = &(new Socket(75,75,1,red))->setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s4 = &(new Socket(120,120,1,red))->setParent(p));

	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s1).setParent(p));

	//dynamic_cast<LineLoop *>(shapes.regions.back())->center = &(new CenterSocket(135,135,1,red))->setParent(p);

	//shapes.regions.push_back(p = new LineLoop(1,silver));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s1 = &(new Socket(-75,-120,1,red))->setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s2 = &(new Socket(-120,-75,1,red))->setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s3 = &(new Socket(-120,-120,1,red))->setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s4 = &(new Socket(-75,-75,1,red))->setParent(p));

	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	//dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s1).setParent(p));

	//dynamic_cast<LineLoop *>(shapes.regions.back())->center = &(new CenterSocket(135,135,1,red))->setParent(p);


	//shapes.regions.push_back(p = new ConvexPolygon(1,cyan));
	//p->setFillColor(blue).fillColor.setAlpha(0.7);
	//p->vertices.push_back(s1 = &(new Socket(0,200,1,red))->setParent(p));
	//p->vertices.push_back(s2 = &(new Socket(200,200,1,red))->setParent(p));
	//p->vertices.push_back(s3 = &(new Socket(250,300,1,red))->setParent(p));
	//p->vertices.push_back(s4 = &(new Socket(100,400,1,red))->setParent(p));
	//p->vertices.push_back(s5 = &(new Socket(-50,300,1,red))->setParent(p));

	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s5).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s5).setRight(s1).setParent(p));

	//p->center = &(new CenterSocket(135,135,1,red))->setParent(p);


	//shapes.regions.push_back(p = new ConvexPolygon(1,gold));
	//p->setFillColor(0.4*green).fillColor.setAlpha(0.5);
	//p->vertices.push_back(s1 = &(new Socket(0,-200,1,red))->setParent(p));
	//p->vertices.push_back(s2 = &(new Socket(-200,-200,1,red))->setParent(p));
	//p->vertices.push_back(s3 = &(new Socket(-250,-300,1,red))->setParent(p));
	//p->vertices.push_back(s4 = &(new Socket(-100,-400,1,red))->setParent(p));
	//p->vertices.push_back(s5 = &(new Socket(50,-300,1,red))->setParent(p));

	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s5).setParent(p));
	//p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s5).setRight(s1).setParent(p));

	//p->center = &(new CenterSocket(135,135,1,red))->setParent(p);

	// enter main loop
	while(1)
	{
		dispatcher.execute();
		paint(dispatcher,CPUclock::currentTime());
	} // end while
} // end function WinMain
