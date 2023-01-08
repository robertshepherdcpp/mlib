#pragma once

#include<algorithm> // std::copy_n
#include<cstddef>   // std::size_t

namespace mlib
{
    template<std::size_t i>
    struct fixed_string
    {
        constexpr fixed_string(const char(&arr)[i + 1])
        {
            std::copy_n(arr, i + 1, data);
        }

        auto operator<=>(const fixed_string&) const = default;

        char data[i + 1] = {};
    };

    template<std::size_t i>
    fixed_string(const char(&arr)[i])->fixed_string<i - 1>;

    template<fixed_string str, typename T>
    struct member
    {
        static constexpr auto tag() { return str; }
        T value;
    };

    template<typename... Members>
    struct meta_struct : Members...
    {
    };

    template<fixed_string tag, typename T>
    constexpr decltype(auto) get(member<tag, T>& m)
    {
        return (m.value);
    }

    template<member m, typename Meta_struct>
    constexpr decltype(auto) get(Meta_struct&& meta)
    {
        return get<m>(std::forward<Meta_struct>(meta));
    }
} // namespace mlib