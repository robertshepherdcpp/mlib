#pragma once

#include<utility>
#include<cstddef>

namespace mlib
{
    // a replacement for mlib::for_each rather than making a tuple with a pack.
    constexpr auto enumerate_pack(auto callable, auto... pack)
    {
        [&] <std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            (callable(indexes, pack), ...);
        }(std::make_index_sequence<sizeof...(pack)>{});
    }
} // namespace mlib