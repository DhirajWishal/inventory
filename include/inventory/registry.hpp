#pragma once

#include "system.hpp"

namespace inventory
{
	/**
	 * @brief Registry class.
	 * This class contains the mechanism for storing entities and components together, and to be able to easily access them.
	 *
	 * @tparam EntityIndex The entity index type. Default is default_index_type.
	 * @tparam ComponentIndex The component index type. Default is default_index_type.
	 * @tparam Components The components to store in the registry.
	 */
	template <index_type EntityIndex = default_index_type, index_type ComponentIndex = default_index_type, class... Components>
	class registry final
	{
	public:
		using index_type = EntityIndex;
		using component_index_type = ComponentIndex;
		using entity_type = entity<ComponentIndex, Components...>;

		template <class Component>
		using system_type = system<Component, ComponentIndex>;

		/**
		 * @brief Get the system object from the registry.
		 *
		 * @tparam Component The component type.
		 * @return constexpr system_type<Component>& The system reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD system_type<Component> &get_system() { return std::get<system_type<Component>>(m_Systems); }

		/**
		 * @brief Get the system object from the registry.
		 *
		 * @tparam Component The component type.
		 * @return constexpr system_type<Component> const& The system reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD const system_type<Component> &get_system() const { return std::get<system_type<Component>>(m_Systems); }

		/**
		 * @brief Create a entity object.
		 *
		 * @return constexpr index_type The entity index.
		 */
		constexpr INV_NODISCARD index_type create_entity() { return m_Entities.emplace().first; }

		/**
		 * @brief Get the entity object from the store.
		 *
		 * @param index The index of the entity.
		 * @return constexpr entity_type& The entity reference.
		 */
		constexpr INV_NODISCARD entity_type &get_entity(const index_type index) { return m_Entities[index]; }

		/**
		 * @brief Get the entity object from the store.
		 *
		 * @param index The index of the entity.
		 * @return constexpr entity_type const& The entity reference.
		 */
		constexpr INV_NODISCARD const entity_type &get_entity(const index_type index) const { return m_Entities[index]; }

		/**
		 * @brief Register an entity to a system.
		 *
		 * @tparam Component The component to register to.
		 * @param index The entity index.
		 * @return constexpr Component& The created component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD Component &register_to_system(const index_type index) { return get_system<Component>().register_entity(get_entity(index)); }

		/**
		 * @brief Get a component from the system.
		 *
		 * @tparam Component The component type.
		 * @param index The entity index.
		 * @return constexpr Component& The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD Component &get_component(const index_type index) { return get_system<Component>().get(get_entity(index)); }

		/**
		 * @brief Get a component from the system.
		 *
		 * @tparam Component The component type.
		 * @param index The entity index.
		 * @return constexpr const Component& The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD const Component &get_component(const index_type index) const { return get_system<Component>().get(get_entity(index)); }

		/**
		 * @brief Get a component from the system.
		 *
		 * @tparam Component The component type.
		 * @param ent The entity.
		 * @return constexpr Component& The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD Component &get_component(const entity_type &ent) { return get_system<Component>().get(ent); }

		/**
		 * @brief Get a component from the system.
		 *
		 * @tparam Component The component type.
		 * @param ent The entity.
		 * @return constexpr const Component& The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD const Component &get_component(const entity_type &ent) const { return get_system<Component>().get(ent); }

	public:
		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() noexcept { return m_Entities.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() noexcept { return m_Entities.end(); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const noexcept { return m_Entities.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const noexcept { return m_Entities.end(); }

		/**
		 * @brief Get the cons begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cbegin() const noexcept { return m_Entities.cbegin(); }

		/**
		 * @brief Get the const end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cend() const noexcept { return m_Entities.cend(); }

	private:
		std::tuple<system_type<Components>...> m_Systems;
		sparse_array<entity_type, EntityIndex> m_Entities;
	};
} // namespace inventory
