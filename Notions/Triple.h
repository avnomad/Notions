struct Triple
{
	// member functions
	inline Triple(){}	// default constructor

	inline Triple(const Triple &original)
		:x(original.x),y(original.y),t(original.t)
	{
		// empty body
	} // end Triple copy constructor

	inline Triple(GLdouble px , GLdouble py , GLdouble pt)
		:x(px),y(py),t(pt)
	{
		// empty body
	} // end Triple constructor

	inline const Triple &operator=(const Triple &original)
	{
		x = original.x;
		y = original.y;
		t = original.t;
		return *this;
	} // end function operator =

	// data members
	GLdouble x;
	GLdouble y;
	GLdouble t;
}; // end class Triple