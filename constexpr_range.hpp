#include<utility>  // std::index_constexpr_range
#include<cstddef>  // std::size_t
#include<tuple>    // std::tuple
#include<iostream> //std::cout

#include "get_nth_element.hpp"

namespace mlib
{
    template<auto... vals>
    struct constexpr_range;

    template<auto lambda, auto... values>
    constexpr auto make_index_holds_true()
    {
        int index = 0;
        int values_[sizeof...(values)] = {};
        auto function = [&](auto value)
        {
            values_[index] = value;
        };
        (function(values), ...);
        return std::move(values_);
    }

    template<auto... values, typename T, auto Idx>
    constexpr auto get_idxs_out(const T(&arr)[Idx])
    {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
        {
            return (get_nth_element<arr[indexes]>(constexpr_range<values>{}) + ...);
        }(std::make_index_sequence<Idx>{});
    }

    template<auto... vals>
    struct value_constexpr_range
    {
    };

    template<auto val, auto... vals>
    constexpr auto pop_front_(constexpr_range<val, vals...>)
    {
        return constexpr_range<vals...>{};
    }

    struct Size {};

    template<auto... vals>
    struct constexpr_range
    {
        template<auto lambda>
        constexpr auto map()
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return constexpr_range<lambda(vals)...>{};
            }(std::make_index_sequence<sizeof...(vals) > {});
        }

        template<auto lambda>
        constexpr auto map_with_location()
        {
            return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return constexpr_range<lambda(vals, indexes)...>{};
            }(std::make_index_sequence<sizeof...(vals) > {});
        }

        constexpr auto sum()
        {
            constexpr auto value = [&]()
            {
                return (vals + ...);
            }();
            return constexpr_range<value>{};
        }

        constexpr auto tuple()
        {
            return std::tuple{ vals... };
        }

        template<auto value>
        constexpr auto add()
        {
            return constexpr_range<vals..., value>{};
        }

        constexpr auto add(Size)
        {
            return constexpr_range<vals..., sizeof...(vals)>{};
        }

        constexpr auto pop_front()
        {
            return pop_front_(constexpr_range<vals...>{});
        }

        template<auto... values_>
        constexpr auto operator+(constexpr_range<values_...> s) const
        {
            return constexpr_range<vals..., values_...>{};
        }

        template<auto... values_>
        constexpr auto join_with(constexpr_range<values_...> s)
        {
            return constexpr_range<vals..., values_...>{};
        }

        template<auto... values_>
        constexpr auto join_with()
        {
            return constexpr_range<vals..., values_...>{};
        }

        template<auto index>
        constexpr auto remove()
        {
            constexpr auto first_part = [&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return constexpr_range<get_nth_element<indexes>(vals...)...>{};
            }(std::make_index_sequence<sizeof...(vals)>{});

            constexpr auto second_part = [&]<std::size_t... indexes>(std::index_sequence<indexes...>)
            {
                return constexpr_range<get_nth_element<indexes + index + 1>(vals...)...>{};
            }(std::make_index_sequence<sizeof...(vals) -index - 1 > {});

            return first_part + second_part;
        }

        template<auto index>
        constexpr auto at()
        {
            return get_nth_element<index>(vals...);
        }
    };
} // namespace mlib