struct Statistics	// check
{
	// member functions
	Statistics()
		:x(0),y(0),xy(0),x2(0),n(0),a(0),b(0),c(0),center_x(0),center_y(0)
	{
		// empty body
	} // end Statistics default constructor

	Statistics(const Statistics &original)
		:x(original.x),y(original.y),xy(original.xy),x2(original.x2),n(original.n),a(original.a),b(original.b),c(original.c),center_x(original.center_x),center_y(original.center_y)
	{
		// empty body
	} // end Statistics copy constructor

	Statistics(GLdouble sx , GLdouble sy , GLdouble sxy , GLdouble sx2 , unsigned int sn , GLdouble sa , GLdouble sb , GLdouble sc , GLdouble scenter_x , GLdouble scenter_y)
		:x(sx),y(sy),xy(sxy),x2(sx2),n(sn),a(sa),b(sb),c(sc),center_x(scenter_x),center_y(scenter_y)
	{
		// empty body
	} // end Statistics constructor

	Statistics &operator=(const Statistics &original)
	{
		x = original.x;
		y = original.y;
		xy = original.xy;
		x2 = original.x2;
		n = original.n;
		a = original.a;
		b = original.b;
		c = original.c;
		center_x = original.center_x;
		center_y = original.center_y;
		return *this;
	} // end function operator =

	// data members
	GLdouble x;
	GLdouble y;
	GLdouble xy;
	GLdouble x2;
	unsigned int n;
	GLdouble a;
	GLdouble b;
	GLdouble c;
	GLdouble center_x;
	GLdouble center_y;
}; // end class Statistics