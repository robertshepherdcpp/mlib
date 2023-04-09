#pragma once

namespace mlib {
    template <auto T>
    struct constexpr_parameter {
        using type = decltype(T);
    };

    template <typename T>
    struct type {};

    template <auto... members>
    struct switch_expressions : constexpr_parameter<members>::type... {
        using decltype(members)::operator()...;
    };

    template <auto... cases>
    struct constexpr_type_switch {
        switch_expressions<cases...> m{};

        template <typename value>
        constexpr auto operator()(type<value>) {
            return m(type<value>{});
        }
    };
}  // namespace mlib