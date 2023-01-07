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
    std::make_tuple(f(std::get<indexes>(t))...);
}

template<typename T, typename... Ts>
constexpr auto transform(std::tuple<T, Ts...>& t, auto& lambda)
{
    return transform_helper(t, lambda, std::make_index_sequence<sizeof...(Ts) + 1>{});
}
```
It is a very simple implementation, and `mlib::transform` is a great tool.

