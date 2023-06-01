#pragma once

#include<tuple> // std::tuple

namespace mlib
{
    constexpr auto equal(auto a, auto b)
    {
        return a == b;
    }

    template <typename As, typename Bs>
    constexpr auto tuple_equal(As tup_a, Bs tup_b)
    {
        constexpr auto pack_size_a = []<typename... Ts>(std::tuple<Ts...>) { return sizeof...(Ts); }(tup_a);
        constexpr auto pack_size_b = []<typename... Ts>(std::tuple<Ts...>) { return sizeof...(Ts); }(tup_b);
        if constexpr (pack_size_a != pack_size_b) {
            return false;
        }
        else {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return ((equal(std::get<indexes>(tup_a), std::get<indexes>(tup_b))) && ...);
            }(std::make_index_sequence<pack_size_a>{});
        }
    }
} // namespace mlib