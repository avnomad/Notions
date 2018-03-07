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

#pragma warning(disable : 4996)

#include "event handlers.h"
#include "global variables.h"
#include <algorithms.h>
#include <gl/glut.h>


void suspendProjectionMatrix()									// suspendProjectionMatrix
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-correction.x,correction.x-1,-correction.y,correction.y-1);
} // end function suspendProjectionMatrix


inline void restoreProjectionMatrix()							// restoreProjectionMatrix
{
	glPopMatrix();
} // end function restoreProjectionMatrix


void displayShapes()											// displayShapes
{
	// strokes
	execute_indirect(shapes.regions.begin(),shapes.regions.end(),&Region::display,transform.zoom);
	execute_indirect(shapes.shapes.begin(),shapes.shapes.end(),&Shape::display,transform.zoom);
	execute_indirect(shapes.strokes.begin(),shapes.strokes.end(),&Stroke<>::displayPoints,transform.zoom);
	if(state.stroking && state.mode == CONVERSION)
		shapes.currentStroke.displayPoints(transform.zoom);
} // end function displayShapes


void displayGrid()												// displayGrid
{
	static RGBA::Color<> color = 0.1*cyan;

	// grid	
	glLineWidth(0.25);
	glColor(color);
	glDisable(GL_LINE_SMOOTH);
	displayLists->grid.call();
	glEnable(GL_LINE_SMOOTH);
} // end function displayGrid


inline void displayCursor()										// displayCursor
{
	glTranslated(current.cursor.x,current.cursor.y,0);
	if(state.mode == CREATION)
	{
		glColor(current.curveColor);
		gluDisk(SOLID,0,current.curveWidth/transform.zoom,60,3);
	}
	else
	{
		glColor(current.lineColor);
		gluDisk(SOLID,0,current.lineWidth/transform.zoom,60,3);
	} // end else
} // end function displayCursor


#include <utility.h>

void displayNavigationGUI()										// displayNavigationGUI
{
	// colors
	static RGBA::Color<> color = whiteSmoke;
	color.setAlpha(0.5);
	static RGBA::Color<> angleColor = green;
	angleColor.setAlpha(0.1);

	// dimensions
	double min = std::min(correction.x,correction.y);
	double range = (2-Fi)*min;
	static double coefficient = 2;
	double angle = fmod(fabs(transform.rotation)+180,360) - 180;
	double unit = correction.maxY / 102.4;
	double sign;
	Vector2D<> stringPosition;

	if(fabs(angle)*(Pi/180)*range < 3*unit)
	{
		sign = 1;
		stringPosition.x = range+unit;
		stringPosition.y = -2*unit;
	}
	else
	{
		stringPosition.x = (range+unit)*cos((Pi/360)*angle);
		stringPosition.y = (range+unit)*sin((Pi/360)*angle);
		sign = -1;
	} // end else

	if(transform.rotation < 0)
	{
		angle = -angle;
		stringPosition.y = -stringPosition.y;
	} // end if
	stringPosition.y -= 0.4*unit;

	if(angle > 0) sign = -sign;
	
	// x axis and arrow
	glColor(green);
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2d(0,0);
		glVertex2d(min,0);
		glVertex2d(range,0);
		glVertex2d(range-unit/2,sign*unit);
		glVertex2d(range,0);
		glVertex2d(range+unit/2,sign*unit);
	glEnd();

	// angle (surface)
	glColor(angleColor);
	gluPartialDisk(SOLID,0,min,coefficient*fabs(angle),1,90,-angle);

	// angle (line)
	glColor(green);
	gluPartialDisk(SILHOUETTE,0,range,coefficient*fabs(angle),1,90,-angle);

	// number
	converter.stream.str("");
	std::ios_base::fmtflags flags = converter.stream.flags();	// save the old converter format.
	converter.stream << std::fixed << setprecision(1) << angle;
	converter.string = converter.stream.str();
	displayString(stringPosition,1.5*unit,1,0,converter.string.begin(),converter.string.end());
	converter.stream.flags(flags);	// restore the old converter format.

	// movable axis and arrow
	glRotated(transform.rotation,0,0,1);	// rotate step 1
	glBegin(GL_LINES);
		glVertex2d(0,0);
		glVertex2d(min,0);
		glVertex2d(range,0);
		glVertex2d(range-unit/2,-sign*unit);
		glVertex2d(range,0);
		glVertex2d(range+unit/2,-sign*unit);
	glEnd();

	// rotation indicator
	glRotated(transform.zoomAngle,0,0,1);	// rotate step 2
	glColor(color);
	displayLists->rotationIndicator.call();
} // end function displayNavigationGUI


#include <cstring>
#include <ctime>
#include <iomanip>
using std::setw;
using std::setprecision;

void displayGUI()												// displayGUI
{
	// state names
	static const char *const modeBegins[5] = {"conversion","creation","navigation","selection","configuration"};
	static const char *const modeEnds[5] = {modeBegins[0]+strlen(modeBegins[0]),modeBegins[1]+strlen(modeBegins[1]),
		modeBegins[2]+strlen(modeBegins[2]),modeBegins[3]+strlen(modeBegins[3]),modeBegins[4]+strlen(modeBegins[4])};
	static const char *const lockBegins[2] = {"unlocked","locked"};
	static const char *const lockEnds[2] = {lockBegins[0]+strlen(lockBegins[0]),lockBegins[1]+strlen(lockBegins[1])};

	// sizes
	double unit = correction.maxY / 102.4;

	// positions
	const Vector2D<> modePosition(52*unit,48*unit);
	const Vector2D<> lockPosition(52*unit,46*unit);
	const Vector2D<> timePosition(45*unit,-50*unit);
	const Vector2D<> zoomPosition(45*unit,48*unit);

	// colors
	static RGBA::Color<> modeColor(0.5,0.5,0.75,0.9);
	static RGBA::Color<> timeColor = yellow;
	static RGBA::Color<> zoomColor = lavender;

	// temporaries
	const char *dateAndTime;
	time_t rawTime;

	// set transparencies
	timeColor.setAlpha(0.9);
	zoomColor.setAlpha(0.9);

	// display state
	glLineWidth(2);
	glColor(modeColor);
	displayString(modePosition,2*unit,1,0,modeBegins[state.mode],modeEnds[state.mode]);
	displayString(lockPosition,2*unit,1,0,lockBegins[state.locked],lockEnds[state.locked]);

	// display zoom
	converter.stream.str("");
	converter.stream<<setprecision(2)<<transform.zoom<<'x';
	converter.string = converter.stream.str();
	glColor(zoomColor);
	displayString(zoomPosition,1.5*unit,1,0,converter.string.begin(),converter.string.end());

	// display time
	glColor(timeColor);
	std::time(&rawTime);
	dateAndTime = asctime(localtime(&rawTime));
	displayString(timePosition,1.5*unit,1,0,dateAndTime,dateAndTime+strlen(dateAndTime));
} // end function displayGUI
