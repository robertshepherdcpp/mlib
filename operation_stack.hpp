#pragma once

#include<utility>
#include<cstddef>
#include<iostream>

#include"constant_parameter.hpp"

namespace mlib
{
struct run_all_t {};
static constexpr auto run_all = run_all_t{};

template<auto callable, auto... operations>
constexpr auto for_each_pack()
{
    [&] <std::size_t... indexes>(std::index_sequence<indexes...>)
    {
        (callable(operations), ...);
    }(std::make_index_sequence<sizeof...(operations)>{});
}

    template<auto... operations>
    struct operation_stack
    {
        template<auto T>
        constexpr auto enque(mlib::constexpr_parameter<T>)
        {
            return operation_stack<operations, T>{};
        }

        template<auto type>
        constexpr auto run()
        {
            for_each_pack < [](auto& x) {x(); }, operations... > ();
        };

    };
} // namespace mlib