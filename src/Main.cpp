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

int main()
{
	try
	{
		Context c;
		I n{10};
		c["Int"] = makePair(n);
		R r{10.12};
		c["Real64"] = makePair(r);
		S s{"Cucu"};
		c["String"] = makePair(s);

		cout << extract<I>(c, "Int", DIM_WHERE) << '\n';
		cout << extract<R>(c, "Real64", DIM_WHERE) << '\n';
		cout << extract<S>(c, "String", DIM_WHERE) << '\n';
		cout << extract<S>(c, "WrongKey", DIM_WHERE) << '\n'; // WrongKey error!
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