#include "event handlers.h"
#include "global variables.h"
#include "utility.h"

namespace Navigation
{
	void mouseleftDown(const EventDispatcher &dispatcher, double time)														// mouseleftDown
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		Vector2D<> position = current.cursor - correction;
		current.cursor = unproject(current.cursor);


		if(!(navigator.dispositioning || navigator.rotating || navigator.zooming))
		{
			if(displayLists->rotationIndicator.inside(position))		// relocate
			{
				navigator.oldPosition = current.cursor;
				navigator.dispositioning = true;
			}
			else if(displayLists->rotationIndicator.outside(position))	// rotate
			{
				navigator.oldPosition = position;
				navigator.rotating = true;
			}
			else														// zoom
			{
				navigator.oldPosition = position;
				navigator.zooming = true;
			} // end else
			disableKeyboardHandlers(dispatcher);
		} // end if
	} // end function mouseleftDown


	void mouseleftUp(const EventDispatcher &dispatcher, double time)														// mouseleftUp
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		Vector2D<> position;


		if(navigator.dispositioning)													// relocate
		{
			position = unproject(current.cursor);
			transform.displacement += position - navigator.oldPosition;
			navigator.dispositioning = false;
			Navigation::enableKeyboardHandlers(dispatcher);
		}
		if(navigator.rotating)															// rotate
		{
			position = current.cursor - correction;
			if(position != Vector2D<>(0,0))
				transform.rotation += (180/PI)*(navigator.oldPosition^position);
			navigator.rotating = false;
			Navigation::enableKeyboardHandlers(dispatcher);
		}
		if(navigator.zooming)															// zoom
		{
			position = current.cursor - correction;
			if(position != Vector2D<>(0,0))
			{
				transform.zoomAngle += (180/PI)*(navigator.oldPosition^position);
				transform.zoom = pow(0.1,transform.zoomAngle/360);
			} // end if
			navigator.zooming = false;
			Navigation::enableKeyboardHandlers(dispatcher);
		} // end else
		transform.apply();
		current.cursor = unproject(current.cursor);
	} // end function mouseleftUp


	void mouseMove(const EventDispatcher &dispatcher, double time)														// mouseMove
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		Vector2D<> position;

		if(navigator.dispositioning)																	// relocate
		{
			position = unproject(current.cursor);
			transform.displacement += position - navigator.oldPosition;
		}
		else
		{
			position = current.cursor - correction;
			if(position != Vector2D<>(0,0))
				if(navigator.rotating)																	// rotate
				{
					transform.rotation += (180/PI)*(navigator.oldPosition^position);
					navigator.oldPosition = position;
				}
				else if(navigator.zooming)																// zoom
				{
					transform.zoomAngle += (180/PI)*(navigator.oldPosition^position);
					transform.zoom = pow(0.1,transform.zoomAngle/360);
					navigator.oldPosition = position;
				} // end else
		} // end if
		transform.apply();
		current.cursor = unproject(current.cursor);
	} // end function mouseMove


}; // end namespace Navigation
