#pragma once

namespace mlib
{
	template<bool b, bool... bs>
	struct all_of
	{
		static constexpr auto value = b && all_of<bs...>::value;
	};

	template<bool b>
	struct all_of<b>
	{
		static constexpr auto value = b;
	};
} // namespace mlib