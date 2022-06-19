//(c)2022 Dan Micsa, dmicsa@gmail.com, dan@dmicsa.com, www.dmicsa.com. Free to use.

// void* operator new(size_t size)
//{
//	heapAllocations()++;
//	memoryAllocated() += size;
//	return malloc(size);
//}

#include "Context.hpp"

using namespace DIM;
using namespace std;

namespace DIM
{

} // namespace DIM

int main()
{
	try
	{
		Context c;
		I n{10};
		c["I"] = makePair(n);
		R r{-22.212};
		c["R"] = makePair(r);
		S s{"Cucu"};
		c["S"] = makePair(s);

		print(c);
		cout << extract<I>(c, "I", DIM_WHERE) << '\n';
		cout << extract<R>(c, "R", DIM_WHERE) << '\n';
		cout << extract<S>(c, "S", DIM_WHERE) << '\n';
		// cout << extract<S>(c, "WrongKey", DIM_WHERE) << '\n'; // WrongKey error!
		// cout << extract<R>(c, "String", DIM_WHERE) << '\n';//WrongType error!
	}
	catch (const std::exception &e)
	{
		cout << "\n\n" << toS(e.what(), DIM_WHERE) << "\n\n";
	}
	catch (const DIM::Exception &e)
	{
		cout << "\n\n" << toS(e.what_, e.where_) << "\n\n";
	}
	return 0;
}