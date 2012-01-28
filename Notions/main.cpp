// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// #includes:
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <cstdlib>
using std::system;
using std::exit;

#include <cmath>
using std::sin;
using std::cos;
using std::tan;
using std::asin;
using std::acos;
using std::atan;
using std::sqrt;
using std::fabs;
using std::ceil;

#include <sstream>
using std::ostringstream;
using std::istringstream;
using std::stringstream;




#include <gl/glut.h>

#include <Direct Input/DirectInput Wrapper.h>
#include <Direct Input/Keyboard Wrapper.h>
#include <Direct Input/Mouse Wrapper.h>
#include <windows/common.h>
#include <Graphics/DisplayList.h>
#include <Graphics/SquareGrid.h>
#include <Graphics/QuadricSurfaceDescriptor.h>
#include <Graphics/RotationIndicator.h>
#include <Space-Time/Vector3D.h>
#include <Space-Time/TimePoint.h>
#include <exceptions/Exceptions.h>
#include <Direct Input/Device Wrapper.h>
#include <Color.h>
#include <Direct Input/mouse and keyboard/EventDispatcher.h>
#include <algorithms.h>
#include <Space-Time/Line2D.h>
#include <graphics/glut window.h>
#include <graphics/OpenGL engine.h>


#include <vector>
using std::vector;
#include <list>
using std::list;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <algorithm>
using std::min_element;

#include <numeric>
using std::adjacent_difference;
using std::accumulate;
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;
using std::back_inserter;


// protorypes
void outputBitmap(int x, int y, const char *string);
void outputStroke(GLfloat x, GLfloat y, const char *text);


//ofstream output("c:/output/mean.txt");
vector<Vector2D<> > points;


struct ProgramState
{
	Vector2D<> cursor;
	Vector2D<> oldCursor;
	vector<double> times;
	list<double> periods;
	double angle;
	double side;
	SquareGrid<> *grid;
	RotationIndicator *rotationIndicator;
	unsigned int n;
	bool writting;
	bool valid;
} state; // end struct ProgramState


//void sizeThrower(int width , int height)					// sizeThrower
//{
//	throw std::pair<int,int>(width,height);
//} // end function sizeThrower
//
//
//void intTrower(){throw 0;}										// intTrower

using namespace MouseAndKeyboard;

void escape(const EventDispatcher &dispatcher,double)
{
	adjacent_difference(state.times.begin(),state.times.end(),back_inserter(state.periods));
	state.periods.pop_front();
	double average = accumulate(state.periods.begin(),state.periods.end(),0)/(double)state.periods.size();
	//double min = *min_element(state.periods.begin(),state.periods.end());

	//output<<"\n\n"<<average<<endl;
	//output.close();
	//system("start c:/output/mean.txt");
	exit(0);
}


void move(const EventDispatcher &dispatcher,double time)
{
	state.cursor.setX(dispatcher.mouse.absolute.x).setY(1023-dispatcher.mouse.absolute.y);
	state.times.push_back(time);
	if(state.writting)
		points.push_back(state.cursor);
	//output<<setw(10)<<dispatcher.mouse.X<<setw(10)<<dispatcher.mouse.Y<<setw(15)<<time<<
	//	setw(2)<<(int)dispatcher.mouse.button[0]<<setw(2)<<(int)dispatcher.mouse.button[1]<<setw(2)<<(int)dispatcher.mouse.button[2]<<endl;

	if(state.valid && state.oldCursor != state.cursor)
	{
		state.angle += (180/PI)*((state.oldCursor-Vector2D<>(640,512))^(state.cursor-Vector2D<>(640,512)));
		state.oldCursor = state.cursor;
	} // end if
} // end function move


void leftDown(const EventDispatcher &dispatcher,double time)
{
	points.push_back(state.cursor);
	state.writting = true;
	//state.grid->compile(++state.n,state.side);
	if(state.rotationIndicator->over(state.cursor-Vector2D<>(640,512)))
	{
		state.valid = true;
		state.oldCursor = state.cursor;
	} // end if
} // end function leftDown


void leftUp(const EventDispatcher &dispatcher,double time)
{
	state.valid = false;
	state.writting = false;
} // end function leftUp



// main
int main(int argc , char **argv)
{
	//output<<setprecision(0)<<std::fixed;
	try
	{
		//if(!output) throw RuntimeError("A CannotOpenFile","std","ofstream::ofstream","Could not open file!");
		GLUT::Window mainWindow("display lists");
		OpenGL::Engine engine(0,1280,0,1024);

		Line2D<> l;
		Line2D<> la;
		Line2D<> lc;
		Vector2D<> center;

		ostringstream convert;
		std::string hello("Hello World!");
		std::string buff;

		// input devices
		DirectInput directInput(GetModuleHandle(NULL));
		EventDispatcher eventDispatcher(directInput);

		// prepare input devices
		eventDispatcher.mouse.setCooperativeLevel(mainWindow.getHandle(),DISCL_EXCLUSIVE|DISCL_FOREGROUND);
		eventDispatcher.mouse.setBufferSize(100).acquire();
		eventDispatcher.initializeClock();
		eventDispatcher.keyboard.setCooperativeLevel(mainWindow.getHandle(),DISCL_NONEXCLUSIVE|DISCL_BACKGROUND);
		eventDispatcher.keyboard.setBufferSize(100).acquire();

		eventDispatcher.setLocalMouseBuffer().setLocalKeyboardBuffer();

		// set initial state
		state.cursor.setX(0).setY(0);
		state.oldCursor.setX(0).setY(0);
		state.angle = 0;
		state.valid = false;
		state.writting = false;
		state.side = sqrt(1280.0*1280+1024*1024);
		state.n = 10;
		eventDispatcher.mouse.Z = 0;
		memset(eventDispatcher.mouse.button,0,sizeof(eventDispatcher.mouse.button));
		memset(eventDispatcher.keyboard.key,0,sizeof(eventDispatcher.keyboard.key));
		
		// set event handlers
		eventDispatcher.key[DIK_ESCAPE].down = escape;
		eventDispatcher.button[0].down = leftDown;
		eventDispatcher.button[0].up = leftUp;
		eventDispatcher.motion = move;


		// create DisplayLists
		SquareGrid<> grid(state.n,state.side);
		RotationIndicator rotationIndicator(390,440);
		state.grid = &grid;
		state.rotationIndicator = &rotationIndicator;

		// set initial OpenGL state
		glClearColor(0,0,0,0);		// clear color


		glMatrixMode(GL_MODELVIEW);

		while(1)
		{
			eventDispatcher.execute();

			// paint
			glClear(GL_COLOR_BUFFER_BIT);

			glLoadIdentity();

			/*glBegin(GL_LINE_LOOP);
			glColor4f(0,0,1,1);
			glVertex2d(100,100);
			glColor4f(0,0,1,0);
			glVertex2d(500,100);
			glColor4f(0,0,1,1);
			glVertex2d(500,500);
			glColor4f(0,0,1,0);
			glVertex2d(100,500);
			glEnd();

			glBegin(GL_TRIANGLE_FAN);
			glColor4f(1,0,0,1);
			glVertex2d(300,300);
			glColor4f(1,0,0,0);
			glVertex2d(100,100);
			glVertex2d(500,100);
			glVertex2d(500,500);
			glVertex2d(100,500);
			glVertex2d(100,100);
			glEnd();*/

			// grid
			
			glLineWidth(0.5);
			glTranslated(640,512,0);
			glRotated(state.angle,0,0,1);
			glColor4f(0,0.2,0.2,1);
			grid.call();

			// points
			glLoadIdentity();
			glLineWidth(0.125);
			glColor4f(1,0,1,1);
			glBegin(GL_LINE_STRIP);
			for(unsigned int c = 0 ; c < points.size() ; ++c)
				glVertex2dv(points[c]);
			glEnd();

			// line
			glLineWidth(0.5);
			if(points.size() > 1)
			{
				center = l.setTo(points);
				glColor4f(0,1,0,1);
				glBegin(GL_LINES);
				if(closerToHorizontal(l))
				{
					glVertex2d(0,l.getY(0));
					glVertex2d(1280,l.getY(1280));
				}
				else
				{
					glVertex2d(l.getX(0),0);
					glVertex2d(l.getX(1024),1024);
				} // end else
				glEnd();
			} // end if

			//// line angle
			//if(points.size() > 1)
			//{
			//	l.roundAngle(PI/12,center);
			//	glColor4f(0,1,1,1);
			//	glBegin(GL_LINES);
			//	if(closerToHorizontal(l))
			//	{
			//		glVertex2d(0,l.getY(0));
			//		glVertex2d(1280,l.getY(1280));
			//	}
			//	else
			//	{
			//		glVertex2d(l.getX(0),0);
			//		glVertex2d(l.getX(1024),1024);
			//	} // end else
			//	glEnd();
			//} // end if

			//// line C
			//if(points.size() > 1)
			//{
			//	l.roundC(state.n);
			//	glColor4f(1,1,0,1);
			//	glBegin(GL_LINES);
			//	if(closerToHorizontal(l))
			//	{
			//		glVertex2d(0,l.getY(0));
			//		glVertex2d(1280,l.getY(1280));
			//	}
			//	else
			//	{
			//		glVertex2d(l.getX(0),0);
			//		glVertex2d(l.getX(1024),1024);
			//	} // end else
			//	glEnd();
			//} // end if

			// Hello
			glLineWidth(1.0);			
			glColor4f(1,1,0,1);
			displayString(state.cursor,0.1,0.1,45,hello.begin(),hello.end());

			// rotation indicator
			glTranslated(640,512,0);
			glRotated(state.angle,0,0,1);
			glColor4f(1,1,1,0.2);
			rotationIndicator.call();

			// number in center
			//glColor4f(1,1,0,1);
			//convert.str("");
			////convert<<stringLenght(hello.begin(),hello.end())*0.1;
			//convert<<glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char *)"Hello World!")*0.1;
			//buff = convert.str();
			//displayString(Vector2D<>(0,0),0.1,0.1,45,buff.begin(),buff.end());

			// cursor
			glLoadIdentity();
			glTranslated(state.cursor.x,state.cursor.y,0);
			glColor4f(0,0,1,1);
			gluDisk(SOLID,0,2,10,1);

			glutSwapBuffers();
		} // end while		
	} // end try
	catch(DivideByZeroException &e)
	{
		ExceptionMessageBox(e,e,"Divide by Zero Exception:");
	} // end catch
	catch(RuntimeError &e)
	{
		ExceptionMessageBox(e,e,"Runtime Error:");
	} // end catch
	catch(OutOfRange &e)
	{
		ExceptionMessageBox(e,e,"Out of Range:");
	} // end catch
	catch(InvalidArgument &e)
	{
		ExceptionMessageBox(e,e,"Invalid Argument:");
	} // end catch
	catch(LogicError &e)
	{
		ExceptionMessageBox(e,e,"Logic Error:");
	} // end catch
	return 0;
} // end function main
