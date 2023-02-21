// count_if.hpp
#pragma once

#include <cstddef>
#include <tuple>
#include <utility>

namespace mlib {
    template <typename... Ts>
    constexpr auto count_if(auto callable, std::tuple<Ts...>& tuple) {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return (callable(std::get<indexes>(tuple)) + ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }

    constexpr auto count_if(auto callable, auto... Ts)
    {
        return (callable(Ts) + ...);
    }
}  // namespace mlib