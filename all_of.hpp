#pragma once

namespace mlib
{
	template<bool b, bool... bs>
	struct all_of
	{
		static constexpr auto value = (b && bs...);
	};

	template<bool b>
	struct all_of<b>
	{
		static constexpr auto value = b;
	};
} // namespace mlib