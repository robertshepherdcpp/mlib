#pragma once

#include<cstddef> // std::size_t
#include<utility> // std::index_sequence, std::make_index_sequence
#include<tuple>   // std::tuple

#include"tuple.hpp" // mlib::tuple
#include"get.hpp"   // mlib::get

namespace mlib
{
   template<auto lambda, typename... Ts>
	constexpr auto for_each(std::tuple<Ts...>& t)
	{
		[=] <std::size_t... indexes>(std::index_sequence<indexes...>)
		{
			(std::get<indexes>(t), ...);
		}(std::make_index_sequence<sizeof...(Ts)>{});
	}
} // namespace mlib