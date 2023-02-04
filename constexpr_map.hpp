#pragma once

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

    template<auto X>
    struct constant_parameter
    {
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