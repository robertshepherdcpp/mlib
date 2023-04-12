#pragma once

#include <algorithm>
#include <cstddef>
#include <tuple>
#include <utility>

#include"get_nth_element.hpp"

namespace mlib
{
    template <std::size_t i>
    struct fixed_string_ {
        constexpr fixed_string_(const char(&arr)[i + 1]) {
            std::copy_n(arr, i + 1, data);
        }

        constexpr fixed_string_(char(&arr)[i + 1])
        {
            std::copy_n(arr, i + 1, data);
        }

        constexpr auto size() const { return i; }

        auto operator<=>(const fixed_string_&) const = default;

        template<auto J>
        constexpr auto nth_element() const { return data[J]; }

        auto data_()
        {
            return data;
        }

        char data[i + 1] = {};
    };

    template <std::size_t i>
    fixed_string_(const char(&arr)[i])->fixed_string_<i - 1>;

    template <std::size_t i>
    fixed_string_(char(&arr)[i])->fixed_string_<i - 1>;

    template <fixed_string_ s>
    struct manipulate_str {
        constexpr auto operator()()
        {
        }

        template <auto T>
        constexpr auto on_all()
        {
            return[]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                char arr[] = { T(s.template nth_element<indexes>())... };
                return fixed_string_{ arr };
            }(std::make_index_sequence<s.size()>{});
        }

        template<auto I>
        constexpr auto get_until()
        {
            return[]<std::size_t... indexes>(std::index_sequence<indexes...>) {
                char arr[I + 1] = { s.template nth_element<indexes>()... };
                arr[I + 1] = 0;
                return fixed_string_{ arr };
            }(std::make_index_sequence<I>{});
        }

        template<std::size_t... indexes>
        constexpr auto select()
        {
            char arr[sizeof...(indexes)] = {s.template nth_element<indexes>()...};
            return fixed_string_{arr};
        }
    };
} // namespace mlib