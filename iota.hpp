#pragma once

#include<tuple>
#include<cstddef>
#include<utility>

template<auto until>
constexpr auto iota()
{
    return[]<std::size_t... indexes>(std::index_sequence<indexes...>)
    {
        return std::make_tuple(indexes...);
    }(std::make_index_sequence<until>{});
}