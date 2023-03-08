#pragma once

#include<utility>
#include<cstddef>
#include<tuple>

#include"get_nth_element.hpp"

namespace mlib
{
    template<auto Index, auto value, auto value_two>
    struct value_is_value
    {
        constexpr auto operator()() const
        {
            if constexpr (decltype(value_two)(value) == value_two)
            {
                return Index;
            }
            else
            {
                return 0;
            }
        }

        constexpr value_is_value() {}
    };

    template<auto value_to_find, typename... pack>
    constexpr auto tuple_find(std::tuple<pack...> t)
    {
        constexpr auto x = [&]<std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            return (value_is_value<indexes, std::get<indexes>(t), value_to_find>{}() + ...);
        }(std::make_index_sequence<sizeof...(pack)>{});
        if constexpr (x == 0 && std::get<0>(t) != value_to_find)
        {
            return -1;
        }

        return x;
    }
} // namespace mlib