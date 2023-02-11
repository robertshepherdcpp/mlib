#pragma once

namespace mlib
{
    template<typename T>
    struct type_t
    {
        constexpr auto operator==(type_t<T>) const
        {
            return true;
        }
        constexpr auto operator==(auto) const
        {
            return false;
        }

        constexpr type_t() {}
    };

    template<typename T>
    static constexpr auto type = type_t<T>{};
} // namespace mlib