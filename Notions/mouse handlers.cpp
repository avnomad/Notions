#include "configuration mouse.h"
#include "conversion mouse.h"
#include "creation mouse.h"
#include "navigation mouse.h"
#include "selection mouse.h"

#include "Shape Hierarchy.h"

Socket *findSocket(const Vector2D<> &point)												// findSocket
{
	Socket *socket;
	list<Region *>::iterator begin = shapes.regions.begin();
	list<Region *>::iterator end = shapes.regions.end();
	while(begin != end)
	{
		if(socket = (*begin)->nearSocket(point,unit))
			return socket;
		++begin;
	} // end while
	return 0;
} // end function findSocket
