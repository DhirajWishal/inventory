#pragma once

#include "defaults.hpp"
#include "platform.hpp"

#include <array>

namespace inventory
{
	/**
	 * @brief Component index traits struct.
	 * The user must define this struct, with the appropriate components to index.
	 *
	 * For example:
	 * @code{cpp}
	 * using traits = inventory::component_index_traits<transform_component, rotation_component, camera_component>;
	 * @endcode
	 *
	 * @tparam Components The components.
	 */
	template <class... Components>
	struct component_index_traits final
	{
		static constexpr uint64_t count = sizeof...(Components);
	};

	/**
	 * @brief Component index generalized type.
	 *
	 * @tparam Component The first component.
	 * @tparam ComponentIndexTraits The component_index_traits object.
	 */
	template <class Component, class ComponentIndexTraits>
	struct component_index;

	/**
	 * @brief Component index specialized type.
	 *
	 * @tparam Component The first component.
	 * @tparam Components The rest of the components.
	 */
	template <class Component, class... Components>
	struct component_index<Component, component_index_traits<Component, Components...>> final
	{
		static constexpr uint64_t value = 0;
	};

	/**
	 * @brief Component index specialized type.
	 *
	 * @tparam Component The first component.
	 * @tparam Component2 The second component.
	 * @tparam Components The rest of the components.
	 */
	template <class Component, class Component2, class... Components>
	struct component_index<Component, component_index_traits<Component2, Components...>> final
	{
		static constexpr uint64_t value = 1 + component_index<Component, component_index_traits<Components...>>::value;
	};

	/**
	 * @brief Get the index of a given component in a list of components.
	 *
	 * @tparam Component The component to get the index of.
	 * @tparam Components The components to index.
	 * @return constexpr uint64_t The component's index.
	 */
	template <class Component, class... Components>
	consteval INV_NODISCARD uint64_t get_component_index() { return component_index<Component, component_index_traits<Components...>>::value; }

	/**
	 * @brief Get the component count from a list of components.
	 *
	 * @tparam Components The components to count.
	 * @return constexpr uint64_t The component count.
	 */
	template <class... Components>
	consteval INV_NODISCARD uint64_t get_component_count() { return component_index_traits<Components...>::count; }

	/**
	 * @brief Invalid index variable.
	 * This constexpr variable contains the invalid index of a given component index type.
	 *
	 * @tparam ComponentIndex The component index type.
	 */
	template <index_type ComponentIndex>
	constexpr ComponentIndex invalid_index = -1;

	/**
	 * @brief Create a default component array object.
	 *
	 * @tparam ComponentIndex The component index type.
	 * @tparam Components The components.
	 * @return consteval std::array<ComponentIndex, sizeof...(Components)> The created array.
	 */
	template <index_type ComponentIndex, class... Components>
	consteval INV_NODISCARD std::array<ComponentIndex, sizeof...(Components)> create_default_component_array()
	{
		std::array<ComponentIndex, sizeof...(Components)> componentArray;
		componentArray.fill(invalid_index<ComponentIndex>);

		return componentArray;
	}
} // namespace inventory
