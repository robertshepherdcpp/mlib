#pragma once

#include"constant_parameter.hpp"

namespace mlib
{
    template<typename A, typename B>
    struct member_map
    {
        A first;
        B second;
    };

    template<typename A>
    struct single_member_map
    {
        A first;
    };

    template<auto... members>
    struct constexpr_map : decltype(members)...
    {
        template<auto X>
        constexpr auto operator[](constant_parameter<X>)
        {
            return get_nth_element<X>(members...).first;
        }

        template<auto X>
        constexpr auto first(constant_parameter<X>)
        {
            return get_nth_element<X>(members...).first;
        }

        template<auto X>
        constexpr auto second(constant_parameter<X>)
        {
            return get_nth_element<X>(members...).second;
        }
    };
} // namespace mlib