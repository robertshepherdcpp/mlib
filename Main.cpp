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
#include "refl_get.hpp"       // mlib::refl_get
#include "get_nth_element.hpp" // mlib::get_nth_element
#include "pack.hpp"            // mlib::value_pack
#include "constexpr_map.hpp"   // mlib::constexpr_map
#include "count_if.hpp"        // mlib::count_if
#include "pack_find.hpp"       // mlib::pack_find

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
	std::cout << v[mlib::index_pack<2>{}] << "\n";
	std::cout << v.begin() << "\n";

	mlib::constexpr_map < mlib::member_map<42, 'c'>{}, mlib::member_map<true, 3.142>{} > map{};

	std::cout << map[mlib::constexpr_parameter<true>{}];

	constexpr auto z = map.lookup<42>();
	std::cout << z;

	std::tuple tuple_count{ 0, 31.4, 5, 7, 0 };
	std::cout << mlib::count_if([](auto t) {return t > 0; }, tuple_count);

	std::cout << mlib::pack_find<42, 'c', true, 3, 12, 'b', 42, false, 5, 'y'>();
	std::cout << mlib::pack_find<'n', 'c', true, 3, 12, 'b', 42, false, 5, 'y'>();
}