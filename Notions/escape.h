#include "event handlers.h"
#include <cstdlib>
using std::exit;

void escape(const EventDispatcher &,double)						// escape
{
	exit(0);
} // end function escape
