#pragma once

#include<iostream>

namespace mlib
{
    template<auto Value, auto Condition, auto ToDo, auto operation>
    constexpr auto constexpr_while_helper()
    {
        if constexpr (Condition(Value))
        {
            ToDo();
            constexpr_while_helper<operation(Value), Condition, ToDo, operation>();
        }
        else
        {
            // we end loop
        }
    }

    template<auto Value, auto Condition, auto ToDo, auto operation>
    struct constexpr_while
    {
        constexpr constexpr_while()
        {
            if constexpr (Condition(Value))
            {
                constexpr_while_helper<operation(Value), Condition, ToDo, operation>();
            }
            else
            {
                // we end the program.
            }
        }
    };
} // namespace mlib