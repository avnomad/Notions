//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

// includes
#include "global.h"

// global variables.
vector<Triple> freePoints;
vector<Triple> velocities;
vector<GLdouble> velocity_magnitudes;

vector<Statistics> line_stats;
vector<Triple> line_segments;

unsigned int windowWidth = 768;
unsigned int windowHeight = 970;
double multiplier;
GLdouble max;
GLdouble min;
GLdouble threshold;
const GLdouble relative_threshold = 0.20;

#if LOGGING
ofstream velocity_magnitudes_file("velocity_magnitudes.txt");
ostream_iterator<GLdouble> outIter(velocity_magnitudes_file,"\n");
#endif
