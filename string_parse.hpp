#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>
#include <string>

#include "fixed_string.hpp"
#include "constant_parameter.hpp"

namespace mlib
{
    template <fixed_string str, char c, int index>
    constexpr auto find_index_arr() {
        if constexpr (str.template nth_element<index>() == c) {
            return index;
        }
        else {
            if constexpr (str.size() <= index)
            {
                return -1;
            }
            else
            {
                return find_index_arr<str, c, index + 1>();
            }
        }
    }

    template <fixed_string str, char c>
    constexpr auto find_index_arr() {
        if constexpr (str.template nth_element<0>() == c) {
            return 0;
        }
        else {
            return find_index_arr<str, c, 1>();
        }
    }

    template<char c, std::size_t>
    constexpr auto function_return()
    {
        return c;
    }

    template<bool condition, auto value, char return_>
    struct if_is
    {
        constexpr if_is() {}

        constexpr auto operator()() const noexcept
        {
            if constexpr (condition)
            {
                return value;
            }
            else
            {
                return return_;
            }
        }
    };

    template<typename T, std::size_t I>
    constexpr auto array_to_fixed_string(std::array<T, I>& arr)
    {
        return fixed_string<I>{arr.data()};
    }

    template <fixed_string str>
    struct string_parse {
        template <auto A, auto B>
        constexpr auto substr() const noexcept {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
                return std::array{ (str.template nth_element<A + indexes>())..., '\0' };
            }(std::make_index_sequence<B - A>{});
        }

        template <char c>
        constexpr auto consume_until() const noexcept {
            constexpr int index = find_index_arr<str, c>();
            return substr<0, index>();
        }

        template<char c>
        constexpr auto find() const noexcept
        {
            return find_index_arr<str, c>();
        }

        // make this private
        template<auto Char, auto Index>
        constexpr auto function_return_index() const noexcept
        {
            return Char;
        }

        template<char c, auto lamda>
        constexpr auto if_string_has() const noexcept
        {
            if constexpr (find<c>() != -1)
            {
                return change_with<lamda>();
            }
        }

        template<char c>
        constexpr auto blur_with() const noexcept
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return std::array{ (function_return_index<c, indexes>())..., '\0' };
            }(std::make_index_sequence<str.size()>{});
        }

        template<auto lambda>
        constexpr auto change_with() const noexcept
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return std::array{ (lambda(str.template nth_element<indexes>()))..., '\0' };
            }(std::make_index_sequence<str.size()>{});
        }

        template<auto lambda>
        constexpr auto occurences() const noexcept
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return (lambda.template operator() < str.template nth_element<indexes>() > () + ...);
            }(std::make_index_sequence<str.size()>{});
        }

        template<char c, int X>
        constexpr auto blur_until() const noexcept
        {
            /*
            constexpr auto first_string = [&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return std::array{(function_return_index<c, indexes>())..., '\0'};
            }(std::make_index_sequence<X>{});
            constexpr auto second_string = substr<X, str.size()>();
            */
        }

        template<auto lambda>
        constexpr auto remove_if() const noexcept
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return std::array{ if_is<!lambda(str.template nth_element<indexes>()), str.template nth_element<indexes>(), ' '>{}()..., '\0' };
            }(std::make_index_sequence<str.size()>{});
        }

        template<auto lambda, char c>
        constexpr auto replace_with_if() const noexcept
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return std::array{ if_is<!lambda(str.template nth_element<indexes>()), str.template nth_element<indexes>(), c>{}()..., '\0' };
            }(std::make_index_sequence<str.size()>{});
        }

        constexpr auto string_view()          const noexcept { return std::string_view{ str.data }; }
        constexpr auto string()               const noexcept { return str; }
        constexpr auto number_of_characters() const noexcept { return str.size(); }
    };
} // namespace mlib