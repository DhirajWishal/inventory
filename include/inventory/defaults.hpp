// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include <cstdint>
#include <type_traits>

namespace inventory
{
	// Set the default index type.
	using default_index_type = uint32_t;

	/**
	 * @brief Integral type concept.
	 * This concept will only accept integral type.
	 *
	 * @tparam Type The type to be checked.
	 */
	template <class Type>
	concept index_type = std::is_integral_v<Type> && std::is_unsigned_v<Type>;

	/**
	 * @brief Combine multiple data types.
	 *
	 * @tparam First The first type.
	 * @tparam Rest The rest of the types.
	 * @param seed The initial seed value.
	 * @param v The second value.
	 * @param rest The rest of the values.
	 */
	template <class First, class... Rest>
	constexpr void index_hash_combine(std::size_t& seed, const First& v, Rest... rest)
	{
		seed ^= std::hash<First>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

		if constexpr (sizeof...(rest) > 0)
			index_hash_combine(seed, rest...);
	}
} // namespace inventory
