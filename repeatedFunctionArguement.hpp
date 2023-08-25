#pragma once

#include<utility>    // std::index_sequence
#include<functional> // std::function

namespace mlib
{
    template<typename Type, auto value>
    struct always_type_t
    {
        using type = Type;
    };

    template<typename Type, auto value>
    using always_type = always_type_t<Type, value>::type;

    template<typename returnType, typename argType, auto N>
    struct repeatedFunctionArgument
    {
        constexpr repeatedFunctionArgument(auto function) { m_function = std::function{ function }; }
        template<typename... Ts> constexpr returnType callFunction(Ts... args) const noexcept { return m_function(args); }

        using type = decltype(
            []<std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            return std::function<int(always_type<int, indexes>... args)>{};
        }(std::make_index_sequence<N>{})
            );

        type m_function;
    };
} // namespace mlib