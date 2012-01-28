#ifndef CENTER_SOCKET_H
#define CENTER_SOCKET_H

#include "Socket.h"

struct CenterSocket : public Socket
{
	/***************************
	* contructors & destructor *
	***************************/

	inline CenterSocket()																					// CenterSocket default constructor
	{
		// do nothing
	} // end CenterSocket default constructor


	inline CenterSocket(const CenterSocket &original)														// CenterSocket copy constructor
		:Socket(original)
	{
		// empty body
	} // end CenterSocket copy constructor


	inline CenterSocket(const Vector2D<> &point,double width,const Color<> &color, bool mark = false)		// CenterSocket constructor
		:Socket(point,width,color,mark)
	{
		// empty body
	} // end CenterSocket constructor


	inline CenterSocket(double x,double y,double width,const Color<> &color, bool mark = false)				// CenterSocket constructor
		:Socket(x,y,width,color,mark)
	{
		// empty body
	} // end CenterSocket constructor


	virtual ~CenterSocket()																					// CenterSocket destructor
	{
		// empty body
	} // end CenterSocket destructor



	/************
	* operators *
	************/

	virtual CenterSocket &operator = (const CenterSocket &original)											// operator =
	{
		Socket::operator =(original);
		return *this;
	} // end function operator =



	/*******************
	* member functions *
	*******************/

	virtual Vector2D<> &position()																		// position
	{
		parent->evaluateCenter();
		list<Plug *>::iterator begin = childs.begin();
		list<Plug *>::iterator end = childs.end();
		while(begin != end)
		{
			if((*begin)->permanent)
				(*begin)->Vector2D::operator =(*this);
			++begin;
		} // end while
		return *this;
	} // end function position


	virtual CenterSocket *clone() const																	// clone
	{
		return new CenterSocket(*this);
	} // end function clone



	/***************
	* data members *
	***************/

}; // end class CenterSocket

#endif // CENTER_SOCKET_H