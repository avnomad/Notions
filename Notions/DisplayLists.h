#ifndef DISPLAY_LISTS_H
#define DISPLAY_LISTS_H

// includes
#include <graphics/RotationIndicator.h>
#include <graphics/SquareGrid.h>

#include <direct input/mouse and keyboard/EventDispatcher.h>
using namespace MouseAndKeyboard;

class DisplayLists
{
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);			// mouseleftDown
	//friend void defaultPainter(const EventDispatcher & , double);					// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);				// navigationPainter
	friend void displayGrid();														// displayGrid
	friend void displayNavigationGUI();												// displayNavigationGUI
	friend int WINAPI WinMain(InstanceHandle,InstanceHandle,CHAR *,int);			// WinMain
public:

	/***************************
	* contructors & destructor *
	***************************/

	DisplayLists()																	// default constructor
	{
		// do nothing
	} // end DisplayLists default constructor


	inline ~DisplayLists()															// destructor
	{
		// do nothing
	} // end ~DisplayLists destructor


private:

	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/



	/***************
	* data members *
	***************/

	SquareGrid<> grid;
	RotationIndicator rotationIndicator;

}; // end class DisplayLists

#endif // DISPLAY_LISTS_H
