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

	bool operator()(const ComparedType &instance_to_compare)
	{
		return ComparerType()(instance_to_compare,iThreshold);
	} // end function operator ()
private:
	ComparedType iThreshold;
}; // end class Comparer