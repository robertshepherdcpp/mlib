#pragma once

#include <iostream>

namespace mlib
{
    template <auto T> struct constexpr_parameter {
        using type = decltype(T);
    };

    template <auto T> struct case_ {
        using type = decltype(T);
    };

    template <auto callable> struct switcher {
        constexpr auto operator()(constexpr_parameter<callable>) {
            return callable();
        }
    };

    template <auto... members>
    struct switch_expressions : constexpr_parameter<members>::type... {
        using decltype(members)::operator()...;
    };

    // a constexpr switch
    template <auto value, auto... cases> struct constexpr_switch {
        switch_expressions<cases...> m{};

        constexpr auto operator()() { return m(case_<value>{}); }
    };
} // namespace mlib