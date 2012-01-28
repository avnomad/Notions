#ifndef STATE_H
#define STATE_H

#include "event handlers.h"

enum Mode { CONVERSION,CREATION,NAVIGATION,SELECTION,CONFIGURATION };

class State
{
	friend inline void displayCursor();																// displayCursor
	friend void displayShapes();																	// displayShapes
	friend void displayGUI();																		// displayGUI

	friend void Creation::mouseMove(const EventDispatcher &, double);								// mouseMove
	friend void Creation::mouseleftUp(const EventDispatcher &, double);								// mouseLeftUp
	friend void Creation::mouseleftDown(const EventDispatcher &, double);							// mouseLeftDown
	friend void Conversion::mouseMove(const EventDispatcher &, double);								// mouseMove
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);							// mouseleftUp
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);							// mouseleftDown

	friend void Conversion::leftDown(const EventDispatcher &dispatcher, double time);				// leftDown
	friend void Conversion::rightDown(const EventDispatcher &dispatcher, double time);				// rightDown
	friend void Conversion::upDown(const EventDispatcher &dispatcher, double time);					// upDown
	friend void Conversion::downDown(const EventDispatcher &dispatcher, double time);				// downDown
	friend void Conversion::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown

	friend void Creation::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown
	friend void Navigation::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown
	friend void Selection::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown
	friend void Configuration::enterDown(const EventDispatcher &dispatcher, double time);			// enterDown

	friend void Creation::upDown(const EventDispatcher &dispatcher, double time);					// leftDown
	friend void Navigation::rightDown(const EventDispatcher &dispatcher, double time);				// rightDown
	friend void Selection::downDown(const EventDispatcher &dispatcher, double time);				// upDown
	friend void Configuration::leftDown(const EventDispatcher &dispatcher, double time);			// downDown

	friend void Creation::upUp(const EventDispatcher &dispatcher, double time);						// leftUp
	friend void Navigation::rightUp(const EventDispatcher &dispatcher, double time);				// rightUp
	friend void Selection::downUp(const EventDispatcher &dispatcher, double time);					// upUp
	friend void Configuration::leftUp(const EventDispatcher &dispatcher, double time);				// downUp
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline State()																	// default constructor
		:mode(CONVERSION),locked(false),stroking(false)
	{
		// empty body.
	} // end State dafault constructor


	inline ~State()																	// destructor
	{
		// do nothing
	} // end ~State destructor

private:

	inline State(const State &original)												// copy constructor
		:mode(original.mode),locked(original.locked),stroking(original.stroking)
	{
		// empty body
	} // end State copy constructor


	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/


	/***************
	* data members *
	***************/

	Mode mode;
	bool locked;
	bool stroking;
}; // end class State

#endif // STATE_H
