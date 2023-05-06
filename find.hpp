#pragma once

#include<utility> // std::index_sequence
#include<tuple>   // std::tuple
#include<cstddef> // std::size_t

#include"for_each.hpp" // mlib::for_each
#include"tuple.hpp"    // mlib::tuple
#include"get.hpp"      // mlib::get

namespace mlib
{
	template<auto to_add, auto to_find, typename T, typename... Ts, std::size_t index, std::size_t... indexes>
	constexpr auto find_helper(mlib::tuple<T, Ts...> tup, std::index_sequence<index, indexes...>)
	{
		if constexpr (get<index + to_add>(tup) == to_find)
		{
			return index;
		}
		else if constexpr (get<index + to_add>(tup) != to_find)
		{
			return find_helper<to_add + 1, to_find, Ts..., indexes...>(tup.second, std::make_index_sequence<Ts...>{});
		}
	}

	template<auto to_add, auto to_find, typename T, std::size_t index>
	constexpr auto find_helper(mlib::tuple<T> tup, std::index_sequence<index>)
	{
		if constexpr (get<index + to_add>(tup) == to_find)
		{
			return index;
		}
		else if constexpr (get<index + to_add>(tup) != to_find)
		{
			return -1;
		}
	}

	template<auto to_find, typename T, typename... Ts, std::size_t index, std::size_t... indexes>
	constexpr auto find_helper(mlib::tuple<T, Ts...> tup, std::index_sequence<index, indexes...>)
	{
		if constexpr (mlib::get<index>(tup) == to_find)
		{
			return index;
		}
		else if constexpr (get<index>(tup) != to_find)
		{
			return find_helper<to_find, Ts..., indexes...>(tup.second, std::index_sequence<indexes...>{});
		}
	}

	template<auto to_find, typename... Ts>
	constexpr auto find(mlib::tuple<Ts...> t) -> bool
	{
		return find_helper<to_find, Ts...>(t, std::make_index_sequence<sizeof...(Ts)>{});
	}
} // namespace mlib