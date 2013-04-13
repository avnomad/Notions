//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Notions.
 *
 *	Notions is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Notions is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Notions.  If not, see <http://www.gnu.org/licenses/>.
 */

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