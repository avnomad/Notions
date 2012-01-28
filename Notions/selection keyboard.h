#include "event handlers.h"
#include "global variables.h"

namespace Selection
{
	extern bool locked;
	extern std::pair<Shape *,Shape *> part;
	extern Shape *wholeShape;


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
		if(locked)
		{
			if(part.first)
				part.first->moveDisconnect(Vector2D<>(0,0));
			if(part.second && !(dynamic_cast<Plug *>(part.first) && dynamic_cast<Plug *>(part.second) &&
				((Plug *)part.first)->permanent && ((Plug *)part.second)-> permanent &&
				((Plug *)part.first)->parent->parent == ((Plug *)part.second)->parent->parent))
					part.second->moveDisconnect(Vector2D<>(0,0));
		} // end if
	} // end function upDown


	void downDown(const EventDispatcher &dispatcher, double time)						// downDown
	{
		if(state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
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
		if(locked)
		{
			if(part.first)
				part.first->move(Vector2D<>(0,0));
			if(part.second && !(dynamic_cast<Plug *>(part.first) && dynamic_cast<Plug *>(part.second) &&
				((Plug *)part.first)->permanent && ((Plug *)part.second)-> permanent &&
				((Plug *)part.first)->parent->parent == ((Plug *)part.second)->parent->parent))
					part.second->move(Vector2D<>(0,0));
		} // end if
	} // end function upUp


	void downUp(const EventDispatcher &dispatcher, double time)								// downUp
	{
		if(!state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
	} // end function downUp


	void enterUp(const EventDispatcher &dispatcher, double time)							// enterUp
	{
		// stay
	} // end function enterUp


}; // end namespace Selection
