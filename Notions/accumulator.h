class Accumulator
{
public:


	void operator()(const pair<int,int> &coords)
	{
		iXSum += coords.first;
		iYSum += coords.second;
		iXYSum += coords.first*coords.second;
		iX2Sum += coords.first*coords.first;
		++iN;
	} // end function operator()

	Accumulator &displaySums() const
	{
		cout<<iXSum<<endl;
		cout<<iYSum<<endl;
		cout<<iXYSum<<endl;
		cout<<iX2Sum<<endl;
		cout<<iN<<endl;
		return *this;
	} // end function registerLine

	Accumulator &registerLine() const
	{
		GLdouble temp = iN*iX2Sum - iXSum*iXSum;
		GLdouble b = (iYSum*iX2Sum - iXSum*iXYSum) / temp;
		GLdouble a = (iN*iXYSum - iXSum*iYSum) / temp;
		//GLdouble da = sqrt(temp = iX2Sum*
		//GLdouble db = 
		polyLine.push_back(pair<GLdouble,GLdouble>(0,b));
		polyLine.push_back(pair<GLdouble,GLdouble>(1280,a*1280+b));
		glutPostRedisplay();
		return *this;
	} // end function registerLine
private:
	GLdouble iXSum;
	GLdouble iYSum;
	GLdouble iXYSum;
	GLdouble iX2Sum;
	unsigned int iN;
}; // end class Accumulator