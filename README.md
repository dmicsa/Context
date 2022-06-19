# Context

A generic Context class to store globals using void* pointers.

Some mechanism for protection via policies are implemented.

Free to use.

<details><summary>Example 1: Wrong Returned Type.</summary>
<p>

#### We can hide anything, even code!

```cpp
   puts "Hello World"


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
Output:
10
10.12
Cucu


EXCEPTION : "Key: 'String' assigned to a different type.", From: "main", file: "Main.cpp", line: 31.
```
</p>
</details>

<details><summary>Example 2: Wrong Key.</summary>
<p>

#### We can hide anything, even code!

```cpp
   puts "Hello World"


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
10
10.12
Cucu


EXCEPTION : "Key: 'WrongKey' not found in context.", From: "main", file: "Main.cpp", line: 30.
```
</p>
</details>