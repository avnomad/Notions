//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Notions.
 *
 *	Notions is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Notions is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Notions.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "event handlers.h"

namespace Conversion
{
	void setHandlers(const EventDispatcher &dispatcher)										// setHandlers
	{
		dispatcher.motion = Conversion::mouseMove;	// move
		dispatcher.button[0].down = Conversion::mouseleftDown;	// mouse left
		dispatcher.button[0].up = Conversion::mouseleftUp;
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
	} // end function setHandlers
}; // end namespace Conversion

namespace Creation
{
	void setHandlers(const EventDispatcher &dispatcher)										// setHandlers
	{
		dispatcher.motion = Creation::mouseMove;	// move
		dispatcher.button[0].down = Creation::mouseleftDown;	// mouse left
		dispatcher.button[0].up = Creation::mouseleftUp;
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
	} // end function setHandlers
}; // end namespace Creation

namespace Navigation
{
	void setHandlers(const EventDispatcher &dispatcher)										// setHandlers
	{
		dispatcher.motion = Navigation::mouseMove;	// move
		dispatcher.button[0].down = Navigation::mouseleftDown;	// mouse left
		dispatcher.button[0].up = Navigation::mouseleftUp;
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
	} // end function setHandlers
}; // end namespace Navigation

namespace Selection
{
	void setHandlers(const EventDispatcher &dispatcher)										// setHandlers
	{
		dispatcher.motion = Selection::mouseMove;	// move
		dispatcher.button[0].down = Selection::mouseleftDown;	// mouse left
		dispatcher.button[0].up = Selection::mouseleftUp;
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
	} // end function setHandlers
}; // end namespace Selection

namespace Configuration
{
	void setHandlers(const EventDispatcher &dispatcher)										// setHandlers
	{
		dispatcher.motion = Configuration::mouseMove;	// move
		dispatcher.button[0].down = Configuration::mouseleftDown;	// mouse left
		dispatcher.button[0].up = Configuration::mouseleftUp;
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
	} // end function setHandlers
}; // end namespace Configuration
