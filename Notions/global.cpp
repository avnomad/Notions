// includes
#include "global.h"

// global variables.
vector<Triple> freePoints;
vector<Triple> velocities;
vector<GLdouble> velocity_magnitudes;

vector<Statistics> line_stats;
vector<Triple> line_segments;
//vector<Triple> line_strip;

unsigned int windowWidth = 768;
unsigned int windowHeight = 970;
double multiplier;
GLdouble max;
GLdouble min;
GLdouble threshold;
GLdouble relative_threshold = 0.20;

//ofstream velocity_magnitudes_file("velocity_magnitudes.txt");
//ostream_iterator<GLdouble> outIter(velocity_magnitudes_file,"\n");
