# Context

A generic Context class to store globals and other settings w/o changing function's definition using void* pointers.

It is one header file and some examples.

Some mechanism for protection are implemented.

Free to use.

<details><summary>The main()  (requires v0.0.2): Used to invoke the examples.</summary>
<p>

```cpp
#include "Context.hpp"

using namespace DIM;
using namespace std;

void use1(Context&, ...) {}
void use2(Context&, ...) {}

int main()
{
	try
	{
		// include here the "Ex*.inc" files!
#include "Tests/Ex1.inc"

		//Examples of calling other functions with the context.
		use1(c);
 		use2(c, 10, 22, "a string");
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
</p>
</details>

<details><summary>Example 1  (requires v0.0.2): Wrong Returned Type.</summary>
<p>

```cpp
Context c;

I n{10};
c["i"] = makePair(n);
R r{10.12};
c["r"] = makePair(r);
S s{"Cucu"};
c["s"] = makePair(s);

cout << extract<I>(c, "i", DIM_WHERE) << '\n';
cout << extract<R>(c, "r", DIM_WHERE) << '\n';
cout << extract<S>(c, "s", DIM_WHERE) << '\n';
cout << extract<R>(c, "s", DIM_WHERE) << '\n'; // Wrong type!
```

```
10
10.12
Cucu

EXCEPTION : "Key: 's' assigned to a different type.", From: "main()", file: "Ex1.inc", line: 12.
```
</p>
</details>

<details><summary>Example 2  (requires v0.0.2): Wrong Returned Type.</summary>
<p>

```cpp
Context c;

I n{10};
c["i"] = makePair(n);
R r{10.12};
c["r"] = makePair(r);
S s{"Cucu"};
c["s"] = makePair(s);

cout << extract<I>(c, "i", DIM_WHERE) << '\n';
cout << extract<R>(c, "r", DIM_WHERE) << '\n';
cout << extract<S>(c, "s", DIM_WHERE) << '\n';
cout << extract<S>(c, "wrongKey", DIM_WHERE) << '\n'; // Wrong key!
```

```
10
10.12
Cucu

EXCEPTION : "Key: 'wrongKey' not found in context.", From: "main()", file: "Ex2.inc", line: 12.
```
</p>
</details>

<details><summary>Example 3  (requires v0.0.5): Print context content.</summary>
<p>

```cpp
Context c;

I n{10};
c["i"] = makePair(n);
R r{-22.212};
c["r"] = makePair(r);
S s{"Cucu"};
c["s"] = makePair(s);

print(c);
cout << extract<I>(c, "i", DIM_WHERE) << '\n';
cout << extract<R>(c, "r", DIM_WHERE) << '\n';
cout << extract<S>(c, "s", DIM_WHERE) << '\n';
```

```
Context content:
{
  i : int,
  r : double,
  s : class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,
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
Context c;

cout << "----------------\n";
{ // using manual names for VariableHolder
	VariableHolder<I> vh1(c, "i1", 10, DIM_WHERE);
	VariableHolder<I> vh2(c, "i2", 15, DIM_WHERE);
	cout << "Checkpoint: A";
	print(c);
	cout << extract<I>(c, "i1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "i2", DIM_WHERE) << '\n';
}
cout << "Checkpoint: B";
print(c);

cout << "----------------\n";
{ // using automatic names.VariableHolder
	DIM_AUTO_VARIABLE_HOLDER(I, c, "i1", 20);
	DIM_AUTO_VARIABLE_HOLDER(I, c, "i2", 25);
	cout << "Checkpoint: C";
	print(c);
	cout << extract<I>(c, "i1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "i2", DIM_WHERE) << '\n';
}
cout << "Checkpoint: D";
print(c);

cout << "----------------\n";
{ // using automatic names.VariableHolder
	DIM_AUTO_VARIABLE_HOLDER(I, c, "i1", 20);
	DIM_AUTO_VARIABLE_HOLDER(I, c, "i2", 25);
	cout << "Checkpoint: E";
	print(c);
	cout << extract<I>(c, "i1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "i2", DIM_WHERE) << '\n';

	cout << "Assign them to new values.\n";
	extract<I>(c, "i1", DIM_WHERE) = 21;
	extract<I>(c, "i2", DIM_WHERE) = 26;
	cout << "Checkpoint: F";
	print(c);
	cout << extract<I>(c, "i1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "i2", DIM_WHERE) << '\n';
}
cout << "Checkpoint: G";
print(c);

cout << "----------------\n";
cout << "Checkpoint: H";
cout << extract<I>(c, "i2", DIM_WHERE) << '\n'; // Throws!
```

```
----------------
Checkpoint: A
Context content:
{
  i1 : int,
  i2 : int,
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
  i1 : int,
  i2 : int,
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
  i1 : int,
  i2 : int,
}
20
25
Assign them to new values.
Checkpoint: F
Context content:
{
  i1 : int,
  i2 : int,
}
21
26
Checkpoint: G
Context content:
{
}
----------------
Checkpoint: H
EXCEPTION : "Key: 'i2' not found in context.", From: "main()", file: "Ex4.inc", line: 49.
```
</p>
</details>

<details><summary>Example 5  (requires v0.0.7): Swap variables in a scope.</summary>
<p>

```cpp
Context c;
DIM_AUTO_VARIABLE_HOLDER(I, c, "I", 10);
cout << extract<I>(c, "I", DIM_WHERE) << '\n';
{
	I i{20};
	DIM_AUTO_SWAP_KEY(i, c["I"].first);
	cout << extract<I>(c, "I", DIM_WHERE) << '\n';
}
cout << extract<I>(c, "I", DIM_WHERE) << '\n';
```

```
10
20
10
```
</p>
</details>

<details><summary>Example 6  (requires v0.0.7): Swap dynmic variables in a scope.</summary>
<p>

```cpp
struct OStream
{
public:
	virtual V print(const SV) = 0;
	virtual ~OStream() {}
};
struct OStream1 : public OStream
{
	virtual V print(const SV v) override { cout << "S1: " << v; }
};
struct OStream2 : public OStream
{
	virtual V print(const SV v) override { cout << "S2: " << v; }
};

Context c;

OStream1 os1;
DIM_AUTO_VARIABLE_HOLDER(OStream &, c, "os", os1);
extract<OStream>(c, "os", DIM_WHERE).print("CUCU!\n");
{
	OStream2 os2;
	// DIM_AUTO_SWAP_KEY(os2, c["os"].first);//is not working yet and I will appreciate help wit it!
	c["os"].first = &os2;
	extract<OStream>(c, "os", DIM_WHERE).print("CUCU!\n");
	c["os"].first = &os1;
}
extract<OStream>(c, "os", DIM_WHERE).print("CUCU!\n");
```

```
S1: CUCU!
S2: CUCU!
S1: CUCU!
```