#ifndef CORRECTION_H
#define CORRECTION_H

#include <Space-Time/Vector2D.h>
#include "event handlers.h"

class Correction : private Vector2D<>
{
	friend void displayNavigationGUI();														// displayNavigationGUI

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
	//friend void navigationPainter(const EventDispatcher &, double);						// navigationPainter
	friend void suspendProjectionMatrix();													// suspendProjectionMatrix
	friend void displayGUI();																// displayGUI
	friend int WINAPI WinMain(InstanceHandle , InstanceHandle , CHAR * , int );				// WinMain
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Correction()																// Correction default constructor
	{
		// empty body
	} // end Correction default constructor


	inline ~Correction()															// Correction destructor
	{
		// empty body
	} // end Correction destructor


private:

	inline Correction(const Correction &original)									// Correction copy constructor
		:Vector2D(original)
	{
		// empty body
	} // end Correction copy constructor



	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/
	/***************
	* data members *
	***************/

	double maxY;
}; // end class Correction

#endif // CORRECTION_H