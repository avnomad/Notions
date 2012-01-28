// prototype
bool point_in_segment(const Triple &p , const Triple &p1, const Triple &p2 , GLfloat width);

struct PolyLine
{
	// member functions
	PolyLine()
	{
		// empty body
	} // end PolyLine default constructor

	PolyLine(const Triple &drawColor,GLenum drawMode,GLfloat drawWidth,const vector<Triple> &edges)
		:color(drawColor),mode(drawMode),width(drawWidth),vertices(edges)
	{
		// empty body
	} // end PolyLine constructor

	PolyLine(const PolyLine &original)
		:color(original.color),mode(original.mode),width(original.width),vertices(original.vertices)
	{
		// empty body
	} // end PolyLine copy constructor

	PolyLine &operator=(const PolyLine &original)
	{
		color = original.color;
		mode = original.mode;
		width = original.width;
		vertices = original.vertices;
		return *this;
	} // end function operator =

	void display() const
	{
		glColor3d(color.x,color.y,color.t);
		glLineWidth(width);
		::display(vertices.begin(),vertices.end(),mode);
	} // end function display

	bool belongs(const Triple &point)
	{
		if(vertices.size() < 2) return false;

		int c = vertices.size();
		while(--c)
			if(point_in_segment(point,vertices[c-1],vertices[c],width)) return true;
		if(mode == GL_LINE_LOOP)
			if(point_in_segment(point,vertices.front(),vertices.back(),width)) return true;
		return false;
	} // end function belongs

	// data members
	Triple color;	// the color of the polyline
	GLenum mode;	// wether the polyline will form a loop
	GLfloat width;	// the line width of the polyline
	vector<Triple> vertices;	// the vertices of the polyline
}; // end class PolyLine