#include "global variables.h"

#ifdef DEBUG
ofstream output("c:/output/log.txt");
#endif

Paint paint;
State state;
Shapes shapes;
Current current;
Converter converter;
Navigator navigator;
Transform transform;
Correction correction;
DisplayLists *displayLists = 0;
GLUT::Window window("notions");