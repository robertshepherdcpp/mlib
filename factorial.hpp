#pragma once

namespace mlib
{
	template<auto T>
	struct factorial
	{
		static constexpr auto value = T * factorial<T - 1>::value;
	};

	template<>
	struct factorial<0>
	{
		static constexpr auto value = 1;
	};
} // namespace mlib