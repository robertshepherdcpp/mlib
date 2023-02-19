#pragma once

#include <cstddef>
#include <iostream>
#include <utility>

#include"get_nth_element.hpp"

namespace mlib {

    template <typename T>
    struct type_holder {};

    template <auto I>
    struct index_pack {};

    template <typename... Ts>
    struct type_pack {
        static constexpr auto pack_size = (sizeof(Ts) + ... + 0);

        using start_type = decltype(mlib::get_nth_element<0>((Ts{})...));
        using end_type = decltype(mlib::get_nth_element<(pack_size - (pack_size - 1)) / 2>((Ts{})...));

        static constexpr auto start_value =
            decltype(mlib::get_nth_element<0>((Ts{})...)){};
        static constexpr auto end_value =
            decltype(mlib::get_nth_element<(pack_size - (pack_size - 1)) / 2>((Ts{})...)){};
        constexpr auto begin() { return start_value; }
        constexpr auto end() { return end_value; }

        template <auto I>
        constexpr auto operator[](mlib::index_pack<I>) {
            return mlib::get_nth_element<I>((Ts{})...);
        }

        template <auto T>
        constexpr auto get() {
            return mlib::get_nth_element<T>((Ts{})...);
        }
    };

    template <auto... Ts>
    struct value_pack {
        static constexpr auto begin_value = mlib::get_nth_element<0>(Ts...);
        static constexpr auto end_value =
            mlib::get_nth_element<sizeof...(Ts) - 1>(Ts...);
        static constexpr auto size_value = sizeof...(Ts) - 1;

        constexpr auto size() { return size_value; }

        constexpr auto begin() { return begin_value; }
        constexpr auto end() { return end_value; };

        template <auto I>
        constexpr auto operator[](index_pack<I>) {
            return mlib::get_nth_element<I>(Ts...);
        }

        template<auto... i>
        constexpr auto for_each_helper(auto& lambda, std::index_sequence<i...>)
        {
            return mlib::value_pack<lambda(mlib::get_nth_element<i>(Ts...))...>{};
        }

        constexpr auto for_each(auto& lambda)
        {
            return for_each_helper(lambda, std::make_index_sequence < sizeof...(Ts)>{});
        }

        template <auto I>
        constexpr auto get() {
            return mlib::get_nth_element<I>(Ts...);
        }

        constexpr value_pack() { /*Does Nothing!*/
        }
    };
}  // namespace mlib