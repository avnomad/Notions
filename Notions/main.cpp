// #includes:
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
using std::clog;

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

#include <cstring>
using std::memset;

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


#include <Direct Input/DirectInput Wrapper.h>
#include <Graphics/SquareGrid.h>
#include <Graphics/RotationIndicator.h>
#include <exceptions/Exceptions.h>
#include <Direct Input/mouse and keyboard/EventDispatcher.h>
#include <Space-Time/Line2D.h>
#include <graphics/glut window.h>
#include <graphics/OpenGL engine.h>
#if DISPLAY_STRINGS
#include <algorithms.h>
#endif

#include <vector>
using std::vector;
#include <list>
using std::list;

#if LOGGING
#include <fstream>
using std::ofstream;
#endif

#include <algorithm>
using std::min_element;
using std::max_element;
using std::min;

#include <numeric>
using std::adjacent_difference;
using std::accumulate;

#if LOGGING
#include <iterator>
using std::back_inserter;
using std::ostream_iterator;

ofstream output("mean.txt");
#endif


vector<Vector2D<> > points;
int width;
int height;

struct ProgramState
{
	Vector2D<> cursor;
	Vector2D<> oldCursor;
#if LOGGING
	vector<double> times;
	list<double> periods;
#endif
	double angle;
	double side;
	SquareGrid<> *grid;
	RotationIndicator *rotationIndicator;
	unsigned int n;
	bool writting;
	bool valid;
} state; // end struct ProgramState


using namespace MouseAndKeyboard;

void escape(const EventDispatcher &dispatcher,double)
{
#if LOGGING
	adjacent_difference(state.times.begin(),state.times.end(),back_inserter(state.periods));
	if(state.times.size())
		state.periods.pop_front();
	double average = accumulate(state.periods.begin(),state.periods.end(),0)/(double)state.periods.size();
	double min = *min_element(state.periods.begin(),state.periods.end());
	double max = *max_element(state.periods.begin(),state.periods.end());
	output<<"\n\naverage period: "<<average<<'\n';
	output<<"min period: "<<min<<'\n';
	output<<"max period: "<<max<<endl;
	output.close();
	system("start mean.txt");
#endif
	exit(0);
}


void move(const EventDispatcher &dispatcher,double time)
{
	state.cursor.setX(dispatcher.mouse.absolute.x).setY(height-1-dispatcher.mouse.absolute.y);
#if LOGGING
	state.times.push_back(time);
	output<<setw(10)<<dispatcher.mouse.X<<setw(10)<<dispatcher.mouse.Y<<setw(15)<<time
		<<setw(10)<<(int)dispatcher.mouse.button[0]<<setw(10)<<(int)dispatcher.mouse.button[1]
		<<setw(10)<<(int)dispatcher.mouse.button[2]<<endl;
#endif
	if(state.oldCursor == state.cursor)	// may be true due to some problems with the library
		return;

	if(state.writting)
		points.push_back(state.cursor);
	if(state.valid)
	{
		state.angle += (180/PI)*((state.oldCursor-Vector2D<>(width/2,height/2))^(state.cursor-Vector2D<>(width/2,height/2)));
	} // end if
	state.oldCursor = state.cursor;
} // end function move


void leftDown(const EventDispatcher &dispatcher,double time)
{
	if(state.rotationIndicator->over(state.cursor-Vector2D<>(width/2,height/2)))
	{
		state.valid = true;
	}
	else
	{
		points.push_back(state.cursor);
		state.writting = true;
	} // end else
} // end function leftDown


void leftUp(const EventDispatcher &dispatcher,double time)
{
	state.valid = false;
	state.writting = false;
} // end function leftUp



// main
int main(int argc , char **argv)
{
#if LOGGING
	output<<setprecision(0)<<std::fixed;
	output<<setw(10)<<"mouse X"<<setw(10)<<"mouse Y"<<setw(15)<<"time"
		<<setw(10)<<"button 0"<<setw(10)<<"button 1"
		<<setw(10)<<"button 2"<<endl;
#endif
	try
	{
#if LOGGING
		if(!output) throw RuntimeError("A CannotOpenFile","std","ofstream::ofstream","Could not open file!");
#endif
		GLUT::Window mainWindow("display lists");
		width = mainWindow.getWidth();
		height = mainWindow.getHeight();
		OpenGL::Engine engine(0,width,0,height);

		Line2D<> l;
		Line2D<> la;
		Line2D<> lc;
		Vector2D<> center;

#if DISPLAY_STRINGS
		ostringstream convert;
		std::string hello("Hello World!");
		std::string buff;
#endif

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
		state.cursor.setX(width/2).setY(height/2);
		state.oldCursor.setX(width/2).setY(height/2);
		state.angle = 0;
		state.valid = false;
		state.writting = false;
		state.side = sqrt((double)(width*width+height*height));
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
		RotationIndicator rotationIndicator(0.381*min(width,height),0.43*min(width,height));
		state.grid = &grid;
		state.rotationIndicator = &rotationIndicator;

		// set initial OpenGL state
		glViewport(0,0,width,height);
		glMatrixMode(GL_MODELVIEW);

		// main loop
		while(1)
		{
			eventDispatcher.execute();

			// paint
			glClear(GL_COLOR_BUFFER_BIT);

			glLoadIdentity();

#if DISPLAY_SQUARE
			glBegin(GL_LINE_LOOP);
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
			glEnd();
#endif

			// grid
			glLineWidth(0.5);
			glTranslated(width/2,height/2,0);
			glRotated(state.angle,0,0,1);
			glColor4f(0,0.2,0.2,1);	// dark cyan
			grid.call();

			// free-form curve
			glLoadIdentity();
			glLineWidth(0.125);
			glColor4f(1,0,1,1);	// purple
			glBegin(GL_LINE_STRIP);
			for(unsigned int c = 0 ; c < points.size() ; ++c)
				glVertex2dv(points[c]);
			glEnd();

			// line(s)
			glLineWidth(0.5);
			if(points.size() > 1)
			{
				center = l.setTo(points);	// will throw if points.size() < 2 or points[0] == ... == points[points.size()-1]

				// display 'best' line approximating the points in points vector.
				glColor4f(0,1,0,1);	// lime
				glBegin(GL_LINES);
				if(closerToHorizontal(l))
				{
					glVertex2d(0,l.getY(0));
					glVertex2d(width,l.getY(width));
				}
				else
				{
					glVertex2d(l.getX(0),0);
					glVertex2d(l.getX(height),height);
				} // end else
				glEnd();

				l.roundAngle(PI/12,center);

				// display line with its slope rounded to closest multiple of PI/12
				glColor4f(0,1,1,1);	// cyan
				glBegin(GL_LINES);
				if(closerToHorizontal(l))
				{
					glVertex2d(0,l.getY(0));
					glVertex2d(width,l.getY(width));
				}
				else
				{
					glVertex2d(l.getX(0),0);
					glVertex2d(l.getX(height),height);
				} // end else
				glEnd();

				l.roundC(state.n);

				// display line with its intercept rounded to grid cell size
				glColor4f(1,1,0,1);	// yellow
				glBegin(GL_LINES);
				if(closerToHorizontal(l))
				{
					glVertex2d(0,l.getY(0));
					glVertex2d(width,l.getY(width));
				}
				else
				{
					glVertex2d(l.getX(0),0);
					glVertex2d(l.getX(height),height);
				} // end else
				glEnd();
			} // end if

#if DISPLAY_STRINGS
			// Hello
			glLineWidth(1.0);			
			glColor4f(1,1,0,1);
			displayString(state.cursor,20,1,45,hello.begin(),hello.end());
#endif

			// rotation indicator
			glTranslated(width/2,height/2,0);
			glRotated(state.angle,0,0,1);
			glColor4f(1,1,1,0.2);
			rotationIndicator.call();

#if DISPLAY_STRINGS
			// number in center
			glColor4f(1,1,0,1);
			convert.str("");
			//convert<<stringLenght(hello.begin(),hello.end())*0.1;
			convert<<glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char *)"Hello World!")*0.1;
			buff = convert.str();
			displayString(Vector2D<>(0,0),20,1,45,buff.begin(),buff.end());
#endif

			// cursor
			glLoadIdentity();
			glTranslated(state.cursor.x,state.cursor.y,0);
			glColor4f(0,0,1,1);	// blue
			gluDisk(SOLID,0,2,10,1);

			mainWindow.swapBuffers();
		} // end while		
	} // end try
#undef e
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
