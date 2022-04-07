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
		storage_interface() = default;

		/**
		 * @brief Destroy the storage interface object.
		 */
		virtual ~storage_interface() = default;

		/**
		 * @brief Apply a callable function over the stored data.
		 *
		 * @param callable The callable which will be applied.
		 */
		virtual void apply(Callable &callable) = 0;

		/**
		 * @brief Apply a callable function over the stored data.
		 *
		 * @param callable The callable which will be applied.
		 */
		virtual void apply(const Callable &callable) const = 0;

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
		virtual const std::type_info &get_type_info() const = 0;
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
		 * @brief Construct a new storage interface object.
		 */
		constexpr storage() = default;

		/**
		 * @brief Destroy the storage interface object.
		 */
		~storage() override = default;

		/**
		 * @brief Apply a callable function over the stored data.
		 *
		 * @param callable The callable which will be applied.
		 */
		constexpr void apply(Callable &callable) override
		{
			for (auto &item : m_Container)
				callable(item);
		}

		/**
		 * @brief Apply a callable function over the stored data.
		 *
		 * @param callable The callable which will be applied.
		 */
		constexpr void apply(const Callable &callable) const override
		{
			for (auto &item : m_Container)
				callable(item);
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
		constexpr INV_NODISCARD std::vector<Type> &container() { return m_Container; }

		/**
		 * @brief Get the stored container.
		 *
		 * @return std::vector<Type> container.
		 */
		constexpr INV_NODISCARD std::vector<Type> container() const { return m_Container; }

		/**
		 * @brief Get the type info object.
		 *
		 * @return const std::type_info& The type info object.
		 */
		virtual const std::type_info &get_type_info() const { return typeid(Type); }

	private:
		std::vector<Type> m_Container = {};
	};
}