#pragma once

namespace mlib
{
	template<bool b, bool... b>
	struct one_of
	{
		static constexpr bool value = b || one_of<b...>::value
	};

	template<bool b>
	struct one_of
	{
		static constexpr bool value = b;
	};
} // namespace mlib