#pragma once

#include<utility> // std::index_sequence
#include<cstddef> // std::size_t
#include<type_traits> // std::remove_cv_reference

namespace mlib
{
	template <typename... T, std::size_t ...i>
	auto select(std::tuple<T...> tuple, std::index_sequence<i...>) 
	{
	    using result = std::tuple<std::tuple_element_t<i, std::remove_reference_t<decltype(tuple)>>...>;
	    return result{ std::get<i>(tuple)... };
	}
} // namespace mlib