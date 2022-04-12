// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "platform.hpp"
#include "defaults.hpp"
#include "component_index.hpp"

#include <array>
#include <cassert>

namespace inventory
{
	/**
	 * @brief Entity class.
	 * This class acts as a single entity and it contains information regarding all the systems it has been registered to.
	 *
	 * @tparam ComponentIndex The component index type. Default is default_index_type.
	 * @tparam Components The components that could be attached to this.
	 */
	template <index_type ComponentIndex = default_index_type, class... Components>
	class entity final
	{
		std::array<ComponentIndex, get_component_count<Components...>()> m_Components = {};
		std::array<bool, get_component_count<Components...>()> m_RegisteredMap = {};

	public:
		/**
		 * @brief Default constructor.
		 */
		constexpr entity() = default;

		/**
		 * @brief Register a component to this entity.
		 *
		 * @tparam Component The component type.
		 * @param index The component index.
		 */
		template <class Component>
		constexpr void register_component(ComponentIndex index)
		{
			m_Components[::inventory::get_component_index<Component, Components...>()] = index;
			m_RegisteredMap[::inventory::get_component_index<Component, Components...>()] = true;
		}

		/**
		 * @brief Register a component to this entity.
		 * Make sure that this entity is registered to the component system before calling this method.
		 *
		 * @tparam Component The component type.
		 * @param index The component index.
		 */
		template <class Component>
		constexpr INV_NODISCARD ComponentIndex get_component_index() const
		{
			assert((m_RegisteredMap[::inventory::get_component_index<Component, Components...>()] && "This entity is not registered to this component! Make sure that the entity is registered to the component system before calling this."));
			return m_Components[::inventory::get_component_index<Component, Components...>()];
		}

		/**
		 * @brief Check if the entity is registered to a system.
		 * This operation takes O(log n) on average.
		 *
		 * @tparam Component The component of the system.
		 * @return true if this entity is registered to the required system.
		 * @return false if this entity is not registered to the required system.
		 */
		template <class Component>
		constexpr INV_NODISCARD bool is_registered_to() const { return m_RegisteredMap[::inventory::get_component_index<Component, Components...>()]; }
	};
} // namespace inventory
