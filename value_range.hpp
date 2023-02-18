#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>

#include"get_nth_element.hpp"

namespace mlib {
    template <auto... Ts> struct value_range {
        constexpr auto operator|(auto lambda) const { return for_each<lambda>(); }

        template <auto lambda> constexpr auto for_each() const {
            return value_range<lambda(Ts)...>{};
        }

        template <auto I> constexpr auto at() const { return get_nth_element(Ts...); }

        constexpr auto tuple() const { return std::make_tuple(Ts...); }
    };
} // namespace mlib