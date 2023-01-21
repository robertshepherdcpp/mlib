#pragma once

namespace mlib
{
	template<bool b, bool... b>
	struct one_of
	{
		static constexpr bool value = (b || b...);
	};

	template<bool b>
	struct one_of
	{
		static constexpr bool value = b;
	};
} // namespace mlib