#pragma once

namespace mlib
{
    template<auto Num>
    struct loop
    {
        constexpr loop(auto lambda)
        {
            lambda();
            if constexpr (Num != 1)
            {
                loop<Num - 1>{lambda};
            }
        }
    };
} // namespace mlib