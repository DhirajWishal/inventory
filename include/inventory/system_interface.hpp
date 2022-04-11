// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "defaults.hpp"
#include "binary_flat_map.hpp"

#include <typeindex>
#include <algorithm>

namespace inventory
{
	template <index_type Index>
	class system_interface;

	/**
	 * @brief System type concept.
	 * This concept will only accept types that are inherited by the system_interface class.
	 *
	 * @tparam Type The type to check.
	 */
	template <class Type, class Index>
	concept system_type = std::is_base_of_v<system_interface<Index>, Type>;

	/**
	 * @brief System interface class.
	 * This class is used for system abstraction.
	 */
	template <index_type Index>
	class system_interface
	{
		std::type_index m_ThisTypeIndex;
		binary_flat_map<std::type_index, system_interface *> m_Links;

	public:
		/**
		 * @brief Explicit constructor.
		 *
		 * @param index The type index of the derived class.
		 */
		constexpr explicit system_interface(std::type_index &&index) : m_ThisTypeIndex(std::move(index)) {}

		/**
		 * @brief Link another system to this system.
		 *
		 * @tparam System The other system type.
		 * @param system The system to link.
		 */
		template <system_type<Index> System>
		constexpr void link(System &system) { m_Links[std::type_index(typeid(System))] = &system; }

		/**
		 * @brief Check if the system has a link to another system.
		 *
		 * @tparam System The system to check the link with.
		 * @return true if the system has a link.
		 * @return false if the system does not have a link.
		 */
		template <system_type<Index> System>
		constexpr bool has_link() const { return m_Links.contains(typeid(System)); }
	};
} // namespace inventory
