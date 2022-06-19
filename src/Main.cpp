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
		cout << "----------------\n";
		{ // using manual names for VariableHolder
			VariableHolder<I> vh1(c, "I1", 10, DIM_WHERE);
			VariableHolder<I> vh2(c, "I2", 15, DIM_WHERE);
			cout << "Checkpoint: A";
			print(c);
			cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
			cout << extract<I>(c, "I2", DIM_WHERE) << '\n';
		}
		cout << "Checkpoint: B";
		print(c);

		cout << "----------------\n";
		{ // using automatic names.VariableHolder
			DIM_AUTO_VARIABLE_HOLDER(I, c, "I1", 20);
			DIM_AUTO_VARIABLE_HOLDER(I, c, "I2", 25);
			cout << "Checkpoint: C";
			print(c);
			cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
			cout << extract<I>(c, "I2", DIM_WHERE) << '\n';
		}
		cout << "Checkpoint: D";
		print(c);

		cout << "----------------\n";
		{ // using automatic names.VariableHolder
			DIM_AUTO_VARIABLE_HOLDER(I, c, "I1", 20);
			DIM_AUTO_VARIABLE_HOLDER(I, c, "I2", 25);
			cout << "Checkpoint: E";
			print(c);
			cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
			cout << extract<I>(c, "I2", DIM_WHERE) << '\n';

			cout << "Assign them to new values.\n";
			extract<I>(c, "I1", DIM_WHERE) = 21;
			extract<I>(c, "I2", DIM_WHERE) = 26;
			cout << "Checkpoint: F";
			print(c);
			cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
			cout << extract<I>(c, "I2", DIM_WHERE) << '\n';
		}
		cout << "Checkpoint: G";
		print(c);

		cout << "----------------\n";
		cout << "Checkpoint: H";
		cout << extract<I>(c, "I2", DIM_WHERE) << '\n'; // Throws!
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

int main1()
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