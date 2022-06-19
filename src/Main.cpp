//(c:2003 Dan Micsa(dan@dmicsa.com, www.dmicsa.com:

//#include <IO.h>
//#include <array>
//#include <assert.h>
//#include <chrono>
//#include <cstdio>
//#include <deque>
//#include <filesystem>
//#include <format>
//#include <iostream>
//#include <iterator>
//#include <limits>
//#include <list>
//#include <map>
//#include <memory>
//#include <numeric>
//#include <omp.h>
//#include <queue>
//#include <ranges>
//#include <set>
//#include <stack>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string>
//#include <time.h>
//#include <typeinfo>
//#include <unordered_map>
//#include <unordered_set>
//#include <valarray>
//#include <vector>

#include <filesystem>
#include <iostream>
#include <map>
#include <omp.h>
#include <string>
#include <string_view>

// void* operator new(size_t size)
//{
//	heapAllocations()++;
//	memoryAllocated() += size;
//	return malloc(size);
//}

#define DIM_UNIQUE_NAME_2(x, y) x##y
#define DIM_UNIQUE_NAME_1(x, y) DIM_UNIQUE_NAME_2(x, y)
#define DIM_UNIQUE_NAME(x) DIM_UNIQUE_NAME_1(x, __COUNTER__)
#define DIM_WHERE                                                                                                                  \
	Where { __func__, __FILE__, __LINE__ }

namespace DIM
{
	using S = std::string;
	using SV = std::string_view;
	using WS = std::wstring;
	using WSV = std::wstring_view;
	using V = void;
	using B = bool;

	const S version("0.0.1");

	///////////////////////////////////////////////////////////////////////////////////////////////////
	class Where
	{
	public:
		SV function_, file_;
		long line_{-1};
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	class Exception
	{
	public:
		S what_;
		Where where_;
	};

	S fromWhere(const Where &);
	V throwException(const S &name, const Where &);

	///////////////////////////////////////////////////////////////////////////////////////////////////
	using Context = std::map<S, std::pair<V *, S>>;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	template <class T> T &extract(Context &c, const S &name, const Where &w)
	{
		const auto it = c.find(name);
		if (it == c.end())
			throwException("Key: '" + name + "' not found in context.", w);

		if (typeid(T).name() != it->second.second)
			throwException("Key: '" + name + "' assigned to a different type.", w);

		return *reinterpret_cast<T *>(it->second.first);
	}
	template <class T> auto makePair(T &t) { return std::make_pair(&t, typeid(T).name()); }

	S fromWhere(const Where &w)
	{
		const auto fileName{std::filesystem::path(w.file_).filename().string()};
		return std::format("From: \"{}\", file: \"{}\", line: {}.", w.function_, fileName, w.line_);
	}

	V throwException(const S &name, const Where &w)
	{
		// S s{ std::format("\"{}\". {}", name,fromWhere(w) };
		if (omp_in_parallel())
		{
#pragma omp critical
			std::cout << ("Error: Try to throw from inside parallel region! ") << fromWhere(w);
		}
		else
			throw Exception{name, w};
	}
} // namespace DIM

using namespace DIM;
using namespace std;

int main() { return 0; }