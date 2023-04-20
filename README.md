# mlib

mlib is a fast, simple c++ meta-programming library that uses c++20. That also has a tiny bit of reflection!

### Motivating Example

```C++
#include<tuple>    // std::tuple
#include<iostream> // std::cout
#include<utility>  // std::make_index_sequence

#include "for_each.hpp"        // mlib::for_each
#include "tuple.hpp"           // mlib::tuple
#include "transform.hpp"       // mlib::transform
#include "select.hpp"          // mlib::select
#include "find.hpp"            // mlib::find
#include "tuple_reverse.hpp"   // mlib::tuple_reverse
#include "constexpr_for.hpp"   // mlib::constexpr_for
#include "constexpr_while.hpp" // mlib::constexpr_while
#include "refl_get.hpp"        // mlib::refl_get
#include "get_nth_element.hpp" // mlib::get_nth_element
#include "pack.hpp"            // mlib::value_pack
#include "constexpr_map.hpp"   // mlib::constexpr_map
#include "count_if.hpp"        // mlib::count_if
#include "pack_find.hpp"       // mlib::pack_find
#include "parse_rules.hpp"     // mlib::parse_rules
#include "constexpr_switch.hpp"// mlib::constexpr_switch
#include "constexpr_range.hpp" // mlib::constexpr_range

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

	// note need to add to less than:                 --\/, will print one hello.
	mlib::constexpr_while < 0, [](int t) {t++; return t < 3; }, [&]() {std::cout << "Hello\n"; }, [](int t) {return t + 1; } > ();

	// highest number of recursion.
	mlib::constexpr_while < 0, [](int t) {t++; return t < 501; }, [&]() {std::cout << "."; }, [](int t) {return t + 1; } > ();

	struct foo { int a; double b; char c; };
	foo f{42, 3.14, 'c'};
	auto x = mlib::meta::refl_get<foo>(f);
	std::cout << std::get<0>(x);

	std::cout << mlib::get_nth_element<2>(42, 'c', 3.14, true) << "\n"; // returns 3.14

	mlib::value_pack<42, 'c', 3.142, true> v{};

	mlib::constexpr_map < mlib::member_map<42, 'c'>{}, mlib::member_map<true, 3.142>{} > map{};

	std::cout << map[mlib::constexpr_parameter<true>{}];

	constexpr auto z = map.lookup<42>();
	std::cout << z;

	std::tuple tuple_count{ 0, 31.4, 5, 7, 0 };
	std::cout << mlib::count_if([](auto t) {return t > 0; }, tuple_count);

	std::cout << mlib::pack_find<42, 'c', true, 3, 12, 'b', 42, false, 5, 'y'>();
	std::cout << mlib::pack_find<'n', 'c', true, 3, 12, 'b', 42, false, 5, 'y'>();

	constexpr auto fixed = mlib::fixed_string{ "hello this is me" };

	constexpr auto result_of_branches = 
    mlib::parse_rules<fixed>{}.if_has_character<'c'>([&](auto x) {return mlib::fixed_string{ "ey i don't want a aije" }; })
		                      .if_has_character<'a'>([&](auto x) {return mlib::fixed_string{ "I dont wnt n eiy" }; })
		                      .if_has_character<'t'>([&](auto x) {return mlib::fixed_string{ "I dont think that this will happen\n" }; })
		                      .if_has_character<' '>([&](auto x) {return mlib::fixed_string{ x.data }; });
	mlib::constexpr_switch <
		5, [](mlib::constexpr_parameter<0>) { std::cout << "it is 0\n"; },
		   [](mlib::constexpr_parameter<5>) { std::cout << "it is not 0\n"; },
		   [](auto) { std::cout << "I don't know what it is!\n"; } >
		value{};
	value();

	constexpr auto value_index = mlib::constexpr_range<1, 2, 3, 4, 5, 6>{}
		.add<5>()
		.pop_front()
		.map < [](auto x) {return x + 1; } > ()
		.map_with_location < [](auto x, auto idx) {return x + idx; } > ()
		.join_with<0, 1, 2, 3, 4>()
		.add(mlib::Size{})
		.remove<0>()
		.at<10>();
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
The benchmark for this is as [follows](https://godbolt.org/z/Wq49Yrjo1):
```
------------------------------------------------------
Benchmark            Time             CPU   Iterations
------------------------------------------------------
BM_for_each        144 ns         82.6 ns      8173558
```
------------------------------------------------------------------------------------------------------------------------------------------------------------
### `mlib::transform`
`mlib::transform` is a `constexpr` function takes a given tuple, `t` and a given function `f` that transforms one of the elements inside of the tuple. An example invocation of `mlib::transfrom` looks like this:
```C++
std::tuple t{1, 4, 7, 'c', true, false};
mlib::transform(t, [](auto& t){return decltype(t)(static_cast<int>(t));});
```
This invokation, has a tuple t: `std::tuple<int, char, bool>` and then transforms that tuple using the `[](auto t) { return (static_cast<int>(t)) + 1; };`, and does so accordingly.

`mlib::transform`'s implementation looks like this:
```C++
template <typename... Ts, std::size_t... indexes>
constexpr auto transform_helper(std::tuple<Ts...> t, auto lambda,
                                std::index_sequence<indexes...> i_s) {
    return std::make_tuple(lambda(std::get<indexes>(t))...);
}

template <typename T, typename... Ts>
constexpr auto transform(std::tuple<T, Ts...> t, auto lambda) {
    return transform_helper(t, lambda,
                            std::make_index_sequence<sizeof...(Ts)>{});
}
```
It is a very simple implementation, and `mlib::transform` is a great tool.

The benchmark is as [follows](https://godbolt.org/z/T73f7GhbP):
```
-------------------------------------------------------
Benchmark             Time             CPU   Iterations
-------------------------------------------------------
BM_Transform        307 ns          173 ns      3620400
```

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
### `mlib::amount`

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
### `mlib::one_of`

`mlib::one_of` is a compile time `or`. You pass in a bunch of bools, and if one of then is `true`, the value that the class `mlib::one_of` holds will be `true`. An example use of `mlib::one_of` is as follows:
```C++
bool b = mlib::one_of<false, false, false>::value; // b == false
bool c = mlib::one_of<false, false, true, false, false>::value; // c == true
```
So it is very easy to use. An example implementation of `mlib::one_of` is as follows:
```C++
namespace mlib
{
	template<bool b, bool... b>
	struct one_of
	{
		static constexpr bool value = (b || b...);
	};

	template<bool b>
	struct one_of
	{
		static constexpr bool value = b;
	};
} // namespace mlib
```
And thats it for its implementation, note that it's implementation is not recursive!

-----------------------------------------------------------------------------------------------------------------------------------------------
### `mlib::constexpr_map`

`mlib::constexpr_map` is a compile-time map that also allows compile time lookup using the `operator[]` which takes a `mlib::constexpr_parameter` as it's compile time arguement and a `constexpr` lookup function `lookup` which takes the value to be looked up as a non type template parameter. It has a very cool implementation here is a watered down version of what it looks like:
```C++
template<auto T> struct constexpr_parameter {using type = decltype(T);}

template<auto A, auto B> struct member_map {
   constexpr auto operator[](constexpr_parameter<A>)
   {
     return B;
   }
};

template<auto... members> struct constexpr_map : constexpr_parameter<members>::type...
{
  using decltype(members)::operator[]...;
  // note lookup is missed out here
};
```
But as you can see it is a very cool implementation. Now onto some examples using `mlib::constexpr_map`:
```C++
mlib::constexpr_map<mlib::member_map<'c', 4>{}, mlib::member_map<true, 42>{}> map{};
std::cout << map[mlib::c_p<'c'>];
```
Note that here we are using `mlib::c_p` which is just a `mlib::constexpr_parameter` it looks like this:
```C++
template<auto T>
constexpr auto c_p = constant_parameter<T>{};
```
So in conclusion, `mlib::constexpr_map` is a really cool feature, the only problem is that the map is `constexpr` so therefore cannot add values, change values, etc.

-----------------------------------------------------------------------------------------------------------------------------------------------
### `mlib::meta::refl_get`
`mlib::meta::relf_get` is a useful reflection, that gets all of the members out of a `struct` for example if you had a struct `a`:
```C++
struct a
{
  int a;
  char c;
  bool b;
};
```
and so if pass an instance of `a` like this: `a A{42, 'c', true};` to `refl_get` we will get a tuple with the contents of `std::tuple<int, char, bool>{42, 'c', true}`! It is as easy as that to reflect this!

It looks like this:
```C++
constexpr auto refl_get(auto& t)
{
  // implementation
}
```
-----------------------------------------------------------------------------------------------------------------------------------------------

### `mlib::string_parse`

`mlib::string_parse` is a `struct` taking an `mlib::fixed_string`, `str` as a NTTP. It then has member functions:
    - `mlib::string_parse::substr`
    - `mlib::string_parse::consume_until`
This, `mlib::string_parse` is a very basic example of compile-time string parsing. An example of how `mlib::string_parse` looks like is as follows:
```C++
template<mlib::fixed_string str>
struct string_parse
{
  template<auto Start, auto End>
  constexpr auto substr() -> mlib::fixed_string<End - Start>;
  
  template<char C>
  constexpr auto consume_until() -> mlib::fixed_string;
};
```
