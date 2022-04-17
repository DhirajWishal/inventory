// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "system.hpp"
#include "query.hpp"

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
		using system_type = system<Component, ComponentIndex>;

		using system_container_type = std::tuple<system_type<Components>...>;
		using entity_container_type = sparse_array<entity_type, EntityIndex>;

		using callback_index = uint8_t;
		using callback_type = std::function<void(registry &, const entity_index_type index)>;
		using callback_container = std::array<sparse_array<callback_type, callback_index>, get_component_count<Components...>()>;

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
		constexpr void destroy_entity(const entity_index_type index)
		{
			(unregister_from_system<Components>(index), ...);
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
			auto &callbacks = m_RegisterCallbacks[get_component_index<Component, Components...>()];
			std::for_each(callbacks.begin(), callbacks.end(), [this, index](auto &callback)
						  { callback(*this, index); });

			return get_system<Component>().register_entity(get_entity(index), std::forward<Types>(arguments)...);
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
			auto &callbacks = m_UnregisterCallbacks[get_component_index<Component, Components...>()];
			std::for_each(callbacks.begin(), callbacks.end(), [this, index](auto &callback)
						  { callback(*this, index); });

			auto &entity = get_entity(index);
			if (entity.template is_registered_to<Component>())
				get_system<Component>().unregister_entity(entity);
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
		 * @brief Attach a callback which will be called upon registering to the component.
		 *
		 * @tparam Component The component type.
		 * @param callback The callback to attach.
		 * @return callback_index The callback index of the attached callback.
		 */
		template <class Component>
		constexpr INV_NODISCARD callback_index attach_on_register_callback(callback_type &&callback) { return m_RegisterCallbacks[get_component_index<Component, Components...>()].emplace(std::move(callback)).first; }

		/**
		 * @brief Attach a callback which will be called upon registering to the component.
		 *
		 * @tparam Component The component type.
		 * @param callback The callback to attach.
		 * @return callback_index The callback index of the attached callback.
		 */
		template <class Component>
		constexpr INV_NODISCARD callback_index attach_on_register_callback(const callback_type &callback) { return m_RegisterCallbacks[get_component_index<Component, Components...>()].emplace(callback).first; }

		/**
		 * @brief Detach a callback from the component.
		 *
		 * @tparam Component The component type.
		 * @param index The callback index to detach.
		 */
		template <class Component>
		constexpr void detach_on_register_callback(const callback_index index) { m_RegisterCallbacks[get_component_index<Component, Components...>()].remove(index); }

		/**
		 * @brief Attach a callback which will be called upon unregistering to the component.
		 *
		 * @tparam Component The component type.
		 * @param callback The callback to attach.
		 * @return callback_index The callback index of the attached callback.
		 */
		template <class Component>
		constexpr INV_NODISCARD callback_index attach_on_unregister_callback(callback_type &&callback) { return m_UnregisterCallbacks[get_component_index<Component, Components...>()].emplace(std::move(callback)).first; }

		/**
		 * @brief Attach a callback which will be called upon unregistering to the component.
		 *
		 * @tparam Component The component type.
		 * @param callback The callback to attach.
		 * @return callback_index The callback index of the attached callback.
		 */
		template <class Component>
		constexpr INV_NODISCARD callback_index attach_on_unregister_callback(const callback_type &callback) { return m_UnregisterCallbacks[get_component_index<Component, Components...>()].emplace(callback).first; }

		/**
		 * @brief Detach a callback from the component.
		 *
		 * @tparam Component The component type.
		 * @param index The callback index to detach.
		 */
		template <class Component>
		constexpr void detach_on_unregister_callback(const callback_index index) { m_UnregisterCallbacks[get_component_index<Component, Components...>()].remove(index); }

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

	public:
		/**
		 * @brief Get the query for the required components.
		 *
		 * @tparam Selection The required components.1
		 * @return constexpr decltype(auto) The query.
		 */
		template <class... Selection>
		constexpr INV_NODISCARD decltype(auto) query()
		{
			if constexpr (sizeof...(Selection) == 1)
				return get_system<Selection...>();

			else if constexpr (sizeof...(Selection) > 1)
			{
				bit_set<get_component_count<Components...>()> bitset;
				(bitset.toggle_true(component_index<Selection>()), ...);

				return ::inventory::query(begin(), end(), bitset);
			}

			else
				return *this;
		}

		/**
		 * @brief Get the query for the required components.
		 *
		 * @tparam Selection The required components.
		 * @return constexpr decltype(auto) The const query.
		 */
		template <class... Selection>
		constexpr INV_NODISCARD decltype(auto) query() const
		{
			if constexpr (sizeof...(Selection) == 1)
				return get_system<Selection...>();

			else if constexpr (sizeof...(Selection) > 1)
			{
				bit_set<get_component_count<Components...>()> bitset;
				(bitset.toggle_true(component_index<Selection>()), ...);

				return ::inventory::const_query(begin(), end(), bitset);
			}

			else
				return *this;
		}

	private:
		system_container_type m_Systems;
		entity_container_type m_Entities;
		callback_container m_RegisterCallbacks;
		callback_container m_UnregisterCallbacks;
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
