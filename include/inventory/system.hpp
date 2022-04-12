// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "entity.hpp"
#include "sparse_array.hpp"

namespace inventory
{
	/**
	 * @brief Component container struct.
	 * This structure is used to store a single component.
	 *
	 * @tparam Component The component type.
	 * @tparam Entity The entity type.
	 */
	template <class Component, class Entity>
	struct component_container final
	{
		/**
		 * @brief Construct a new component container object.
		 *
		 * @param component The component lvalue.
		 * @param index The entity index lvalue.
		 */
		explicit component_container(Component &&component, const Entity &ent) : m_Component(std::move(component)), m_Entity(ent) {}

		/**
		 * @brief Get the component.
		 *
		 * @return Component& The component reference.
		 */
		INV_NODISCARD Component &component() { return m_Component; }

		/**
		 * @brief Get the component.
		 *
		 * @return const Component& The component reference.
		 */
		INV_NODISCARD const Component &component() const { return m_Component; }

		/**
		 * @brief Get the entity.
		 *
		 * @return EntityIndex& The entity ID.
		 */
		INV_NODISCARD const Entity& entity() const { return m_Entity; }

		Component m_Component;
		const Entity& m_Entity;
	};

	/**
	 * @brief System class.
	 * This class is used to store a single component type.
	 *
	 * @tparam Entity The entity type.
	 * @tparam Component The component type.
	 * @tparam ComponentIndex The component index type. Default is the default_component_index_type.
	 */
	template <class Entity, class Component, index_type ComponentIndex = default_component_index_type>
	class system
	{
		sparse_array<component_container<Component, Entity>, ComponentIndex> m_Container;

	public:
		/**
		 * @brief Default constructor.
		 */
		constexpr system() = default;

		/**
		 * @brief Register a new entity to the system.
		 *
		 * @tparam Entity The entity type.
		 * @tparam Types The constructor argument types for the component.
		 * @param ent The entity.
		 * @param arguments The component constructor arguments.
		 */
		template <class... Types>
		constexpr INV_NODISCARD decltype(auto) register_entity(Entity &ent, Types &&...arguments)
		{
			auto result = m_Container.emplace(component_container(Component(std::forward<Types...>(arguments)...), ent));
			ent.template register_component<Component>(result.first);

			return result.second;
		}

		/**
		 * @brief Get a component from the container using the entity it is attached to.
		 * This operation takes O(1) in best case, and O(log n) in the worst case.
		 *
		 * @tparam Entity The entity to get the component from.
		 * @param ent The entity to index.
		 * @return constexpr Component& The component reference.
		 */
		constexpr INV_NODISCARD Component &get(const Entity &ent) { return m_Container.at(ent.template get_component_index<Component>()).component(); }

		/**
		 * @brief Get a component from the container using the entity it is attached to.
		 * This operation takes O(1) in best case, and O(log n) in the worst case.
		 *
		 * @tparam Entity The entity to get the component from.
		 * @param ent The entity to index.
		 * @return constexpr Component& The component reference.
		 */
		constexpr INV_NODISCARD const Component &get(const Entity &ent) const { return m_Container.at(ent.template get_component_index<Component>()).component(); }

	public:
		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() noexcept { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() noexcept { return m_Container.end(); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const noexcept { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const noexcept { return m_Container.end(); }

		/**
		 * @brief Get the cons begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cbegin() const noexcept { return m_Container.cbegin(); }

		/**
		 * @brief Get the const end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cend() const noexcept { return m_Container.cend(); }
	};
} // namespace inventory
