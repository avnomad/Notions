#include "event handlers.h"
#include "global variables.h"

namespace Conversion
{
							/************
							* key press *
							************/

	void leftDown(const EventDispatcher &dispatcher, double time)						// leftDown
	{
		state.mode = CONFIGURATION;
		Configuration::setHandlers(dispatcher);
	} // end function leftDown


	void rightDown(const EventDispatcher &dispatcher, double time)						// rightDown
	{
		state.mode = NAVIGATION;
		paint.iPaint = navigationPainter;
		Navigation::setHandlers(dispatcher);
	} // end function rightDown


	void upDown(const EventDispatcher &dispatcher, double time)							// upDown
	{
		state.mode = CREATION;
		Creation::setHandlers(dispatcher);
	} // end function upDown


	void downDown(const EventDispatcher &dispatcher, double time)						// downDown
	{
		state.mode = SELECTION;
		Selection::setHandlers(dispatcher);
	} // end function downDown


	void enterDown(const EventDispatcher &dispatcher, double time)						// enterDown
	{
		state.locked = !state.locked;
	} // end function enterDown


							/**************
							* key release *
							**************/

	void leftUp(const EventDispatcher &dispatcher, double time)								// leftUp
	{
		// stay
	} // end function leftUp


	void rightUp(const EventDispatcher &dispatcher, double time)							// rightUp
	{
		// stay
	} // end function rightUp


	void upUp(const EventDispatcher &dispatcher, double time)								// upUp
	{
		// stay
	} // end function upUp


	void downUp(const EventDispatcher &dispatcher, double time)								// downUp
	{
		// stay
	} // end function downUp


	void enterUp(const EventDispatcher &dispatcher, double time)							// enterUp
	{
		// stay
	} // end function enterUp


}; // end namespace Conversion
