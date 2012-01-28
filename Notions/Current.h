#ifndef CURRENT_H
#define CURRENT_H

// includes
#include <Color.h>
#include <Space-Time/Vector2D.h>
#include "event handlers.h"

class Current
{
	friend void Conversion::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);					// mouseLeftUp
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Creation::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Creation::mouseleftUp(const EventDispatcher &, double);						// mouseLeftUp
	friend void Creation::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Navigation::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Navigation::mouseleftUp(const EventDispatcher &, double);					// mouseLeftUp
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Selection::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Selection::mouseleftUp(const EventDispatcher &, double);					// mouseLeftUp
	friend void Selection::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Configuration::mouseMove(const EventDispatcher &, double);					// mouseMove
	friend void Configuration::mouseleftUp(const EventDispatcher &, double);				// mouseLeftUp
	friend void Configuration::mouseleftDown(const EventDispatcher &, double);				// mouseLeftDown

	//friend void defaultPainter(const EventDispatcher & , double);							// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);						// defaultPainter
	friend inline void displayCursor();														// displayCursor
	friend int WINAPI WinMain(InstanceHandle,InstanceHandle,CHAR *,int);					// WinMain
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Current()																	// Current default constructor
		:cursor(0,0)
	{
		// do nothing
	} // end Current default constructor

	inline ~Current()																	// Current destructor
	{
		// empty body
	} // end Current destructor


private:

	inline Current(const Current &original)												// Current copy constructor
		:cursor(original.cursor),lineColor(original.lineColor),
		fillColor(original.fillColor),curveColor(original.curveColor),
		lineWidth(original.lineWidth),curveWidth(original.curveWidth)
	{
		// empty body
	} // end Current copy constructor



	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/


	/***************
	* data members *
	***************/

	Vector2D<> cursor;
	RGBA::Color<> lineColor;
	RGBA::Color<> fillColor;
	RGBA::Color<> curveColor;
	double lineWidth;
	double curveWidth;

}; // end class Current

#endif // CURRENT_H