#pragma once

#include <utility>  // std::index_sequence
#include <tuple>    // std::tuple
#include <cstddef>  // std::size_t

namespace mlib {
    template <auto... Vs>
    constexpr auto apply(auto lambda, std::index_sequence<Vs...>)
        -> decltype(lambda.template operator() < Vs... > ())
    {
        return lambda.template operator() < Vs... > ();
    }
}  // namespace mlib