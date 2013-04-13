//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

#ifndef LINE_STRIP_H
#define LINE_STRIP_H

// includes
#include <list>
using std::list;
#include "Vertex.h"
#include <Space-Time/LineSegment2D.h>
#include <Graphics/glVertex2.h>
#include <algorithms.h>

struct LineStrip : public Shape
{
	/***************************
	* contructors & destructor *
	***************************/

	inline LineStrip()																						// LineStrip default constructor
	{
		// do nothing
	} // end LineStrip default constructor


	inline LineStrip(const LineStrip &original)																// LineStrip copy constructor
		:Shape(original)
	{
		setVertices(original.vertices);
	} // end LineStrip copy constructor


	inline LineStrip(double width , const Color<> &color , bool mark = false)								// LineStrip constructor
		:Shape(width,color,mark)
	{
		// empty body
	} // end LineStrip constructor


	virtual ~LineStrip()																					// LineStrip destructor
	{
		deleteVertices();
	} // end LineStrip destructor




	/************
	* operators *
	************/

	virtual LineStrip &operator = (const LineStrip &original)												// operator =
	{
		Shape::operator =(original);
		setVertices(original.vertices);
		return *this;
	} // end function operator =


	/*******************
	* member functions *
	*******************/

	inline LineStrip &deleteVertices()																		// deleteVertices
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


	inline LineStrip &setVertices(const list<Vertex *> &lineStripVertices)									// setVertices
	{
		deleteVertices();	// delete old vertices
		// and make new ones
		list<Vertex *>::const_iterator begin = lineStripVertices.begin();
		list<Vertex *>::const_iterator end = lineStripVertices.end();
		while(begin != end)
		{
			vertices.push_back((*begin)->clone());
			++begin;
		} // end while
		return *this;
	} // end function setVertices



	virtual LineStrip &display()																			// display
	{
		if(marked)
		{
			// bold line
			glColor(lineColor.negative());
			glLineWidth(lineWidth*2);
			glBegin(GL_LINE_STRIP);
				execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			glEnd();
		} // end if

		// normal line
		glColor(lineColor);
		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
			execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
		glEnd();

		if(marked)
		{
			// bold points
			glColor(lineColor);
			glPointSize(lineWidth*3);
			glBegin(GL_POINTS);
				execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			glEnd();
		} // end if

		// marked points
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::display);

		return *this;
	} // end function display


	virtual LineStrip &display(double zoom)																	// display
	{
		if(marked)
		{
			// bold line
			glColor(lineColor.negative());
			glLineWidth(lineWidth*2*zoom);
			glBegin(GL_LINE_STRIP);
				execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			glEnd();
		} // end if

		// normal line
		glColor(lineColor);
		glLineWidth(lineWidth*zoom);
		glBegin(GL_LINE_STRIP);
			execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
		glEnd();

		if(marked)
		{
			// bold points
			glColor(lineColor);
			glPointSize(lineWidth*3*zoom);
			glBegin(GL_POINTS);
				execute_indirect(vertices.begin(),vertices.end(),&Vertex::note);
			glEnd();
		} // end if

		// marked points
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::display);

		return *this;
	} // end function display


	virtual LineStrip &move(const Vector2D<> &displacement)													// move
	{															// must have a least 2 elements.
		list<Vertex *>::iterator begin = vertices.begin();
		if(!(dynamic_cast<Plug *>(*begin) && dynamic_cast<Plug *>(vertices.back()) &&
			((Plug *)*begin)->permanent && ((Plug *)vertices.back())-> permanent &&
				((Plug *)*begin)->parent->parent == ((Plug *)vertices.back())->parent->parent))
					(*begin)->move(displacement);
		++begin;
		execute_indirect(begin,vertices.end(),&Vertex::move,displacement);
		return *this;
	} // end function move


	virtual LineStrip &moveDisconnect(const Vector2D<> &displacement)										// moveDisconnect
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::moveDisconnect,displacement);
		return *this;
	} // end function moveDisconnect


	virtual Vertex *nearVertex(const Vector2D<> &point , double distance2)									// nearVertex
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


	virtual pair nearEdge(const Vector2D<> &point , double distance2)										// nearEdge
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
		return pair(nullptr,nullptr);
	} // end function nearEdge


	virtual LineStrip *clone() const																		// clone
	{
		return new LineStrip(*this);
	} // end function clone


	virtual LineStrip &work()																				// work
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::work);
		return *this;
	} // end function work


	virtual LineStrip &rest()																				// rest
	{
		execute_indirect(vertices.begin(),vertices.end(),&Vertex::rest);
		return *this;
	} // end function rest



	/***************
	* data members *
	***************/

	std::list<Vertex *> vertices;

}; // end class LineStrip

#endif // LINE_STRIP_H