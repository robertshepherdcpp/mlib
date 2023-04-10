#pragma once

#include <cstddef>      // std::size_t
#include <iostream>     // std::cout
#include <type_traits>  // std::is_aggregate
#include <utility>      // std::index_sequence

namespace mlib
{
    template <std::size_t i>
    struct convertible_to_anything {
        template <typename T>
        operator T() {};
    };

    template <typename T, std::size_t I>
    concept is_constructable_with = requires {
        [] <std::size_t... is>(std::index_sequence<is...> i_s)
            -> decltype(T{ convertible_to_anything<is>{}... }) {
            return {};
        }(std::make_index_sequence<I>{});
    };

    template <typename T, std::size_t n>
    concept aggregate_of = std::is_aggregate_v<T> && is_constructable_with<T, n> &&
        !is_constructable_with<T, n + 1>;

    template <typename T>
    constexpr auto number_of_aggregate_members =
        []<std::size_t... indexes>(std::index_sequence<indexes...> i_s) {
        return ((aggregate_of<T, indexes> *indexes) + ... + 0);
    }(std::make_index_sequence<12>{});
} // namespace mlib