#pragma once

namespace mlib
{
    template<auto T>
    struct amount
    {
        constexpr auto times(auto&& lambda) const;
    };

    template<auto T>
    static constexpr auto amount_t = amount<T>{};

    template<auto T>
    constexpr auto amount<T>::times(auto&& lambda) const
    {
        lambda();
        if constexpr (T - 1 != 0)
        {
            amount_t<T - 1>.times(lambda);
        }
        return true;
    }
}; // namespace mlib