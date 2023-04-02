#pragma once

#include<utility>
#include<cstddef>

namespace mlib
{
    template<auto Num>
    struct loop
    {
        constexpr loop(auto lambda)
        {
            [&] <std::size_t... indexes>(std::index_sequence<indexes>)
            {
                (lambda, void(indexes), ...);
            }(std::make_index_sequence<Num>{});
        }
    };
} // namespace mlib