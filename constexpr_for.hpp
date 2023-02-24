#pragma once

#include<utility>
#include<cstddef>

namespace mlib
{

    struct with_indexes {};

    template<auto... Values>
    struct sequence
    {
        constexpr auto operator()()
        {
            (Values(), ...);
        }

        // requires `indexes` to be the same length as `Values`
        template<std::size_t... indexes>
        constexpr auto operator()(std::index_sequence<indexes...>)
        {
            (Values(indexes), ...);
        }
    };

    template<auto Val, auto condition, auto operation, auto to_do, auto... operations>
    constexpr auto make_sequence_impl()
    {
        if constexpr (condition(Val))
        {
            return make_sequence_impl<operation(Val), condition, operation, to_do, operations..., to_do>();
        }
        else
        {
            return sequence<operations...>{};
        }
    }

    template<auto Val, auto condition, auto operation, auto to_do>
    constexpr auto make_sequence()
    {
        if constexpr (condition(Val))
        {
            return make_sequence_impl<condition(Val), condition, operation, to_do>();
        }
        else
        {
            return []() {};
        }
    }

    template<auto Val, auto condition, auto operation>
    struct constexpr_for
    {
        constexpr constexpr_for(auto loop_operation)
        {
            auto s = make_sequence<Val, condition, operation, loop_operation>();
            auto x = []<auto... Is>(sequence<Is...> s_)
            {
                s_();
            };
            x(s);
        }

        constexpr constexpr_for(auto loop_operation, with_indexes)
        {
            auto s = make_sequence<Val, condition, operation, loop_operation>();
            auto x = []<auto... Is>(sequence<Is...> s_)
            {
                constexpr auto x = std::make_index_sequence<sizeof...(Is)>{};
                s_(x);
            };
            x(s);
        }
    };
} // namespace mlib