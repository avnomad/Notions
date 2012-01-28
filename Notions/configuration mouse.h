#include "event handlers.h"
#include "global variables.h"
#include "utility.h"

namespace Configuration
{
	void mouseleftDown(const EventDispatcher &dispatcher, double time)						// mouseleftDown
	{

	} // end function mouseleftDown


	void mouseleftUp(const EventDispatcher &dispatcher, double time)						// mouseleftUp
	{

	} // end function mouseleftUp


	void mouseMove(const EventDispatcher &dispatcher, double time)							// mouseMove
	{
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;

		current.cursor = unproject(current.cursor);
	} // end function mouseMove


}; // end namespace Configuration
