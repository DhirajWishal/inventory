// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_store.hpp"

namespace inventory
{
	/**
	 * @brief Entity base class.
	 * This class is the base class of the entity object, and is intended to be used for abstraction.
	 */
	class entity_base
	{
	};

	/**
	 * @brief Entity class.
	 * This is an abstract entity class which can house any component and can be accessed easily using the given member functions.
	 *
	 * @note This class cannot be inherited and is intended to be used as a single entity in the system.
	 *
	 * @tparam Types The component types.
	 */
	template <class... Types>
	class entity final : public entity_base, public component_store<Types...>
	{
	public:
		/**
		 * @brief Get the component object.
		 *
		 * @tparam Type The component type.
		 * @return constexpr Type& The component reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD Type &get_component() { return get_component<Type>(this); }

		/**
		 * @brief Get the component object.
		 *
		 * @tparam Type The component type.
		 * @return constexpr Type& The component reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD const Type &get_component() const { return get_component<Type>(this); }
	};
}