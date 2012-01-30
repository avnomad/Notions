struct Stroke
{
	// Fields
	vector<Triple> points;
	vector<Triple> velocities;
	vector<GLdouble> velocity_magnitudes;
	GLdouble max;
	GLdouble min;
	GLdouble threshold;

	// default constructed
	// default destructed
}; // end struct Stroke