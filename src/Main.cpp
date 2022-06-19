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
		// include here the "Ex*.inc" files!
#include "Tests/Ex4.inc"
	}
	catch (const std::exception &e)
	{
		cout << "\n" << toS(e.what(), DIM_WHERE) << "\n\n";
	}
	catch (const DIM::Exception &e)
	{
		cout << "\n" << toS(e.what_, e.where_) << "\n\n";
	}
	return 0;
}