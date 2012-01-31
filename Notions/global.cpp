// includes
#include "global.h"

// global variables.
vector<Triple> freePoints;

vector<Triple> line_segments;

vector<PolyLine> polyLines;
vector<Stroke> strokes;

unsigned int windowWidth = 1280;
unsigned int windowHeight = 1024;
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
