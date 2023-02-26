#pragma once

#include<utility>
#include<cstddef>

namespace mlib
{
    // this allows no recursion
    struct callable_wrapper
    {
        constexpr callable_wrapper() {}

        constexpr auto operator()(auto callable, std::size_t index)
        {
            callable();
        }
    };

    template<auto T>
    struct times
    {
        constexpr auto operator()(auto callable)
        {
            [&] <std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                (callable_wrapper{}(callable, indexes), ...);
            }(std::make_index_sequence<T>{});
        }
    };
} // namespace mlib