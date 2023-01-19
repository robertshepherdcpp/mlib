# mlib

mlib is a fast, simple c++ meta-programming library that uses c++20.

### Motivating Example

```C++
#include<tuple>    // std::tuple
#include<iostream> // std::cout
#include<utility>  // std::make_index_sequence

#include "for_each.hpp"       // mlib::for_each
#include "tuple.hpp"          // mlib::tuple
#include "transform.hpp"      // mlib::transform
#include "select.hpp"         // mlib::select
#include "find.hpp"           // mlib::find
#include "tuple_reverse.hpp"  // mlib::tuple_reverse
#include "constexpr_for.hpp"  // mlib::constexpr_for
#include "constexpr_while.hpp"// mlib::constexpr_while

int main()
{
	// mlib::for_each
	std::tuple<int, char, bool, double> t{ 42, 'c', true, 3.142 };
	mlib::for_each(t, [](auto& t) { std::cout << "val: " << t << "\n"; });

	// mlib::transform
	std::tuple<int, char, double> t2{ 42, 'c', 3.142 };
	mlib::transform(t2, [](auto& t) {return static_cast<int>(t); });

	// mlib::select
	std::tuple<char, bool, double> t3{ 'c', true, 3.142 };
	auto tuple = mlib::select(t3, std::index_sequence<1, 2>{});
	mlib::for_each(tuple, [](auto& t) {std::cout << "val: " << t << "\n"; });

	// note need to add to to less than:                 --\/, will print one hello.
	mlib::constexpr_while < 0, [&](int t) {t++; return t < 3; }, [&]() {std::cout << "Hello\n"; }, [](int t) {return t + 1; } > ();

	// highest number of recursion.
	mlib::constexpr_while < 0, [&](int t) {t++; return t < 501; }, [&]() {std::cout << "."; }, [](int t) {return t + 1; } > ();
	
	struct foo { int a; double b; char c; };
	foo f{42, 3.14, 'c'};
	char c = std::get<2>(mlib::meta::refl_get<foo>(f));
	
	std::cout << mlib::get_nth_element<2>(42, 'c', 3.14, true); // returns 3.14
}
```
# Documentation

### `mlib::for_each`

`mlib::for_each` is a `constexpr` function that takes two arguements `std::tuple` and a callable, for instance a lambda. `mlib::for_each`'s has the following outline:
```C++
template<typename T, typename... Ts>
constexpr auto for_each(std::tuple<T, Ts...>& tup, auto& callable)
{
  // delegate to for_each_impl
}
```
An example use case is passing a lambda expression that outputs the elements in the `std::tuple`:

```C++
std::tuple<int, char, bool, double> t{42, 'c', true, 3.142};
mlib::for_each(t, [&](auto& a){std::cout << t << ", ";})
```
And the output would be the following:
```
42, c, t, 1, 3.142,
```
------------------------------------------------------------------------------------------------------------------------------------------------------------
### `mlib::transform`
`mlib::transform` is a `constexpr` function takes a given tuple, `t` and a given function `f` that transforms one of the elements inside of the tuple. An example invocation of `mlib::transfrom` looks like this:
```C++
std::tuple<int, char, bool> t{42, 'c', true};
mlib::transform(t, [](auto& t){return decltype(t)(static_cast<int>(t));});
```
This invokation, has a tuple t: `std::tuple<int, char, bool>` and then transforms that tuple using the `[](auto& t){return decltype(t)(static_cast<int>(t));};`, and does so accordingly.

`mlib::transform`'s implementation looks like this:
```C++
template<typename... Ts, std::size_t... indexes>
constexpr auto transform_helper(std::tuple<Ts...>& t, auto& lambda, std::index_sequence<indexes...>& i_s)
{
    return std::make_tuple(f(std::get<indexes>(t))...);
}

template<typename T, typename... Ts>
constexpr auto transform(std::tuple<T, Ts...>& t, auto& lambda)
{
    return transform_helper(t, lambda, std::make_index_sequence<sizeof...(Ts) + 1>{});
}
```
It is a very simple implementation, and `mlib::transform` is a great tool.

----------------------------------------------------------------------------------------------------------------------------------------------------------
### `mlib::fixed_string`.
`mlib::transform` is a string that can be used at compile time, so the size needs to be known at compile time and needs to be passed as an [NTTP](https://stackoverflow.com/questions/70924025/c20-nttp-specialization) or it can be infered by the `constexpr` constructor. Here is how you would have a compile time string, using `fixed_string`:
```C++
fixed_string<6> f{"hello"}; // note that `fixed_string` has a `constexpr` constructor taking an array.
```
The only hardship is specifying the [NTTP](https://stackoverflow.com/questions/70924025/c20-nttp-specialization). An example implementation of `fixed_string` is like this:
```C++
template<auto I> // I is the size of the string
struct fixed_string
{
  // notice the constexpr constructor.
  constexpr fixed_string(char(&arr)[I])
  {
    // copies `arr` into `m_data`
  }
  
  char m_data[I] = {};
};
```
-----------------------------------------------------------------------------------------------
### `mlib::Print.hpp`
`mlib::Print` is a function that takes a variadic amount of arguements and prints them out to the console using `std::cout`. And example use case is as follows:
```C++
mlib::Print(42, std::string(" is a number, and "), 'c' std::string("is a character"));
```
It is very easy to use, an example implementation looks as follows:
```C++
auto print(auto... t)
{
  (std::cout << t, ...);
}
```
---------------------------------------------------------------------------------------------------
### `mlib::all_of`
`mlib::all_of` is a simple feature that checks if all of the booleans, `bools` passed in are all `true`. A simple example is as follows:
```C++
mlib::all_of(true, true, 6 == 6, true, 42 == 0, true); // false
```
Another example is as follows:
```C++
mlib::all_of(true, true, true, true); // true
```
So it is a very useful feature, and can be used in many different ways, and example implementation of `mlib::all_of` is as follows:
```C++
namespace mlib
{
	template<bool b, bool... bs>
	struct all_of
	{
		static constexpr auto value = b && all_of<bs...>::value;
	};

	template<bool b>
	struct all_of<b>
	{
		static constexpr auto value = b;
	};
} // namespace mlib
```
---------------------------------------------------------------------------------------------------------------------------------
### `mlib::amount.hpp`

`mlib::amount` allows you do do things like you would do in a run time loop but at compile time. You can specify the number of recursions in the `<>` template parameter part. It is a very easy think to use, and can happen at compile time, as long as the callable passed in can run at compile time. Here is an example usage:
```C++
  amount<10>.times([](){std::cout << "hello" << "\n";} // note that this doesn't happen at compile time
  amount<10>.times([](){0 + 257;}                      // happens at compile time, but the result isn't really observable.
```
So, as shown it is a very useful feature. An example implementation is as follows:
```C++
    template<auto T>
    struct amount
    {
        constexpr auto times(auto&& lambda) const;
    };

    template<auto T>
    static constexpr auto amount_t = amount<T>{};

    template<auto T>
    constexpr auto amount<T>::times(auto&& lambda) const
    {
        lambda();
        if constexpr (T - 1 != 0)
        {
            amount_t<T - 1>.times(lambda);
        }
        return true;
    }
```
-----------------------------------------------------------------------------------------------------------------------------------------------
