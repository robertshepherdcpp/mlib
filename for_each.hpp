#pragma once

#include<cstddef> // std::size_t
#include<utility> // std::index_sequence, std::make_index_sequence

#include"tuple.hpp" // mlib::tuple
#include"get.hpp"   // mlib::get

namespace mlib
{
	template <typename... T, typename F, std::size_t... indexes>
	constexpr auto for_each_helper(std::tuple<T...>& tuple, F& f, std::index_sequence<indexes...>) -> void
	{
		int expand[] = { 0, ((f(std::get<indexes>(tuple))), void(), 0)... };
		(void)expand;
	}

	template<typename F, typename... Ts>
	constexpr auto for_each(std::tuple<Ts...>& t, F&& c)
	{
		for_each_helper(t, c, std::make_index_sequence<sizeof...(Ts)>{});
	}
} // namespace mlib