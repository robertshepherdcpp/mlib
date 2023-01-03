// could take this out.
#pragma once

#include<iostream>

namespace mlib
{
	template<typename T, typename... Ts>
	auto Print(T t, Ts... ts)
	{
		std::cout << t;
		(std::cout << ts, ...);
	}

	template<typename T>
	auto Print(T t)
	{
		std::cout << t;
	}
} // namespace pse