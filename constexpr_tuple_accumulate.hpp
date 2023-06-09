#pragma once

#include <tuple>  // std::tuple

namespace mlib {
    template <typename... Ts>
    constexpr auto constexpr_tuple_accumulate(std::tuple<Ts...> tup) {
        return[=]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return (std::get<indexes>(tup) + ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }
}  // namespace mlib