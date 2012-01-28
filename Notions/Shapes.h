#ifndef SHAPES_H
#define SHAPES_H

// includes
#include <Digitizing/Stroke.h>
#include <list>
#include "event handlers.h"

class Shapes
{
	/*temp*/friend int WINAPI WinMain(InstanceHandle,InstanceHandle,CHAR *,int);	// WinMain
	friend void Selection::mouseleftDown(const EventDispatcher &, double);			// mouseleftDown
	friend Socket *findSocket(const Vector2D<> &);									// findSocket
	friend Socket *initialFindSocket(const Vector2D<> &, double);					// initialFindSocket
	friend void Creation::mouseleftDown(const EventDispatcher &, double);			// mouseleftDown
	friend void Creation::mouseleftUp(const EventDispatcher &, double);				// mouseleftUp
	friend void Creation::mouseMove(const EventDispatcher &, double);				// mouseMove
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);			// mouseleftDown
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);			// mouseleftUp
	friend void Conversion::mouseMove(const EventDispatcher &, double);				// mouseMove
	//friend void defaultPainter(const EventDispatcher & , double);					// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);				// navigationPainter
	friend void displayShapes();													// displayShapes
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Shapes()																// Shapes default constructor
	{
		// do nothing
	} // end Shapes default constructor


	inline ~Shapes()															// Shapes destructor
	{
		// empty body
	} // end Shapes destructor

private:

	inline Shapes(const Shapes &original)										// Shapes copy constructor
		:strokes(original.strokes),shapes(original.shapes),
		regions(original.regions),currentStroke(original.currentStroke)
	{
		// empty body
	} // end Shapes copy constructor


	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/


	/***************
	* data members *
	***************/

	std::list<Stroke<> *> strokes;
	std::list<Shape *> shapes;
	std::list<Region *> regions;
	Stroke<> currentStroke;

}; // end class Shapes

#endif // SHAPES_H