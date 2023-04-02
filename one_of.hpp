#pragma once

namespace mlib
{
	template<bool... c>
	struct one_of
	{
		static constexpr bool value = (c ||...);
	};
} // namespace mlib