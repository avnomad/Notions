// includes
#include "global.h"

void keyPress(unsigned char key , int x , int y)
{
	switch(key)
	{
	case '\r':
		break;
	case '\b':
		grid_layer_status = !grid_layer_status;
		break;
	case '\33':
		exit(0);
		break;
	}
} // end function keypress

void keyPressSpecial(int key , int x , int y)
{
	switch(key)
	{
	case GLUT_KEY_RIGHT:
		selected = -1;
		line_segments.clear();
		polyLines.clear();
		strokes.clear();
		break;
	case GLUT_KEY_DOWN:
		++point_layer_status %= 4;
		break;
	case GLUT_KEY_LEFT:
		line_segment_layer_status = !line_segment_layer_status;
		break;
	case GLUT_KEY_UP:
		line_strip_layer_status = !line_strip_layer_status;
		break;
	}
} // end function keyPressSpecial