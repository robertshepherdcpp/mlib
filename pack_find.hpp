#pragma once

#include<utility>
#include<cstddef>

namespace mlib
{
    template<auto A, auto...B>
    struct first
    {
        constexpr auto operator()()
        {
            return A;
        }
    };

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

    template<auto value_to_find, auto... pack>
    constexpr auto pack_find()
    {
        constexpr auto x = [&]<std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            return (value_is_value<indexes, pack, value_to_find>{}() + ...);
        }(std::make_index_sequence<sizeof...(pack)>{});
        if constexpr ((x == 0) && mlib::first<pack...>{}() == value_to_find)
        {
            return -1;
        }

        return x;
    }
} // namespace mlib