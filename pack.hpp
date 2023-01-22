// pack.hpp

#pragma once

#include <cstddef>
#include <iostream>
#include <utility>

#include"get_nth_element.hpp"

namespace mlib {

    template <auto I> struct index_pack {};

    template <auto... Ts> struct value_pack {

        static constexpr auto begin_value = mlib::get_nth_element<0>(Ts...);
        static constexpr auto end_value =
            mlib::get_nth_element<sizeof...(Ts) - 1>(Ts...);
        static constexpr auto size_value = sizeof...(Ts) - 1;

        constexpr auto size() { return (sizeof(Ts) + ... + 0); }

        constexpr auto begin() { return begin_value; }
        constexpr auto end() { return end_value; };

        template <auto I> constexpr auto operator[](index_pack<I>) {
            return mlib::get_nth_element<I>(Ts...);
        }

        template <auto I> constexpr auto get() {
            return mlib::get_nth_element<I>(Ts...);
        }

        value_pack() { /*Does Nothing!*/ }
    };
} // namespace mlib