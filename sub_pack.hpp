#pragma once

#include"get_nth_element.hpp"
#include"pack.hpp"

namespace mlib
{
	template<auto Start, auto End, auto... packs>
	constexpr auto sub_pack() /*-> mlib::pack*/
	{
		return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
		{
			return mlib::pack<get_nth_element<indexes>(packs...)...>{};
		}(std::make_index_sequence<sizeof...(packs)>{});
	}
} // namespace mlib