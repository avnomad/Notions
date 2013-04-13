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

template<typename ComparedType , typename ComparerType = std::less<ComparedType> >
class Comparer
{
public:
	Comparer(const ComparedType &threshold)
		:iThreshold(threshold)
	{
		// empty body
	} // end Comparer constructor

	Comparer(const Comparer &original)
		:iThreshold(original.iThreshold)
	{
		// empty body
	} // end Comparer copy constructor

	bool operator()(const ComparedType &instance_to_compare) const
	{
		return ComparerType()(instance_to_compare,iThreshold);
	} // end function operator ()
private:
	ComparedType iThreshold;
}; // end class Comparer