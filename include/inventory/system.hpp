// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "binary_flat_map.hpp"
#include "system_interface.hpp"
#include "entity.hpp"

namespace inventory
{
	/**
	 * @brief Simple system class.
	 * This class is used to store a single component.
	 *
	 * @tparam Component The component type.
	 * @tparam Index The entity index type. Default is the default_index_type.
	 */
	template <class Component, index_type Index = default_index_type>
	class simple_system : public system_interface<index>
	{
		using entity_type = entity<Index>;
		binary_flat_map<entity_type, Component> m_Storage;

	public:
		/**
		 * @brief Default constructor.
		 */
		constexpr simple_system() : system_interface(std::type_index(typeid(simple_system<Index, Component>))) {}

		/**
		 * @brief Register a new entity to the system.
		 *
		 * @tparam Types The constructor argument types for the component.
		 * @param ent The entity.
		 * @param arguments The component constructor arguments.
		 */
		template <class... Types>
		constexpr void register_entity(const entity_type &ent, Types &&...arguments) { m_Storage[ent] = Component(std::forward<Types>(arguments)...); }

		/**
		 * @brief Check if a given entity is registered or not.
		 *
		 * @param ent The entity to check.
		 * @return true if the entity is registered.
		 * @return false if the entity is not registered.
		 */
		constexpr INV_NODISCARD bool is_registered(const entity_type &ent) const { return m_Storage.contains(ent); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() noexcept { return m_Storage.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() noexcept { return m_Storage.end(); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const noexcept { return m_Storage.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const noexcept { return m_Storage.end(); }

		/**
		 * @brief Get the cons begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cbegin() const noexcept { return m_Storage.cbegin(); }

		/**
		 * @brief Get the const end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cend() const noexcept { return m_Storage.cend(); }
	};
} // namespace inventory
