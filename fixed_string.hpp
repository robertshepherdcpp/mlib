#include<cstddef>

namespace mlib
{
    template<std::size_t i>
    struct fixed_string
    {
        constexpr fixed_string(const char(&arr)[i + 1])
        {
            std::copy_n(arr, i + 1, data);
        }

        auto operator<=>(const fixed_string&) const = default;

        char data[i + 1] = {};
    };
} // namespace mlib