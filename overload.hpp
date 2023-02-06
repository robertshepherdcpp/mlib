#pragma once

namespace mlib
{
	template<auto... Ts>
	struct overload : Ts...
	{
	};
} // namespace mlib