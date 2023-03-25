#pragma once

#include"fixed_string.hpp"
#include"string_parse.hpp"

namespace mlib
{
    template <fixed_string str>
    struct parse_rules {
        template<char c>
        constexpr auto if_has_character(auto lambda)
        {
            if constexpr (string_parse<str>{}.template character_occurences<c>() > 1)
            {
                return parse_rules<lambda(str)>{};
            }
            else
            {
                return parse_rules<str>{};
            }
        }

        template<auto c>
        constexpr auto has_sizeof(auto lambda)
        {
            if constexpr (str.size())
            {
                return lambda(str);
            }
            else
            {
                return str;
            }
        }
    };
} // namespace mlib