#pragma once

#include <cstddef>      // std::size_t
#include <iostream>     // std::cout
#include <tuple>        // std::tuple
#include <type_traits>  // std::is_aggregate
#include <utility>      // std::index_sequence

#include"constructable_with.hpp"

namespace mlib {
    namespace meta {
        template <typename T>
        constexpr auto refl_get(T t) {
            if constexpr (number_of_aggregate_members<T> == 1) {
                auto [a] = t;
                return a;
            }
            else if constexpr (number_of_aggregate_members<T> == 2) {
                auto [a, b] = t;
                return std::tuple<decltype(a), decltype(b)>{a, b};
            }
            else if constexpr (number_of_aggregate_members<T> == 3) {
                auto [a, b, c] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c)>{a, b, c};
            }
            else if constexpr (number_of_aggregate_members<T> == 4) {
                auto [a, b, c, d] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d)>{
                    a, b, c, d};
            }
            else if constexpr (number_of_aggregate_members<T> == 5) {
                auto [a, b, c, d, e] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d),
                    decltype(e)>{a, b, c, d, e};
            }
            else if constexpr (number_of_aggregate_members<T> == 6) {
                auto [a, b, c, d, e, f] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d),
                    decltype(e), decltype(f)>{a, b, c, d, e, f};
            }
            else if constexpr (number_of_aggregate_members<T> == 7) {
                auto [a, b, c, d, e, f, g] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d),
                    decltype(e), decltype(f), decltype(g)>{a, b, c, d,
                    e, f, g};
            }
            else if constexpr (number_of_aggregate_members<T> == 8) {
                auto [a, b, c, d, e, f, g, h] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d),
                    decltype(e), decltype(f), decltype(g), decltype(h)>{
                    a, b, c, d, e, f, g, h};
            }
            else if constexpr (number_of_aggregate_members<T> == 9) {
                auto [a, b, c, d, e, f, g, h, i] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d),
                    decltype(e), decltype(f), decltype(g), decltype(h),
                    decltype(i)>{a, b, c, d, e, f, g, h, i};
            }
            else if constexpr (number_of_aggregate_members<T> == 10) {
                auto [a, b, c, d, e, f, g, h, i, j] = t;
                return std::tuple<decltype(a), decltype(b), decltype(c), decltype(d),
                    decltype(e), decltype(f), decltype(g), decltype(h),
                    decltype(i), decltype(j)>{a, b, c, d, e,
                    f, g, h, i, j};
            }
        }
        template <int index>
        constexpr auto get(auto& obj)
        {
            return std::get<index>(refl_get<decltype(obj)>(obj));
        }

    }  // namespace meta
}  // namespace mlib