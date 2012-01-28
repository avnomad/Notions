#pragma warning(disable : 4996)

#include "event handlers.h"
#include "global variables.h"
void navigationPainter(const EventDispatcher &dispatcher , double time)					// navigationPainter
{
	// clear buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// grid
	suspendProjectionMatrix();
	displayGrid();
	restoreProjectionMatrix();

	// shapes
	glMatrixMode(GL_MODELVIEW);
	displayShapes();

	// GUI
	suspendProjectionMatrix();
	displayGUI();
	displayNavigationGUI();
	restoreProjectionMatrix();

	// cursor
	glMatrixMode(GL_MODELVIEW);
	displayCursor();


	glLoadIdentity();
	glutSwapBuffers();
} // end function navigationPainter