#pragma once

namespace mlib
{
	template<auto T>
	struct constant_parameter
	{
		using type = decltype(T);
	};
}