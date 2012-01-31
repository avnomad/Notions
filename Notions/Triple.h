struct Triple	// check
{
	// member functions
	Triple(){}	// default constructor

	Triple(const Triple &original)
		:x(original.x),y(original.y),t(original.t)
	{
		// empty body
	} // end Triple copy constructor

	Triple(GLdouble px , GLdouble py , GLdouble pt)
		:x(px),y(py),t(pt)
	{
		// empty body
	} // end Triple constructor

	Triple &operator=(const Triple &original)
	{
		x = original.x;
		y = original.y;
		t = original.t;
		return *this;
	} // end function operator =

	Triple &operator=(const Statistics &stats)	// dummy function to work around a problem with
	{											// adjacent_difference assigning the first element as is.
		return *this;
	} // end function operator =
	
	Triple operator-(const Triple &right) const
	{
		return Triple( this->x - right.x , this->y - right.y , this->t - right.t );
	} // end function operator-

	// data members
	GLdouble x;
	GLdouble y;
	GLdouble t;
}; // end class Triple