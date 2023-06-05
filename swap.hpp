#include<cstddef> // std::size_t
#include<utility> // std::index_sequence
#include<tuple>   // std::tuple

#include"get_nth_element.hpp"

namespace mlib
{
    // a class to hold compile time data
    template<auto... Ts>
    struct container
    {
        template<auto X>
        constexpr auto get()
        {
            return mlib::get_nth_element<X>(Ts...);
        }
    };

    // this is a compile time parameter that is easy to pass into things
    template<auto X>
    struct c_p__
    {
    };

    // when condition(value) returns TrueValue, else returns FalseValue
    template<auto value, auto condition, auto other_condition, auto TrueValue, auto SecondTrueValue, auto FalseValue>
    struct when_
    {
        constexpr auto operator()()
        {
            if constexpr (condition(value))
            {
                return TrueValue;
            }
            if constexpr (other_condition(value))
            {
                return SecondTrueValue;
            }
            else
            {
                return FalseValue(c_p__<value>{});
            }
        }
    };

    // this function swaps Index and Other index then returns the tuple.
    template<auto Index, auto OtherIndex, auto... Ts>
    constexpr auto swap() // -> container
    {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            return container < (when_ < indexes, [=](auto x) {return x == Index; }, [=](auto x) {return x == OtherIndex; }, mlib::get_nth_element<OtherIndex>(Ts...), mlib::get_nth_element<Index>(Ts...), [=]<auto X>(c_p__<X>) { return mlib::get_nth_element<X>(Ts...); } > {}())... > {};
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }
} // namespace mlib