# mlib

mlib is a fast, simple c++ meta-programming library that uses c++20.

### Motivating Example

```C++
#include<tuple> // std::tuple
#include<iostream> // std::cout
#include<utility> // std::make_index_sequence

#include "for_each.hpp"  // mlib::for_each
#include "tuple.hpp"     // mlib::tuple
#include "transform.hpp" // mlib::transform
#include "select.hpp"    // mlib::select

int main()
{
	// mlib::for_each
	std::tuple<int, char, bool, double> t{42, 'c', true, 3.142};
	mlib::for_each(t, [](auto& t) { std::cout << "val: " << t << "\n"; });

	// mlib::transform
	std::tuple<int, char, double> t2{ 42, 'c', 3.142 };
	mlib::transform(t2, [](auto& t) {return static_cast<int>(t); });

	// mlib::select
	std::tuple<char, bool, double> t3{ 'c', true, 3.142 };
	auto tuple = mlib::select(t3, std::index_sequence<1, 2>{});
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

