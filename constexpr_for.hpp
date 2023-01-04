#pragma once

#include<iostream>

// Use constexpr while instead.

namespace mlib
{

    template<auto... Values>
    struct sequence
    {
        constexpr auto operator()()
        {
            (Values(), ...);
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
            return sequence{ operations... };
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
    };
}
