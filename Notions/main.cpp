//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Notions.
 *
 *	Notions is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Notions is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Notions.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>
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
	GLUT::Window window("notions");
	correction.x = window.getWidth()/2;					// store these values in a global variable
	correction.y = window.getHeight()/2;				// for later use by the event handlers.
	correction.maxY = window.getHeight()-1;
	DirectInput directInput(currentInstance);	// direct input
	MouseAndKeyboard::EventDispatcher dispatcher(directInput);	// event dispatcher
	OpenGL::Engine engine(-correction.x , correction.x-1 , -correction.y , correction.y-1);	// open GL

	// change viewport
	glViewport(0,0,window.getWidth(),window.getHeight());

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
#if TABLET
	dispatcher.assumeDigitizer(correction.x,correction.y,window.getWidth(),window.getHeight());
#endif

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

#if START_WITH_CONTENT
	shapes.shapes.push_back(new LineStrip(1,gold));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(50,50,1,red));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(150,100,1,red));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(150,50,1,red));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(250,70,1,red));

	shapes.shapes.push_back(new LineStrip(1,green));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(-50,-50,1,red));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(-150,-100,1,red));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Vertex(-150,-50,1,red));
	dynamic_cast<LineStrip *>(shapes.shapes.back())->vertices.push_back(new Plug(-250,-70,1,red));

	LineLoop *p;
	shapes.regions.push_back(p = new LineLoop(1,orange));
	Socket *s1,*s2,*s3,*s4,*s5;
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s1 = &(new Socket(75,120,1,red))->setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s2 = &(new Socket(120,75,1,red))->setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s3 = &(new Socket(75,75,1,red))->setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s4 = &(new Socket(120,120,1,red))->setParent(p));

	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s1).setParent(p));

	dynamic_cast<LineLoop *>(shapes.regions.back())->center = &(new CenterSocket(135,135,1,red))->setParent(p);

	shapes.regions.push_back(p = new LineLoop(1,silver));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s1 = &(new Socket(-75,-120,1,red))->setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s2 = &(new Socket(-120,-75,1,red))->setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s3 = &(new Socket(-120,-120,1,red))->setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->vertices.push_back(s4 = &(new Socket(-75,-75,1,red))->setParent(p));

	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	dynamic_cast<LineLoop *>(shapes.regions.back())->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s1).setParent(p));

	dynamic_cast<LineLoop *>(shapes.regions.back())->center = &(new CenterSocket(135,135,1,red))->setParent(p);


	shapes.regions.push_back(p = new ConvexPolygon(1,cyan));
	p->setFillColor(blue).fillColor.setAlpha(0.7);
	p->vertices.push_back(s1 = &(new Socket(0,200,1,red))->setParent(p));
	p->vertices.push_back(s2 = &(new Socket(200,200,1,red))->setParent(p));
	p->vertices.push_back(s3 = &(new Socket(250,300,1,red))->setParent(p));
	p->vertices.push_back(s4 = &(new Socket(100,400,1,red))->setParent(p));
	p->vertices.push_back(s5 = &(new Socket(-50,300,1,red))->setParent(p));

	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s5).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s5).setRight(s1).setParent(p));

	p->center = &(new CenterSocket(135,135,1,red))->setParent(p);


	shapes.regions.push_back(p = new ConvexPolygon(1,gold));
	p->setFillColor(0.4*green).fillColor.setAlpha(0.5);
	p->vertices.push_back(s1 = &(new Socket(0,-200,1,red))->setParent(p));
	p->vertices.push_back(s2 = &(new Socket(-200,-200,1,red))->setParent(p));
	p->vertices.push_back(s3 = &(new Socket(-250,-300,1,red))->setParent(p));
	p->vertices.push_back(s4 = &(new Socket(-100,-400,1,red))->setParent(p));
	p->vertices.push_back(s5 = &(new Socket(50,-300,1,red))->setParent(p));

	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s1).setRight(s2).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s2).setRight(s3).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s3).setRight(s4).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s4).setRight(s5).setParent(p));
	p->sockets.push_back(&(new EdgeSocket(75,120,1,red))->setLeft(s5).setRight(s1).setParent(p));

	p->center = &(new CenterSocket(135,135,1,red))->setParent(p);
#endif

	// enter main loop
	MSG message;
	while(1/*GetMessage(&message,nullptr,0,0)*/)
	{
		dispatcher.execute();
		paint(dispatcher,CPUclock::currentTime());
		window.swapBuffers();
	} // end while
} // end function WinMain
