// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "entity.hpp"
#include "sparse_array.hpp"

namespace inventory
{
	/**
	 * @brief Entity factory class.
	 * This class is responsible for creating new unique entities and keeping track of them.
	 *
	 * @tparam Entity The entity type.
	 */
	template <class Entity>
	class entity_factory
	{
	public:
		/**
		 * @brief Create a new entity.
		 *
		 * @return constexpr Entity The created entity.
		 */
		constexpr INV_NODISCARD Entity create() const { return Entity(); }
	};
} // namespace inventory
