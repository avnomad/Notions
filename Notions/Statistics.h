struct Statistics
{
	// member functions
	inline Statistics()
		:x(0),y(0),xy(0),x2(0),n(0),a(0),b(0)
	{
		// empty body
	} // end Statistics default constructor

	inline Statistics(const Statistics &original)
		:x(original.x),y(original.y),xy(original.xy),x2(original.x2),n(original.n),a(original.a),b(original.b)
	{
		// empty body
	} // end Statistics copy constructor

	inline Statistics(GLdouble sx , GLdouble sy , GLdouble sxy , GLdouble sx2 , unsigned int sn , GLdouble sa , GLdouble sb)
		:x(sx),y(sy),xy(sxy),x2(sx2),n(sn),a(sa),b(sb)
	{
		// empty body
	} // end Statistics constructor

	inline const Statistics &operator=(const Statistics &original)
	{
		x = original.x;
		y = original.y;
		xy = original.xy;
		x2 = original.x2;
		n = original.n;
		a = original.a;
		b = original.b;
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
}; // end class Statistics