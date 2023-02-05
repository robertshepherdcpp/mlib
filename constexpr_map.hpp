#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>

namespace mlib
{
    template <auto X> struct constexpr_parameter {};

    template <auto A, auto B> struct member_map {
        constexpr auto operator[](constant_parameter<A>) const noexcept {
            return B;
        }
    };

    // a member with a variadic number of elements, not used here though.
    template <auto... members_of> struct variadic_member
    {

    };

    template<auto members> struct single_member
    {
        constexpr auto operator[](constant_parameter<members>) const noexcept
        {
            return members;
        }
    };

    template <auto... members> struct constexpr_map : decltype(members)... {
        using decltype(members)::operator[]...;

        template <auto T> constexpr auto lookup() const noexcept {
            return this->operator[](constexpr_parameter<T>{});
        }
    };
} // namespace mlib