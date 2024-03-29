#pragma once

#include"constant_parameter.hpp"

namespace mlib
{
    template <auto... members>
    struct switch_expressions : constexpr_parameter<members>::type... {
        using decltype(members)::operator()...;
    };

    // a constexpr switch
    template <auto value, auto... cases> struct constexpr_switch {
        switch_expressions<cases...> m{};

        constexpr auto operator()() { m(constexpr_parameter<value>{}); }
    };
} // namespace mlib