#pragma once

#include<utility>
#include<cstddef>

namespace mlib {
    template <auto N> constexpr auto get_nth_element(auto... args) {
        return[&]<std::size_t... Indexes>(std::index_sequence<Indexes...>) {
            return [](decltype((void*)Indexes)... DontCare, auto* arg,
                auto *...DontCareEither) { return *arg; }(&args...);
        }(std::make_index_sequence<N>{});
    }
} // namespace mlib