#pragma once

#include<cstddef> // std::size_t

namespace mlib
{
	// index sequence only
	template <std::size_t ...>
	struct index_sequence
	{
	};

	template <std::size_t N, std::size_t ... Next>
	struct index_sequence_helper : public index_sequence_helper<N - 1U, N - 1U, Next...>
	{
	};

	template <std::size_t ... Next>
	struct index_sequence_helper<0U, Next ... >
	{
		using type = index_sequence<Next ... >;
	};

	template <std::size_t N>
	using make_index_sequence = typename index_sequence_helper<N>::type;
} // namespace mlib