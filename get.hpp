#pragma once

#include"tuple.hpp" // mlib::tuple

namespace mlib
{
	template<auto Index>
	constexpr auto get(auto& tup) -> decltype(auto)
	{
		if constexpr (Index == 0)
		{
			return tup.first;
		}
		else if constexpr (Index != 0)
		{
			return get<Index - 1>(tup.second);
		}
	}
} // namespace mlib