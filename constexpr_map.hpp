#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace mlib
{
    template <auto X> struct constexpr_parameter 
    {
        using type = decltype(X);
    };

    template<auto T>
    static constexpr auto c_p = constexpr_parameter<T>{};

    template <auto A, auto B> struct member_map {
        constexpr auto operator[](constexpr_parameter<A>) const noexcept {
            return B;
        }
    };

    // a member with a variadic number of elements, not used here though.
    template <auto... members_of> struct variadic_member
    {
    };

    template<auto member> struct single_member
    {
        constexpr auto operator[](constexpr_parameter<member>) const noexcept
        {
            return member;
        }
    };

    template<typename... members>
    struct inheriter : members...
    {
        using members::operator[]...;
    };

    template<typename T>
    struct constexpr_map_base_
    {
        using type = decltype(componentContainer<T>());
    };

    template <auto... members>
    struct constexpr_map : constexpr_parameter<members>::type... {
        using decltype(members)::operator[]...;

        template <auto T>
        constexpr auto lookup() const noexcept {
            return this->operator[](constexpr_parameter<T>{});
        }
    };
} // namespace mlib