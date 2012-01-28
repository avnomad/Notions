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

#ifdef DEBUG
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <iomanip>
using std::setw;
using std::setprecision;

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