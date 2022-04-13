// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "system.hpp"
#include "query.hpp"
#include "flat_map.hpp"
#include "flat_set.hpp"

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
		using entity_index_type = EntityIndex;
		using component_index_type = ComponentIndex;
		using entity_type = entity<ComponentIndex, Components...>;

		template <class Component>
		using system_type = system<Component, ComponentIndex, EntityIndex>;

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
		 * @return constexpr entity_index_type The entity index.
		 */
		constexpr INV_NODISCARD entity_index_type create_entity() { return m_Entities.emplace().first; }

		/**
		 * @brief Destroy an entity from the registry.
		 * This will unregister the entity from all the systems it is attached to.
		 *
		 * @param index The entity index.
		 */
		constexpr void destroy_entity(const entity_index_type &index)
		{
			(unregister_from_system<Components>(get_entity(index)), ...);
			m_Entities.remove(index);
		}

		/**
		 * @brief Get the entity object from the store.
		 *
		 * @param index The index of the entity.
		 * @return constexpr entity_type& The entity reference.
		 */
		constexpr INV_NODISCARD entity_type &get_entity(const entity_index_type index) { return m_Entities[index]; }

		/**
		 * @brief Get the entity object from the store.
		 *
		 * @param index The index of the entity.
		 * @return constexpr entity_type const& The entity reference.
		 */
		constexpr INV_NODISCARD const entity_type &get_entity(const entity_index_type index) const { return m_Entities[index]; }

		/**
		 * @brief Register an entity to a system.
		 *
		 * @tparam Component The component to register to.
		 * @tparam Types The argument types.
		 * @param index The entity index.
		 * @param arguments The arguments to be forwarded to create the component.
		 * @return constexpr Component& The created component reference.
		 */
		template <class Component, class... Types>
		constexpr INV_NODISCARD Component &register_to_system(const entity_index_type index, Types &&...arguments)
		{
			auto &entity = get_entity(index);

			m_AdjacencyMap[entity.get_component_hash()].remove(index);
			auto &component = get_system<Component>().register_entity(entity, index, std::forward<Types>(arguments)...);
			m_AdjacencyMap[entity.get_component_hash()].insert(index);

			return component;
		}

		/**
		 * @brief Unregister an entity from a system.
		 *
		 * @tparam Component The component type.
		 * @param index The entity index.
		 */
		template <class Component>
		constexpr void unregister_from_system(const entity_index_type index)
		{
			auto &entity = get_entity(index);
			m_AdjacencyMap[entity.get_component_hash()].remove(index);

			if (entity.template is_registered_to<Component>())
				get_system<Component>().unregister_entity(entity);

			m_AdjacencyMap[entity.get_component_hash()].insert(index);
		}

		/**
		 * @brief Unregister an entity from a system.
		 *
		 * @tparam Component The component type.
		 * @param ent The entity reference.
		 */
		template <class Component>
		constexpr void unregister_from_system(entity_type &ent)
		{
			if (ent.template is_registered_to<Component>())
				get_system<Component>().unregister_entity(ent);
		}

		/**
		 * @brief Get a component from the system.
		 *
		 * @tparam Component The component type.
		 * @param index The entity index.
		 * @return constexpr Component& The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD Component &get_component(const entity_index_type index) { return get_system<Component>().get(get_entity(index)); }

		/**
		 * @brief Get a component from the system.
		 *
		 * @tparam Component The component type.
		 * @param index The entity index.
		 * @return constexpr const Component& The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD const Component &get_component(const entity_index_type index) const { return get_system<Component>().get(get_entity(index)); }

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
		/**
		 * @brief Get the component index from the given component list.
		 *
		 * @tparam Component The component to get the index of.
		 * @return consteval decltype(auto) The component index.
		 */
		template <class Component>
		static consteval INV_NODISCARD decltype(auto) component_index() { return get_component_index<Component, Components...>(); }

		/**
		 * @brief Get the component sum.
		 *
		 * @tparam Type The type of the indexes.
		 * @tparam Indexes The indexes.
		 * @param sequence The index sequence.
		 * @return constexpr std::size_t The hash value.
		 */
		template <class Type, Type... Indexes>
		static constexpr INV_NODISCARD std::size_t get_component_hash([[maybe_unused]] const std::integer_sequence<Type, Indexes...> &sequence)
		{
			std::size_t hashValue = 0;
			for (const auto i : std::array<uint64_t, sizeof...(Indexes)>{Indexes...})
				index_hash_combine(hashValue, i);

			return hashValue;
		}

	public:
		/**
		 * @brief Get the query for the required components.
		 *
		 * @tparam Selection The required components.1
		 * @return constexpr decltype(auto) The query.
		 */
		template <class... Selection>
		constexpr INV_NODISCARD decltype(auto) query_components()
		{
			if constexpr (sizeof...(Selection) == 1)
				return get_system<Selection...>();

			else
			{
				const auto sequence = std::integer_sequence<ComponentIndex, component_index<Selection>()...>();
				auto &entities = m_AdjacencyMap[get_component_hash(sequence)];
				return query(entities.begin(), entities.end(), std::move(sequence));
			}
		}

		/**
		 * @brief Get the query for the required components.
		 *
		 * @tparam Selection The required components.
		 * @return constexpr decltype(auto) The const query.
		 */
		template <class... Selection>
		constexpr INV_NODISCARD decltype(auto) query_components() const
		{
			if constexpr (sizeof...(Selection) == 1)
				return get_system<Selection...>();

			else
			{
				const auto sequence = std::integer_sequence<ComponentIndex, component_index<Selection>()...>();
				const auto &entities = m_AdjacencyMap[get_component_hash(sequence)];
				return const_query(entities.begin(), entities.end(), std::move(sequence));
			}
		}

	private:
		std::tuple<system_type<Components>...> m_Systems;
		sparse_array<entity_type, EntityIndex> m_Entities;
		flat_map<std::size_t, flat_set<entity_index_type>> m_AdjacencyMap;
	};

	/**
	 * @brief Default registry type.
	 * This type is just a registry with the entity and component index types begin the default index type.
	 *
	 * @tparam Components The components.
	 */
	template <class... Components>
	using default_registry = registry<default_index_type, default_index_type, Components...>;
} // namespace inventory
