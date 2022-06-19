# Context

A generic Context class to store globals and other settings w/o changing function's definition using void* pointers.

It is one header file and some examples.

Some mechanism for protection via policies are implemented.

Free to use.

<details><summary>Example 1  (requires v0.0.2): Wrong Returned Type.</summary>
<p>

```cpp
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
		cout << extract<R>(c, "String", DIM_WHERE) << '\n';//Wrong type!
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
```
```
OUTPUT:
10
10.12
Cucu


EXCEPTION : "Key: 'String' assigned to a different type.", From: "main()", file: "Main.cpp", line: 31.
```
</p>
</details>

<details><summary>Example 2 (requires v0.0.2): Wrong Key.</summary>
<p>

```cpp
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
		cout << extract<S>(c, "WrongKey", DIM_WHERE) << '\n';//Wrong key!		
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
```
```
OUTPUT:
10
10.12
Cucu


EXCEPTION : "Key: 'WrongKey' not found in context.", From: "main()", file: "Main.cpp", line: 30.
```
</p>
</details>

<details><summary>Example 3 (requires v0.0.5): Context content.</summary>
<p>

```cpp
#include "Context.hpp"

using namespace DIM;
using namespace std;

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
	}
	catch (...){}//as before

	return 0;
}	
```
```
OUTPUT:
Context content:
{
  I : int,
  R : double,
  S : class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,
}
10
-22.212
Cucu
```
</p>
</details>


<details><summary>Example 4 (requires v0.0.6): VariableHolder.</summary>
<p>

```cpp
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
	catch (...){}//as before

	return 0;
}	
```
```
OUTPUT:
----------------
Checkpoint: A
Context content:
{
  I1 : int,
  I2 : int,
}
10
15
Checkpoint: B
Context content:
{
}
----------------
Checkpoint: C
Context content:
{
  I1 : int,
  I2 : int,
}
20
25
Checkpoint: D
Context content:
{
}
----------------
Checkpoint: E
Context content:
{
  I1 : int,
  I2 : int,
}
20
25
Assign them to new values.
Checkpoint: F
Context content:
{
  I1 : int,
  I2 : int,
}
21
26
Checkpoint: G
Context content:
{
}
----------------
Checkpoint: H

EXCEPTION : "Key: 'I2' not found in context.", From: "main()", file: "Main.cpp", line: 66.
```
</p>
</details>
