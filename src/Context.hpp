#pragma once
//(c)2022 Dan Micsa, dmicsa@gmail.com, dan@dmicsa.com, www.dmicsa.com. Free to use.

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
	using I = int;
	using R = double;
	using V = void;
	using B = bool;

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

	inline S toS(const Where &w)
	{
		const auto fileName{std::filesystem::path(w.file_).filename().string()};
		return std::format("From: \"{}\", file: \"{}\", line: {}.", w.function_, fileName, w.line_);
	}

	inline V throwException(const S &name, const Where &w)
	{
		// S s{ std::format("\"{}\". {}", name,fromWhere(w) };
		if (omp_in_parallel())
		{
#pragma omp critical
			std::cout << ("Error: Try to throw from inside parallel region!  : \"{}\"") << toS(w);
		}
		else
			throw Exception{name, w};
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	class Context : public std::map<S, std::pair<V *, S>>
	{
		static inline const S version_{"0.0.2"};
	};

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

	S toS(const S &what, const Where &w) { return std::format("EXCEPTION : \"{}\", {}", what, toS(w)); }
} // namespace DIM
