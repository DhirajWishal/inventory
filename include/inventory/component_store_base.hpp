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
	public:
		/**
		 * @brief Construct a new component store base object.
		 */
		component_store_base() = default;

		/**
		 * @brief Construct a new component store base object.
		 *
		 * @param first The data to be passed for the first component.
		 */
		explicit component_store_base(const Type &first) : component_store_base<Type>(first) {}

		/**
		 * @brief Construct a new component store base object.
		 *
		 * @param first The data to be passed for the first component.
		 * @param rest the data to be passed for the rest of the components.
		 */
		explicit component_store_base(const Type &first, const Types &...rest) : component_store_base<Type>(first), component_store_base<Types...>(std::forward<Types>(rest)...) {}

		/**
		 * @brief Construct a new component store base object.
		 *
		 * @param first The data to be passed for the first component.
		 * @param rest the data to be passed for the rest of the components.
		 */
		explicit component_store_base(Type &&first, Types &&...rest) : component_store_base<Type>(std::forward<Type>(first)), component_store_base<Types...>(std::forward<Types>(rest)...) {}
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
	public:
		/**
		 * @brief Construct a new component store base object.
		 */
		component_store_base() = default;

		/**
		 * @brief Construct a new component store base object.
		 *
		 * @param first The data to be passed for the first component.
		 */
		explicit component_store_base(const Type &first) : m_Component(first) {}

		/**
		 * @brief Construct a new component store base object.
		 *
		 * @param first The data to be passed for the first component.
		 */
		explicit component_store_base(Type &&first) : m_Component(std::move(first)) {}

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

	private:
		Type m_Component;
	};
}