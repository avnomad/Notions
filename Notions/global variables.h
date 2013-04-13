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

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// includes
#include "paint.h"
#include "State.h"
#include "Shapes.h"
#include "Current.h"
#include "Converter.h"
#include "Navigator.h"
#include "Transform.h"
#include "Correction.h"
#include "DisplayLists.h"
#include <Color/namings/double precision colors.h>
#include <graphics/glut window.h>

#include <iomanip>
using std::setw;
using std::setprecision;

#ifdef DEBUG
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

extern ofstream output;
#endif

// extern declarations
extern Paint paint;
extern State state;
extern Shapes shapes;
extern Current current;
extern Converter converter;
extern Navigator navigator;
extern Transform transform;
extern Correction correction;
extern DisplayLists *displayLists;

#endif // GLOBAL_VARIABLES_H
