#pragma once

namespace mlib
{
	template<typename T>
	struct type
	{
		auto operator==(auto& t)
			requires(decltype(t){} == T)
		{
			return true;
		}

		auto operator==()
		{
			return false;
		}
	};

	template<typename T>
	static constexpr type<T> type_c = type<T>{};
} // namespace mlib