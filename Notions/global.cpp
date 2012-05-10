//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

vector<Triple> line_segments;

vector<PolyLine> polyLines;
vector<Stroke> strokes;

unsigned int windowWidth = 768;
unsigned int windowHeight = 970;
double multiplier;
const GLdouble relative_threshold = 0.15;

int selected = -1;

unsigned char point_layer_status = NO_POINTS;
bool line_segment_layer_status = 0;
bool line_strip_layer_status = 1;
bool grid_layer_status = 1;

const GLdouble angle_step = PI/4;
const GLdouble intercept_step = 10.0;


#if LOGGING
ofstream velocity_magnitudes_file("velocity_magnitudes.txt");
ostream_iterator<GLdouble> outIter(velocity_magnitudes_file,"\n");
#endif
