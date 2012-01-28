#include "event handlers.h"
#include "global variables.h"

namespace Creation
{
							/************
							* key press *
							************/

	void leftDown(const EventDispatcher &dispatcher, double time)						// leftDown
	{

	} // end function leftDown


	void rightDown(const EventDispatcher &dispatcher, double time)						// rightDown
	{

	} // end function rightDown


	void upDown(const EventDispatcher &dispatcher, double time)							// upDown
	{
		if(state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
	} // end function upDown


	void downDown(const EventDispatcher &dispatcher, double time)						// downDown
	{

	} // end function downDown


	void enterDown(const EventDispatcher &dispatcher, double time)						// enterDown
	{
		if(state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
		state.locked = !state.locked;
	} // end function enterDown


							/**************
							* key release *
							**************/

	void leftUp(const EventDispatcher &dispatcher, double time)								// leftUp
	{

	} // end function leftUp


	void rightUp(const EventDispatcher &dispatcher, double time)							// rightUp
	{

	} // end function rightUp


	void upUp(const EventDispatcher &dispatcher, double time)								// upUp
	{
		if(!state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
	} // end function upUp


	void downUp(const EventDispatcher &dispatcher, double time)								// downUp
	{

	} // end function downUp


	void enterUp(const EventDispatcher &dispatcher, double time)							// enterUp
	{
		// stay
	} // end function enterUp


}; // end namespace Creation
