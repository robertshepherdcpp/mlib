#pragma once

#include<cstddef> // std::size_t
#include<tuple>   // std::get

#include"index_sequence.hpp" // mlib::index_sequence

namespace mlib
{
	template<typename... T, typename F, std::size_t... indexes>
	constexpr auto transform_helper(std::tuple<T...>& t, F& f, std::index_sequence<indexes...> i_s)
	{
		return std::make_tuple(f(std::get<indexes>(t))...);
	}

	template<typename... T, typename F>
	constexpr auto transform(std::tuple<T...>& tup, F&& f)
	{
		return transform_helper(tup, f, std::make_index_sequence<sizeof...(T)>{});
	}
} // namespace mlib