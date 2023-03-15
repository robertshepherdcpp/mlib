#pragma once

#include <cstddef>  // std::size_t
#include <iostream> // std::cout
#include <tuple>    // std::tuple
#include <utility>  // std::index_sequence

namespace mlib
{
    template <auto V, auto T, typename... Ts>
    constexpr auto sub_tuple(std::tuple<Ts...> t) {
        static_assert(T < sizeof...(Ts), "Invalid Index range");
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::tuple{ std::get<indexes + V>(t)... };
        }(std::make_index_sequence<T>{});
    }
} // namespace mlib