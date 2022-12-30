#pragma once

#include<utility> // std::forward

namespace mlib
{
	template<typename T, typename... Ts>
	struct tuple
	{
		T first{};
		tuple<Ts...> second{};
	};

	template<typename T>
	struct tuple<T>
	{
		T first{};
	};

	template<typename... Types>
	constexpr auto make_tuple(Types... types)
	{
		return tuple<Types...>{std::forward<Types...>(types...)};
	}

	template<typename Type>
	constexpr auto make_tuple(Type type)
	{
		return tuple<Type>{std::forward<Type>(type)};
	}

	template< int I, typename T >
	struct tuple_element;

	template< int I, typename Head, typename... Tail >
	struct tuple_element<I, tuple<Head, Tail...>> : tuple_element<I - 1, tuple<Tail...>> 
	{ 
	};

	template< typename Head, typename... Tail >
	struct tuple_element<0, tuple<Head, Tail...>> 
	{
		using type = Head;
	};

	template<int I, typename... Ts>
	using tuple_element_t = tuple_element<I, Ts...>::type;
} // namespace mlib