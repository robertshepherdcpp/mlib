#pragma once

#include<cstddef>
#include<algorithm>

namespace mlib
{
    template<std::size_t i>
    struct fixed_string
    {
        constexpr fixed_string(const char(&arr)[i + 1])
        {
            std::copy_n(arr, i + 1, data);
        }

        constexpr auto size() const { return i; }

        template<auto I>
        constexpr auto nth_element() const
        {
            return data[I];
        }

        auto operator<=>(const fixed_string&) const = default;

        char data[i + 1] = {};
    };

    template<std::size_t i>
    fixed_string(const char(&arr)[i])->fixed_string<i - 1>;
} // namespace mlib