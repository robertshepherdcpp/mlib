#pragma once

namespace mlib
{
    template <typename T, T I> struct integral_constant {
        static constexpr T value = I;
        using value_type = T;

        constexpr operator value_type() const noexcept { return value; }

        constexpr auto operator()() const noexcept { return value; }
    };
} // namespace mlib