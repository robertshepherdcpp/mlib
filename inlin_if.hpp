#pragma once

namespace mlib
{
    struct SameAs {};

    // this is a bad implementation, becuase it requires operator==
    template <typename A, typename B> struct is_same {
        static constexpr bool value = false;
    };

    template <typename A, typename B>
        requires(A{} == B{})
    struct is_same<A, B> {
        static constexpr bool value = true;
    };

    template <typename T, typename condition, typename ToCompare, auto first_,
        auto second_>
    struct inline_if {
        constexpr inline_if() {}

        constexpr auto get() {
        }
        constexpr auto operator()() { return get(); }

        static constexpr auto first = first_;
        static constexpr auto second = second_;
    };

    template<typename T, typename ToCompare, auto first_, auto second_>
    struct inline_if<T, is_same<T, ToCompare>, ToCompare, first_, second_>
    {
        constexpr inline_if() {}

        constexpr auto get() {
            if constexpr (is_same<T, ToCompare>::value) {
                return first;
            }
            else if constexpr (!is_same<T, ToCompare>::value) {
                return second;
            }
            constexpr auto operator()() { return get(); }

            static constexpr auto first = first_;
            static constexpr auto second = second_;
        };
    } // namespace mlib