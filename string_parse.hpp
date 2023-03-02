#pragma once

#include <algorithm>
#include <array>
#include <compare>
#include <cstddef>

#include"fixed_string.hpp"

namespace mlib
{

    template <fixed_string str, char c, int index>
    constexpr auto find_index_arr() {
        if constexpr (str.template nth_element<index>() == c) {
            return index;
        }
        else {
            return find_index_arr<str, c, index + 1>();
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

    template <fixed_string str> struct string_parse {
        template <auto A, auto B> constexpr auto substr()
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return std::array{ (str.template nth_element<A + indexes>())... };
            }(std::make_index_sequence<B - A>{});
        }

        template <char c> constexpr auto consume_until() {
            constexpr int index = find_index_arr<str, c>();
            return substr<0, index>();
        }

        constexpr auto number_of_characters() {
            return str.size();
        }
    };
} // namespace mlib