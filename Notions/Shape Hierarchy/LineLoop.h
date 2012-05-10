//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Notions.
 *
 *	Notions is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Notions is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Notions.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LINE_LOOP_H
#define LINE_LOOP_H

#include "Region.h"
#include "Socket.h"

struct LineLoop : public Region
{
	/***************************
	* contructors & destructor *
	***************************/

	inline LineLoop()																					// LineLoop default constructor
	{
		// do nothing
	} // end LineLoop default constructor


	inline LineLoop(const LineLoop &original)															// LineLoop copy constructor
		:Region(original)
	{
		setVertices(original.vertices);
		setSockets(original.sockets);
		setCenter(original.center->clone());
	} // end LineLoop copy constructor


	inline LineLoop(double width, const Color<> &color, bool mark = false)								// LineLoop constructor
		:Region(width,color,mark)
	{
		// empty body
	} // end LineLoop constructor


	virtual ~LineLoop()																					// LineLoop destructor
	{
		deleteCenter();
		deleteSockets();
		deleteVertices();
	} // end LineLoop destructor



	/************
	* operators *
	************/

	virtual LineLoop &operator = (const LineLoop &original)												// operator =
	{
		Region::operator =(original);
		setCenter(original.center->clone());
		setVertices(original.vertices);
		setSockets(original.sockets);
		return *this;
	} // end function operator =



	/*******************
	* member functions *
	*******************/

	inline LineLoop &deleteVertices()																	// deleteVertices
	{
		list<Vertex *>::iterator begin = vertices.begin();
		list<Vertex *>::iterator end = vertices.end();
		while(begin != end)
		{
			delete *begin;
			++begin;
		} // end while
		vertices.clear();
		return *this;
	} // end function deleteVertices


	inline LineLoop &setVertices(const list<Vertex *> &lineLoopVertices)								// setVertices
	{
		deleteVertices();	// delete old vertices
		// and make new ones
		list<Vertex *>::const_iterator begin = lineLoopVertices.begin();
		list<Vertex *>::const_iterator end = lineLoopVertices.end();
		while(begin != end)
		{
			vertices.push_back((*begin)->clone());
			++begin;
		} // end while
		return *this;
	} // end function setVertices


	inline LineLoop &deleteSockets()																	// deleteSockets
	{
		list<Socket *>::iterator begin = sockets.begin();
		list<Socket *>::iterator end = sockets.end();
		while(begin != end)
		{
			delete *begin;
			++begin;
		} // end while
		sockets.clear();
		return *this;
	} // end function deleteSockets


	inline LineLoop &setSockets(const list<Socket *> &lineLoopSockets)									// setSockets
	{
		deleteSockets();	// delete old sockets
		// and make new ones
		list<Socket *>::const_iterator begin = lineLoopSockets.begin();
		list<Socket *>::const_iterator end = lineLoopSockets.end();
		while(begin != end)
		{
			sockets.push_back((*begin)->clone());
			++begin;
		} // end while
		return *this;
	} // end function setSockets


	inline LineLoop &setCenter(Socket *centerSocket)													// setCenter
	{
		center = centerSocket;
		return *this;
	} // end function setCenter


	inline LineLoop &deleteCenter()																		// deleteCenter
	{
		delete center;
		return *this;
	} // end function deleteCenter



	virtual LineLoop &display()																			// display
	{
		if(marked)
		{
			// bold line
			glColor(lineColor.negative());
			glLineWidth(lineWidth*2);
			glBegin(GL_LINE_LOOP);
				execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			glEnd();
		} // end if

		// normal line
		glColor(lineColor);
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
			execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
		glEnd();

		// bold points
		glColor(lineColor);
		glPointSize(lineWidth*3);
		glBegin(GL_POINTS);
			execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			execute_indirect(sockets.begin(),sockets.end(),&Vertex::note);
			center->note();
		glEnd();

		// marked points
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::display);
		execute_indirect(sockets.begin(),sockets.end(),&Vertex::display);
		center->display();

		Region::display();
		return *this;
	} // end function display


	virtual LineLoop &display(double zoom)																// display
	{
		if(marked)
		{
			// bold line
			glColor(lineColor.negative());
			glLineWidth(lineWidth*2*zoom);
			glBegin(GL_LINE_LOOP);
				execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			glEnd();
		} // end if

		// normal line
		glColor(lineColor);
		glLineWidth(lineWidth*zoom);
		glBegin(GL_LINE_LOOP);
			execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
		glEnd();

		// bold points
		glColor(lineColor);
		glPointSize(lineWidth*3*zoom);
		glBegin(GL_POINTS);
			execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			execute_indirect(sockets.begin(),sockets.end(),&Vertex::note);
			center->note();
		glEnd();

		// marked points
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::display);
		execute_indirect(sockets.begin(),sockets.end(),&Vertex::display);
		center->display();

		Region::display(zoom);
		return *this;
	} // end function display


	virtual LineLoop &move(const Vector2D<> &displacement)												// move
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::move,displacement);
		Region::move(displacement);
		return *this;
	} // end function move


	virtual LineLoop &moveDisconnect(const Vector2D<> &displacement)									// moveDisconnect
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::moveDisconnect,displacement);
		Region::move(displacement);
		return *this;
	} // end function moveDisconnect


	virtual Vertex *nearVertex(const Vector2D<> &point , double distance2)								// nearVertex
	{
		list<Vertex *>::iterator begin = vertices.begin();
		list<Vertex *>::iterator end = vertices.end();
		while(begin != end)
		{
			if((*begin)->nearVertex(point,distance2))
				return *begin;
			++begin;
		} // end while
		return 0;
	} // end function nearVertex


	virtual pair nearEdge(const Vector2D<> &point , double distance2)									// nearEdge
	{
		if(vertices.size() < 2) return pair(nullptr,nullptr);

		list<Vertex *>::iterator begin = vertices.begin();
		list<Vertex *>::iterator old = vertices.begin();
		list<Vertex *>::iterator end = vertices.end();
		while(++begin != end)
		{
			if(inRange(point,(*old)->position(),(*begin)->position(),distance2))
				return pair(*old,*begin);
			++old;
		} // end while
		if(inRange(point,*vertices.front(),*vertices.back(),distance2))
			return pair(vertices.front(),vertices.back());
		return pair(nullptr,nullptr);
	} // end function nearEdge


	virtual LineLoop *clone() const																		// clone
	{
		return new LineLoop(*this);
	} // end function clone


	virtual LineLoop &work()																			// work
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::work);
		execute_indirect(sockets.begin(),sockets.end(),&Vertex::work);
		center->work();
		return *this;
	} // end function work


	virtual LineLoop &rest()																			// rest
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::rest);
		execute_indirect(sockets.begin(),sockets.end(),&Vertex::rest);
		center->rest();
		return *this;
	} // end function rest


	virtual Socket *nearSocket(const Vector2D<> &point , double distance2)								// nearSocket
	{
		list<Vertex *>::iterator vBegin = vertices.begin();
		list<Vertex *>::iterator vEnd = vertices.end();
		while(vBegin != vEnd)
		{
			if(dynamic_cast<Socket *>(*vBegin))
				if((*vBegin)->nearVertex(point,distance2))
					return static_cast<Socket *>(*vBegin);
			++vBegin;
		} // end while
		list<Socket *>::iterator sBegin = sockets.begin();
		list<Socket *>::iterator sEnd = sockets.end();
		while(sBegin != sEnd)
		{
			if((*sBegin)->nearVertex(point,distance2))
				return *sBegin;
			++sBegin;
		} // end while
		
		return dynamic_cast<Socket *>(center->nearVertex(point,distance2));
	} // end function nearSocket


	virtual Socket *initialNearSocket(const Vector2D<> &point , double distance2)						// initialNearSocket
	{
		double min_distance2 = distance2;
		Socket *closest_socket = 0;
		list<Vertex *>::iterator vBegin = vertices.begin();
		list<Vertex *>::iterator vEnd = vertices.end();
		while(vBegin != vEnd)
		{
			if(dynamic_cast<Socket *>(*vBegin))
				if((distance2 = (**vBegin - point).norm2()) < min_distance2)
				{
					closest_socket = static_cast<Socket *>(*vBegin);
					min_distance2 = distance2;
				}
			++vBegin;
		} // end while
		list<Socket *>::iterator sBegin = sockets.begin();
		list<Socket *>::iterator sEnd = sockets.end();
		while(sBegin != sEnd)
		{
			if((distance2 = (**sBegin - point).norm2()) < min_distance2)
			{
				closest_socket = *sBegin;
				min_distance2 = distance2;
			}
			++sBegin;
		} // end while

		if((distance2 = (*center - point).norm2()) < min_distance2)
		{
			closest_socket = center;
			//min_distance2 = distance2;
		}

		return closest_socket;
	} // end function initialNearSocket


	virtual LineLoop &evaluateCenter()																	// evaluateCenter
	{
		Vector2D<> sum(0,0);
		list<Vertex *>::iterator begin = vertices.begin();
		list<Vertex *>::iterator end = vertices.end();
		while(begin != end)
		{
			sum += **begin;
			++begin;
		} // end while

		center->Vector2D::operator =(sum / vertices.size());
		return *this;
	} // end function evaluateCenter



	/***************
	* data members *
	***************/

	Socket *center;
	list<Vertex *> vertices;
	list<Socket *> sockets;

}; // end class LineLoop

#endif // LINE_LOOP_H