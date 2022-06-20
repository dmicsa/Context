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

	class SwapKey2
	{
	public:
		SwapKey2(void *&p1, void *&p2) : p1_(p1), p2_(p2) { std::swap(p1_, p2_); }
		~SwapKey2() { std::swap(p1_, p2_); }
		void *p1_;
		void *p2_;
	};
	class SwapKey3
	{
	public:
		SwapKey3(void *&p1, void *&p2) : p1_(p1), p2_(p2) { std::swap(p1_, p2_); }
		~SwapKey3() { std::swap(p1_, p2_); }
		void *p1_;
		void *p2_;
	};

	template <class T> class SwapKey4
	{
	public:
		SwapKey4(T *&p1, T *&p2) : p1_(p1), p2_(p2) { std::swap(p1_, p2_); }
		~SwapKey4() { std::swap(p1_, p2_); }
		T *p1_;
		T *p2_;
	};
} // namespace DIM

void use1(Context &, ...) {}
void use2(Context &, ...) {}

int main()
{
	try
	{
// include here the "Ex*.inc" files!
#include "Tests/Ex2.inc"

		// Examples of calling other functions with the context
		use1(c);
		use2(c, 10, 22, "a string");
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

int main2()
{
	int a, b;
	int *pa = &a, *pb = &b;

	cout << "pa = " << static_cast<void *>(pa) << endl;
	cout << "pb = " << static_cast<void *>(pb) << endl;

	swap(pa, pb);

	cout << "pa = " << static_cast<void *>(pa) << endl;
	cout << "pb = " << static_cast<void *>(pb) << endl;

	return 0;
}