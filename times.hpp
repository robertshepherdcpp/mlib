#pragma once

#include<utility>
#include<cstddef>

namespace mlib
{

    template<auto T>
    struct times
    {
        constexpr auto operator()(auto callable)
        {
            [&] <std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                (callable, void(indexes), ...);
            }(std::make_index_sequence<T>{});
        }
    };
} // namespace mlib