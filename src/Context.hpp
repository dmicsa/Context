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
#define DIM_AUTO_VARIABLE_HOLDER(Type, c, variableName, t)                                                                         \
	::DIM::VariableHolder<Type> DIM_UNIQUE_NAME(vh)(c, variableName, t, DIM_WHERE);
#define DIM_AUTO_SWAP_KEY(p1, p2) ::DIM::SwapKey DIM_UNIQUE_NAME(ck)(p1, p2);

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
		long long line_{-1};
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
		return std::format("From: \"{}()\", file: \"{}\", line: {}.", w.function_, fileName, w.line_);
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
		static inline const S version_{"0.0.10"};
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
	inline S repeat(const SV v, size_t times)
	{
		S s;
		for (size_t n(0); n < times; n++)
			s += v;
		return s;
	}
	inline S leftPad(const S &v, size_t length, const SV paddingString = " ")
	{
		return repeat(paddingString, length - v.size()) + v;
	}
	inline V print(const Context &c)
	{
		size_t maxLength{0};
		for (auto v : c)
			maxLength = std::max(maxLength, v.first.size());
		std::cout << "\nContext content: \n{\n";
		for (auto v : c)
		{
			std::cout << leftPad(v.first, maxLength + 2) << " : " << v.second.second << ',' << '\n';
		}
		std::cout << "}\n";
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	template <class T> class VariableHolder
	{
	public:
		VariableHolder(Context &c, const SV variableName, const T &t, const Where &w)
		    : c_(c), variableName_(variableName), t_(t), w_(w)
		{
			if (c_.find(variableName_) != c_.end())
				throwException(std::format("Variable: '{}' already registered. Use a simple assignment if "
							   "you want to change it.",
						   variableName_),
				    w_);
			c[variableName_] = makePair(t_);
		}

		~VariableHolder()
		{
			if (c_.find(variableName_) == c_.end())
				throwException(std::format("Variable: '{}' already erased.", variableName_), w_);
			c_.erase(variableName_);
		}

		Context &c_;
		const S variableName_;
		const Where w_;
		T t_;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	template <class T> class SwapKey
	{
	public:
		SwapKey(T &p1, void *&p2) : p1_(p1), p2_(*(T *)p2) { std::swap(p1_, p2_); }
		~SwapKey() { std::swap(p1_, p2_); }
		T &p1_;
		T &p2_;
	};
} // namespace DIM
