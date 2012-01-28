#ifndef CONVERTER_H
#define CONVERTER_H

#include <sstream>
using std::ostringstream;
#include <string>
#include "event handlers.h"

class Converter
{
	// friend declarations
	friend void displayNavigationGUI();													// displayNavigationGUI
	friend void displayGUI();															// displayGUI
	//friend void defaultPainter(const EventDispatcher & , double);						// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);					// navigationPainter
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Converter()															// default constructor
	{
		// do nothing
	} // end Converter default constructor


	inline ~Converter()															// destructor
	{
		// do nothing
	} // end ~Converter destructor

private:

	/***************
	* data members *
	***************/

	ostringstream stream;
	std::string string;
}; // end class Converter

#endif // CONVERTER_H
