#pragma once

#include<utility> // std::integer_sequence
#include<cstddef> // std::size_t
#include<tuple>   // std::tuple
#include<type_traits> // std::declval

namespace mlib
{
	template<typename... Ts>
	struct tuple_reverse;

	template<>
	struct tuple_reverse<std::tuple<>>
	{
		using type = std::tuple<>;
	};

	template<typename T, typename... Ts>
	struct tuple_reverse < std::tuple<T, Ts...> >
	{
		using head = tuple<T>;
		using tail = tuple_reverse<std::tuple<Ts...>>::type;

		using type = decltype(std::tuple_cat(std::declval<tail>(), std::declval<head>()));
	};

	template<typename T, size_t... I>
	constexpr auto reverse_tuple_value_impl(T&& t, std::index_sequence<I...>)
	{
		return std::make_tuple(std::get<sizeof...(I) - 1 - I>(std::forward<T>(t))...);
	}

	template<typename T>
	constexpr auto reverse_tuple_value(T&& t)
	{
		return reverse_impl(std::forward<T>(t),
			std::make_index_sequence<std::tuple_size<T>::value>());
	}
}