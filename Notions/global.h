// library includes
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <fstream>
using std::ofstream;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <algorithm>
using std::copy;
using std::for_each;
using std::transform;
using std::max_element;
using std::min_element;
using std::find_if;
using std::sort;

#include <numeric>
using std::accumulate;
using std::adjacent_difference;

#include <iterator>
using std::back_inserter;
using std::ostream_iterator;

#include <functional>
using std::less;
using std::greater;
using std::less_equal;

#include <utility>
using std::pair;

#include <cstdlib>
using std::exit;

#include <cstring>
using std::memcpy;

#include <cmath>
using std::sqrt;
using std::fabs;
using std::floor;
using std::atan;
using std::tan;

#include <ctime>
using std::clock;

#include <exception>
using std::exception;

#include <gl/glut.h>

#include <windows.h>

// #defines
#define PI 3.141592653589793
#define NO_POINTS 0
#define PLAIN_POINTS 1
#define COLORED_POINTS_DISCRETE 2
#define COLORED_POINTS_CONTINUOUS 3

// used includes
#include "Statistics.h"
#include "Triple.h"
#include "Comparer.h"
#include "templates.h"
#include "PolyLine.h"
#include "Stroke.h"



// extern declarations for global variables.
extern vector<Triple> freePoints;
extern vector<Triple> velocities;
extern vector<GLdouble> velocity_magnitudes;

extern vector<Statistics> line_stats;
extern vector<Triple> line_segments;

extern vector<PolyLine> polyLines;
extern vector<Stroke> strokes;

extern unsigned int windowWidth;
extern unsigned int windowHeight;
extern double multiplier;
extern const GLdouble relative_threshold;

extern int selected;	// remember to set to -1 when a polyLine is deleted!

extern unsigned char point_layer_status;
extern bool line_segment_layer_status;
extern bool line_strip_layer_status;
extern bool grid_layer_status;

extern GLdouble angle_step;
extern GLdouble intercept_step;


//extern ofstream velocity_magnitudes_file;
//extern ostream_iterator<GLdouble> outIter;

// prototypes
Triple getSpeed(const Triple &final , const Triple &initial);
GLdouble getMagnitude(const Triple &vector);
Statistics *add_to_sums(Statistics *statPtr , const Triple &point);
Triple getIntersectionPoint(const Statistics &firstLine , const Statistics &secondLine);
void snap_to_grid(Statistics &stats);
void printLine(Statistics &stats);
Triple dummy_project(const Triple &point , const Statistics &line);	// TODO: replace with actual projection function
bool lessTriple(const Triple &left , const Triple &right);
bool check_intersecting(const Triple &intersection , const Triple &seg_1_out , const Triple &seg_1_in , const Triple &seg_2_in , const Triple &seg_2_out);
bool check_parallel(const Triple &seg_1_out , const Triple &seg_1_in , const Triple &seg_2_in , const Triple &seg_2_out);
