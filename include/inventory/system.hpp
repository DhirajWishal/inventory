// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "entity.hpp"
#include "sparse_array.hpp"

namespace inventory
{
	/**
	 * @brief Component storage structure.
	 * This structure contains the actual component and its owning entity.
	 *
	 * @tparam Component The component type.
	 * @tparam EntityIndex The entity index type.
	 */
	template <class Component, index_type EntityIndex>
	struct component_storage final
	{
		Component m_Component;
		const EntityIndex m_EntityIndex;

		/**
		 * @brief Create the component storage object.
		 *
		 * @param component The component.
		 * @param index The entity index.
		 */
		constexpr explicit component_storage(Component &&component, const EntityIndex index) : m_Component(std::move(component)), m_EntityIndex(index) {}

		/**
		 * @brief Get the component from the container.
		 *
		 * @return constexpr Component& The component reference.
		 */
		constexpr INV_NODISCARD Component &component() { return m_Component; }

		/**
		 * @brief Get the component from the container.
		 *
		 * @return constexpr Component& The component reference.
		 */
		constexpr INV_NODISCARD const Component &component() const { return m_Component; }

		/**
		 * @brief Explicit component reference operator.
		 *
		 * @return constexpr Component& The component reference.
		 */
		INV_NODISCARD operator Component &() { return m_Component; }

		/**
		 * @brief Explicit component reference operator.
		 *
		 * @return constexpr Component& The component reference.
		 */
		INV_NODISCARD operator const Component &() const { return m_Component; }

		/**
		 * @brief Get the component's entity.
		 *
		 * @return constexpr EntityIndex The entity index.
		 */
		constexpr EntityIndex entity() const { return m_EntityIndex; }
	};

	/**
	 * @brief System class.
	 * This class is used to store a single component type.
	 *
	 * @tparam Component The component type.
	 * @tparam ComponentIndex The component index type. Default is the default_index_type.
	 * @tparam EntityIndex The entity index type. Default is the default_index_type.
	 */
	template <class Component, index_type ComponentIndex = default_index_type, index_type EntityIndex = default_index_type>
	class system
	{
		using container = sparse_array<component_storage<Component, EntityIndex>, ComponentIndex>;
		container m_Container;

	public:
		using iterator = typename container::iterator;
		using const_iterator = typename container::const_iterator;

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
		 * @param index The entity index.
		 * @param arguments The component constructor arguments.
		 * @return constexpr Component& The component reference.
		 */
		template <class Entity, class... Types>
		constexpr INV_NODISCARD Component &register_entity(Entity &ent, const EntityIndex index, Types &&...arguments)
		{
			auto result = m_Container.emplace(component_storage(Component(std::forward<Types>(arguments)...), index));
			ent.template register_component<Component>(result.first);

			return result.second->component();
		}

		/**
		 * @brief Get a component from the container using the entity it is attached to.
		 *
		 * @tparam Entity The entity to get the component from.
		 * @param ent The entity to index.
		 * @return constexpr Component& The component reference.
		 */
		template <class Entity>
		constexpr INV_NODISCARD Component &get(const Entity &ent) { return m_Container.at(ent.template get_component_index<Component>()); }

		/**
		 * @brief Get a component from the container using the entity it is attached to.
		 *
		 * @tparam Entity The entity to get the component from.
		 * @param ent The entity to index.
		 * @return constexpr Component& The component reference.
		 */
		template <class Entity>
		constexpr INV_NODISCARD const Component &get(const Entity &ent) const { return m_Container.at(ent.template get_component_index<Component>()); }

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
