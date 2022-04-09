// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "platform.hpp"

#include <vector>
#include <typeinfo>

namespace inventory
{
	/**
	 * @brief Storage interface class.
	 * This class acts as the main anchor point of the main storage class.
	 *
	 * @tparam Callable The callable type.
	 */
	template <class Callable>
	class storage_interface
	{
	public:
		/**
		 * @brief Construct a new storage interface object.
		 */
		constexpr storage_interface() = default;

		/**
		 * @brief Destroy the storage interface object.
		 */
		virtual ~storage_interface() = default;

		/**
		 * @brief Apply a callable function over the stored data.
		 */
		virtual void apply() = 0;

		/**
		 * @brief Apply a callable function over the stored data.
		 */
		virtual void apply() const = 0;

		/**
		 * @brief Get the number of data stored.
		 *
		 * @return size_t Size.
		 */
		INV_NODISCARD virtual size_t size() const = 0;

		/**
		 * @brief Capacity of the current allocation.
		 *
		 * @return size_t The capacity.
		 */
		INV_NODISCARD virtual size_t capacity() const = 0;

		/**
		 * @brief Clear the stored data.
		 */
		virtual void clear() = 0;

		/**
		 * @brief Get the type info object.
		 *
		 * @return const std::type_info& The type info object.
		 */
		virtual INV_NODISCARD const std::type_info &get_type_info() const = 0;
	};

	/**
	 * @brief Storage class.
	 * This class stores the actual data in a vector.
	 *
	 * @tparam Type
	 * @tparam Callable
	 */
	template <class Type, class Callable>
	class storage final : public storage_interface<Callable>
	{
	public:
		/**
		 * @brief Construct a new storage object.
		 *
		 * @param callable The callable object to be called.
		 */
		constexpr explicit storage(Callable &callable) : m_Callable(callable), m_ConstCallable(callable) {}

		/**
		 * @brief Destroy the storage interface object.
		 */
		~storage() override = default;

		/**
		 * @brief Apply a callable function over the stored data.
		 */
		constexpr void apply() override
		{
			for (auto &item : m_Container)
				m_Callable(item);
		}

		/**
		 * @brief Apply a callable function over the stored data.
		 */
		constexpr void apply() const override
		{
			for (const auto &item : m_Container)
				m_ConstCallable(item);
		}

		/**
		 * @brief Get the number of data stored.
		 *
		 * @return size_t Size.
		 */
		constexpr INV_NODISCARD size_t size() const override { return m_Container.size(); }

		/**
		 * @brief Capacity of the current allocation.
		 *
		 * @return size_t The capacity.
		 */
		constexpr INV_NODISCARD size_t capacity() const override { return m_Container.capacity(); }

		/**
		 * @brief Clear the stored data.
		 */
		constexpr void clear() override { m_Container.clear(); }

		/**
		 * @brief Get the stored container.
		 *
		 * @return std::vector<Type>& container.
		 */
		constexpr INV_NODISCARD std::vector<Type> &get_container() { return m_Container; }

		/**
		 * @brief Get the stored container.
		 *
		 * @return std::vector<Type> container.
		 */
		constexpr INV_NODISCARD std::vector<Type> get_container() const { return m_Container; }

		/**
		 * @brief Get the type info object.
		 *
		 * @return const std::type_info& The type info object.
		 */
		constexpr INV_NODISCARD const std::type_info &get_type_info() const override { return typeid(Type); }

	private:
		std::vector<Type> m_Container = {};

		Callable &m_Callable;
		const Callable &m_ConstCallable;
	};
}