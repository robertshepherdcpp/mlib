#pragma once

#include<utility> // std::index_sequence
#include<cstddef> // std::size_t

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
        [] <std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            (lambda(), void(indexes), ...);
        }(std::make_index_sequence<T>{});
        return true;
    }
}; // namespace mlib