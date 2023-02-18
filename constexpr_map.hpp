#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#include "get_nth_element.hpp"

namespace mlib {

    template <auto X> struct constexpr_parameter {
        using type = decltype(X);
    };

    template <auto T> static constexpr auto c_p = constexpr_parameter<T>{};

    template <auto A, auto B> struct member_map {
        constexpr auto operator[](constexpr_parameter<A>) const noexcept {
            return B;
        }

        constexpr auto key() { return A; }
        constexpr auto value() { return B; }

        template<auto X> constexpr auto has_key() { return X == A; }
        template<auto X> constexpr auto has_value() { return X == B; }
    };

    template<bool T>
    constexpr auto is_not_void(constexpr_parameter<T>)
    {
        return true;
    }

    template<auto T>
    constexpr auto is_not_void(constexpr_parameter<T>)
    {
        return false;
    }

    template <auto... members>
    struct constexpr_map : constexpr_parameter<members>::type... {
        using decltype(members)::operator[]...;

        template<auto T> constexpr auto get_member() const noexcept -> decltype(auto)
        {
            return mlib::get_nth_element<T>(members...);
        }

        template <auto T> constexpr auto lookup() const noexcept {
            return this->operator[](constexpr_parameter<T>{});
        }

        template <auto T> constexpr auto get() const noexcept {
            return this->operator[](constexpr_parameter<T>{});
        }

        template <auto T>
        constexpr auto has_value(constexpr_parameter<T>) const noexcept {
            return[]<std::size_t... indexes>(std::index_sequence<indexes...>) {
                return ((mlib::get_nth_element<indexes>(members...).template has_value<T>() || ...)) || get_nth_element<sizeof...(members) - 1>(members...).template has_value<T>();
            }(std::make_index_sequence<sizeof...(members) - 1>{});
        }

        template <auto T>
        constexpr auto has_key(constexpr_parameter<T>) const noexcept {
            return[]<std::size_t... indexes>(std::index_sequence<indexes...>) {
                return ((mlib::get_nth_element<indexes>(members...).template has_key<T>() || ...)) || get_nth_element<sizeof...(members) - 1>(members...).template has_key<T>();
            }(std::make_index_sequence<sizeof...(members) - 1>{});
        }

        constexpr auto get_keys() const noexcept {
            return[]<std::size_t... indexes>(std::index_sequence<indexes...>) {
                return std::make_tuple(
                    (mlib::get_nth_element<indexes>(members...).key())...);
            }(std::make_index_sequence<sizeof...(members)>{});
        }

        constexpr auto get_values() const noexcept {
            return [] <std::size_t... indexes>(std::index_sequence<indexes...>) {
                return std::make_tuple(
                    (mlib::get_nth_element<indexes>(members...).value())...);
            }(std::make_index_sequence<sizeof...(members)>{});
        }
    };
} // namespace mlib