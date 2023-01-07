#pragma once

namespace mlib
{
	template<auto T>
	struct fibonacci
	{
		static constexpr auto value = T + fibonacci<T - 1>::value;
	};

	template<>
	struct fibonacci<0>
	{
		static constexpr auto value = 0;
	};
} // namespace mlib