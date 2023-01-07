// a c++20 alternative to mlib::for_each
#pragma once

#include<tuple> // std::tuple

namespace mlib
{
	template <typename Tuple, typename Func>
	constexpr auto on_all(Tuple&& t, Func&& f) -> void
	{
		std::apply([&](auto&&... args) { (f(args), ...); }, std::forward<Tuple>(t));
	}
} // namespace mlib