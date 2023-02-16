#pragma once

#include"get_nth_element.hpp"

namespace mlib
{
	template<auto... Ts>
	struct value_sequence
	{
		template<auto I>
		constexpr auto at()
		{
			return mlib::get_nth_element<I>(Ts...);
		}
	};
} // namespace mlib