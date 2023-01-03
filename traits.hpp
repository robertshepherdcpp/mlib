#pragma once

namespace mlib
{
	namespace traits
	{
		// const
		template<typename T>
		struct add_const
		{
			using type = const T;
		};

		template<typename T>
		struct add_const<T const>
		{
			using type = T;
		};

		template<typename T>
		struct remove_const
		{
			using type = T;
		};

		template<typename T>
		struct remove_const<T const>
		{
			using type = T;
		};

		// ref
		template<typename T>
		struct add_ref
		{
			using type = T&;
		};

		template<typename T>
		struct add_ref<T&>
		{
			using type = T;
		};

		template<typename T>
		struct remove_ref
		{
			using type = T;
		};

		template<typename T>
		struct remove_ref<T&>
		{
			using type = T;
		};
	}
};