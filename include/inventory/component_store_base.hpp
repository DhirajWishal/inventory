// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "platform.hpp"

namespace inventory
{
	/**
	 * @brief Component store base class.
	 * This class is used to store multiple components. Make sure that each component template argument
	 * is unique.
	 *
	 * @tparam Type The type of the first component.
	 * @tparam Types The types of the rest.
	 */
	template <class Type, class... Types>
	class component_store_base : public component_store_base<Type>, public component_store_base<Types...>
	{
	};

	/**
	 * @brief Component store base class.
	 * This class is a specialization of the component_store_base class and will contain the actual component.
	 *
	 * @tparam Type The type of the component.
	 */
	template <class Type>
	class component_store_base<Type>
	{
		Type m_Component;

	public:
		/**
		 * @brief Get the component.
		 *
		 * @return constexpr Type& The component reference.
		 */
		constexpr INV_NODISCARD Type &get() { return m_Component; }

		/**
		 * @brief Get the component.
		 *
		 * @return constexpr const Type& The component reference.
		 */
		constexpr INV_NODISCARD const Type &get() const { return m_Component; }
	};
}