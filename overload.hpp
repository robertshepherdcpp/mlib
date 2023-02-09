#pragma once

namespace mlib
{
	template<typename... Ts>
	struct overload : Ts...
	{
		using Ts::operator()...;
	};
} // namespace mlib