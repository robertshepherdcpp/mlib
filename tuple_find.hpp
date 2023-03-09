#pragma once

#include<utility>
#include<cstddef>
#include<tuple>

#include"pack_find.hpp"
#include"get_nth_element.hpp"

namespace mlib
{
    template<auto value_to_find, typename... pack>
    constexpr auto tuple_find(std::tuple<pack...> t)
    {
        constexpr auto x = [&]<std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            return (mlib::value_is_value<indexes, std::get<indexes>(t), value_to_find>{}() + ...);
        }(std::make_index_sequence<sizeof...(pack)>{});
        if constexpr (x == 0 && std::get<0>(t) != value_to_find)
        {
            return -1;
        }

        return x;
    }
} // namespace mlib