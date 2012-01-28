#ifndef PAINT_H
#define PAINT_H

// includes
#include "event handlers.h"

class Paint
{
	typedef void (*PainterType)(const EventDispatcher &,double);

	friend int WINAPI WinMain(InstanceHandle,InstanceHandle,CHAR *,int);
	friend void Navigation::rightDown(const EventDispatcher &, double);					// rightDown
	friend void Navigation::rightUp(const EventDispatcher &, double);					// rightUp
	friend void Navigation::enterDown(const EventDispatcher &, double);					// enterDown
	friend void Conversion::rightDown(const EventDispatcher &, double);					// rightDown
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Paint()															// default constructor
	{
		// do nothing
	} // end Paint default constructor


	inline ~Paint()															// destructor
	{
		// do nothing
	} // end ~Paint destructor

private:

	inline Paint(const Paint &original)										// copy constructor
		:iPaint(original.iPaint)
	{
		// empty body
	} // end Paint copy constructor


	/************
	* operators *
	************/

	inline Paint &operator = (PainterType painter)							// operator =
	{
		iPaint = painter;
		return *this;
	} // end function operator =


	inline Paint &operator = (const Paint &original)						// operator =
	{
		iPaint = original.iPaint;
		return *this;
	} // end function operator =


	inline operator PainterType () const									// cast operator
	{
		return iPaint;
	} // end function cast operator


	/*******************
	* member functions *
	*******************/

	/***************
	* data members *
	***************/

	PainterType iPaint;

}; // end class Paint

#endif // PAINT_H
