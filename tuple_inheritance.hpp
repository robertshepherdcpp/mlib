#pragma once

#include<cstddef> // std::size_t

namespace mlib
{
    template <std::size_t s, typename T> struct tuple_leaf {
        T value;
    };

    template <std::size_t t, typename... T> struct tuple_impl;

    template <std::size_t t> struct tuple_impl<t> {};

    template <std::size_t t, typename Head, typename... Tails>
    struct tuple_impl<t, Head, Tails...> : public tuple_leaf<t, Head>,
        public tuple_leaf<t + 1, Tails...> {};

    template<std::size_t t, typename Head, typename... Tails>
    Head get(tuple_impl<t, Head, Tails...>& x)
    {
        x.tuple_leaf<t, Head>::value;
    }

    template<typename... Types>
    using Tuple = tuple_impl<0, Types...>;
} // namespace mlib