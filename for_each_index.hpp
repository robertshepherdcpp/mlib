#pragma once

#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>

namespace mlib {
    template <auto lamda, typename... Ts>
    constexpr auto for_each_index(std::tuple<Ts...> tuple) {
        [&] <std::size_t... indexes>(std::index_sequence<indexes...>) {
            (lamda(indexes, std::get<indexes>(tuple)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }
} // namespace mlib