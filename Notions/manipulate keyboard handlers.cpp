#include "event handlers.h"

void disableKeyboardHandlers(const EventDispatcher &dispatcher)											// disableKeyboardHandlers
{
	dispatcher.key[DIK_ESCAPE].down = 0;	// escape
	dispatcher.key[DIK_LEFT].down = 0;	// left
	dispatcher.key[DIK_LEFT].up = 0;
	dispatcher.key[DIK_RIGHT].down = 0;	// right
	dispatcher.key[DIK_RIGHT].up = 0;
	dispatcher.key[DIK_UP].down = 0;	// up
	dispatcher.key[DIK_UP].up = 0;
	dispatcher.key[DIK_DOWN].down = 0;	// down
	dispatcher.key[DIK_DOWN].up = 0;
	dispatcher.key[DIK_RETURN].down = 0;	// enter
	dispatcher.key[DIK_RETURN].up = 0;
} // end function disableKeyboardHandlers

namespace Conversion
{
	void enableKeyboardHandlers(const EventDispatcher &dispatcher)										// enableKeyboardHandlers
	{
		dispatcher.key[DIK_ESCAPE].down = escape;	// escape
		dispatcher.key[DIK_LEFT].down = Conversion::leftDown;	// left
		dispatcher.key[DIK_LEFT].up = Conversion::leftUp;
		dispatcher.key[DIK_RIGHT].down = Conversion::rightDown;	// right
		dispatcher.key[DIK_RIGHT].up = Conversion::rightUp;
		dispatcher.key[DIK_UP].down = Conversion::upDown;	// up
		dispatcher.key[DIK_UP].up = Conversion::upUp;
		dispatcher.key[DIK_DOWN].down = Conversion::downDown;	// down
		dispatcher.key[DIK_DOWN].up = Conversion::downUp;
		dispatcher.key[DIK_RETURN].down = Conversion::enterDown;	// enter
		dispatcher.key[DIK_RETURN].up = Conversion::enterUp;
	} // end function enableKeyboardHandlers
}; // end namespace Conversion

namespace Creation
{
	void enableKeyboardHandlers(const EventDispatcher &dispatcher)										// enableKeyboardHandlers
	{
		dispatcher.key[DIK_ESCAPE].down = escape;	// escape
		dispatcher.key[DIK_LEFT].down = Creation::leftDown;	// left
		dispatcher.key[DIK_LEFT].up = Creation::leftUp;
		dispatcher.key[DIK_RIGHT].down = Creation::rightDown;	// right
		dispatcher.key[DIK_RIGHT].up = Creation::rightUp;
		dispatcher.key[DIK_UP].down = Creation::upDown;	// up
		dispatcher.key[DIK_UP].up = Creation::upUp;
		dispatcher.key[DIK_DOWN].down = Creation::downDown;	// down
		dispatcher.key[DIK_DOWN].up = Creation::downUp;
		dispatcher.key[DIK_RETURN].down = Creation::enterDown;	// enter
		dispatcher.key[DIK_RETURN].up = Creation::enterUp;
	} // end function enableKeyboardHandlers
}; // end namespace Creation

namespace Navigation
{
	void enableKeyboardHandlers(const EventDispatcher &dispatcher)										// enableKeyboardHandlers
	{
		dispatcher.key[DIK_ESCAPE].down = escape;	// escape
		dispatcher.key[DIK_LEFT].down = Navigation::leftDown;	// left
		dispatcher.key[DIK_LEFT].up = Navigation::leftUp;
		dispatcher.key[DIK_RIGHT].down = Navigation::rightDown;	// right
		dispatcher.key[DIK_RIGHT].up = Navigation::rightUp;
		dispatcher.key[DIK_UP].down = Navigation::upDown;	// up
		dispatcher.key[DIK_UP].up = Navigation::upUp;
		dispatcher.key[DIK_DOWN].down = Navigation::downDown;	// down
		dispatcher.key[DIK_DOWN].up = Navigation::downUp;
		dispatcher.key[DIK_RETURN].down = Navigation::enterDown;	// enter
		dispatcher.key[DIK_RETURN].up = Navigation::enterUp;
	} // end function enableKeyboardHandlers
}; // end namespace Navigation

namespace Selection
{
	void enableKeyboardHandlers(const EventDispatcher &dispatcher)										// enableKeyboardHandlers
	{
		dispatcher.key[DIK_ESCAPE].down = escape;	// escape
		dispatcher.key[DIK_LEFT].down = Selection::leftDown;	// left
		dispatcher.key[DIK_LEFT].up = Selection::leftUp;
		dispatcher.key[DIK_RIGHT].down = Selection::rightDown;	// right
		dispatcher.key[DIK_RIGHT].up = Selection::rightUp;
		dispatcher.key[DIK_UP].down = Selection::upDown;	// up
		dispatcher.key[DIK_UP].up = Selection::upUp;
		dispatcher.key[DIK_DOWN].down = Selection::downDown;	// down
		dispatcher.key[DIK_DOWN].up = Selection::downUp;
		dispatcher.key[DIK_RETURN].down = Selection::enterDown;	// enter
		dispatcher.key[DIK_RETURN].up = Selection::enterUp;
	} // end function enableKeyboardHandlers
}; // end namespace Selection

namespace Configuration
{
	void enableKeyboardHandlers(const EventDispatcher &dispatcher)										// enableKeyboardHandlers
	{
		dispatcher.key[DIK_ESCAPE].down = escape;	// escape
		dispatcher.key[DIK_LEFT].down = Configuration::leftDown;	// left
		dispatcher.key[DIK_LEFT].up = Configuration::leftUp;
		dispatcher.key[DIK_RIGHT].down = Configuration::rightDown;	// right
		dispatcher.key[DIK_RIGHT].up = Configuration::rightUp;
		dispatcher.key[DIK_UP].down = Configuration::upDown;	// up
		dispatcher.key[DIK_UP].up = Configuration::upUp;
		dispatcher.key[DIK_DOWN].down = Configuration::downDown;	// down
		dispatcher.key[DIK_DOWN].up = Configuration::downUp;
		dispatcher.key[DIK_RETURN].down = Configuration::enterDown;	// enter
		dispatcher.key[DIK_RETURN].up = Configuration::enterUp;
	} // end function enableKeyboardHandlers
}; // end namespace Configuration
