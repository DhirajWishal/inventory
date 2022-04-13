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
} // namespace inventory
