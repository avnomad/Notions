void defaultPainter(const EventDispatcher &dispatcher , double time)					// defaultPainter
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
	restoreProjectionMatrix();

	// cursor
	glMatrixMode(GL_MODELVIEW);
	displayCursor();


	glLoadIdentity();
	glutSwapBuffers();
} // end function defaultPainter