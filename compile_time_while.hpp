#pragma once


#include<tuple>
#include<utility>
#include<cstddef>
#include<iostream>

namespace mlib
{

	template<auto start_value, auto condition_for_val, auto operation_on_val>
	struct pack
	{
		constexpr auto operator()()
		{
			if constexpr (!condition_for_val(start_value))
			{
				return 0;
			}
			else
			{
				return 1 + pack<operation_on_val(start_value), condition_for_val, operation_on_val>{}();
			}
		}
	};

	template<auto Care, auto DontCare>
	struct any_first
	{
		constexpr auto operator()()
		{
			return Care;
		}
	};

	template<auto iterations, auto lambda>
	constexpr auto make_tuple_sequence()
	{
		return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
		{
			return std::tuple{ (any_first<lambda, indexes>{}())... };
		}(std::make_index_sequence<iterations>{});
	}

	template<typename... Ts>
	constexpr auto for_each_lambda(std::tuple<Ts...> tup)
	{
		[&] <std::size_t... indexes>(std::make_index_sequence<indexes...>)
		{
			(std::get<indexes>(tup)(), ...);
		}(std::make_index_sequence<sizeof...(Ts)>{});
	}

	template<auto start_value, auto condition_for_val, auto operation_on_val>
	struct compile_time_while
	{
		constexpr auto operator()(auto operation_to_do)
		{
			// first of all, make a value that is how many times the operations are true.
			constexpr auto amount_of_iterations = pack<start_value, condition_for_val, operation_on_val>{}();
			// so now that we have the number of iterations, we need to make a tuple of size: amount_of_iterations
			// and then we need to do a for_each on them! simple!
			constexpr auto tuple_sequence = make_tuple_sequence<amount_of_iterations, operation_to_do>();
			// now do for_each
			for_each_lambda(tuple_sequence);
		}
	};
} // namespace mlib
