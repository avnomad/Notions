#ifndef SHAPE_H
#define SHAPE_H

// includes
#include <Color.h>
using namespace RGBA;
#include <utility>
#include <Space-Time/Vector2D.h>

struct Vertex;
typedef std::pair<Vertex *,Vertex *> pair;

struct Shape
{
	/***************************
	* contructors & destructor *
	***************************/

	inline Shape()																						// Shape default constructor
	{
		// do nothing
	} // end Shape default constructor


	inline Shape(const Shape &original)																	// Shape copy constructor
		:lineColor(original.lineColor),lineWidth(original.lineWidth),marked(original.marked)
	{
		// empty body
	} // end Shape copy constructor


	inline Shape(double width , const Color<> &color , bool mark = false)								// Shape constructor
		:lineColor(color),lineWidth(width),marked(mark)
	{
		// empty body
	} // end Shape constructor


	virtual ~Shape()																					// Shape destructor
	{
		// empty body
	} // end Shape destructor



	/************
	* operators *
	************/

	virtual Shape &operator = (const Shape &original)													// operator =
	{
		lineColor = original.lineColor;
		lineWidth = original.lineWidth;
		marked = original.marked;
		return *this;
	} // end function operator =



	/*******************
	* member functions *
	*******************/

	inline Shape &setLineWidth(double width)															// setLineWidth
	{
		lineWidth = width;
		return *this;
	} // end function setLineWidth


	inline Shape &setLineColor(const Color<> &color)													// setLineColor
	{
		lineColor = color;
		return *this;
	} // end function setLineColor


	inline Shape &setMarked(bool mark)																	// setMarked
	{
		marked = mark;
		return *this;
	} // end function setMarked


	virtual Shape &display() = 0;																		// display
	virtual Shape &display(double zoom) = 0;															// display
	virtual Shape &move(const Vector2D<> &displacement) = 0;											// move
	virtual Shape &moveDisconnect(const Vector2D<> &displacement) = 0;									// moveDisconnect
	virtual Vertex *nearVertex(const Vector2D<> &point , double distance2) = 0;							// nearVertex
	virtual pair nearEdge(const Vector2D<> &point , double distance2) = 0;								// nearEdge
	virtual Shape *clone() const = 0;																	// clone

	virtual Shape &work()																				// work
	{
		return *this;
	} // end function work


	virtual Shape &rest()																				// rest
	{
		return *this;
	} // end function rest



	/***************
	* data members *
	***************/

	Color<> lineColor;
	double lineWidth;
	bool marked;

}; // end class Shape

#endif // SHAPE_H