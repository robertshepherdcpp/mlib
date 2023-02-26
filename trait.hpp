#pragma once
// only works on Clang and MSVC, not GCC

namespace mlib
{
    template<auto T>
    struct trait_module
    {
        constexpr auto operator()(auto X) const
        {
            // we call our NTTP
            T(X);
            return true;
        }
    };


    template<auto T, auto... trait_modules>
        requires((trait_modules(T), ...))
    struct trait
    {
        constexpr trait() {}

        static constexpr auto value = true;
    };
} // namespace mlib