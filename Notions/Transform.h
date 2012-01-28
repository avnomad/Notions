#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <gl/glut.h>
#include <Space-Time/Vector2D.h>
#include "event handlers.h"

class Transform
{
	friend void Creation::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);					// mouseleftUp
	//friend void defaultPainter(const EventDispatcher &, double);							// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);						// defaultPainter
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Navigation::mouseleftUp(const EventDispatcher &, double);					// mouseleftUp
	friend void Navigation::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void displayShapes();															// displayShapes
	friend void displayGUI();																// displayGUI
	friend void displayNavigationGUI();														// displayNavigationGUI
	friend inline void displayCursor();														// displayCursor
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Transform()																				// default constructor
		:displacement(0,0),rotation(0),zoom(1),zoomAngle(0)
	{
		// empty body
	} // end Transform default constructor


	inline ~Transform()																				// destructor
	{
		// do nothing
	} // end ~Transform destructor

private:

	inline Transform(const Transform &original)														// copy constructor
		:displacement(original.displacement),rotation(original.rotation),
		zoom(original.zoom),zoomAngle(original.zoomAngle)
	{
		// empty body
	} // end Transform copy constructor



	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/

	inline void apply()																				// apply
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPushMatrix();
		glScaled(zoom,zoom,1);
		glRotated(rotation,0,0,1);
		glTranslated(displacement.x,displacement.y,0);
	} // end function apply



	/***************
	* data members *
	***************/

	Vector2D<> displacement;
	double rotation;	// in degrees!
	double zoom;
	double zoomAngle;	// in degrees!

}; // end class Transform

#endif // TRANSFORM_H
