// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "platform.hpp"

#include <memory>
#include <typeindex>
#include <algorithm>
#include <vector>

namespace inventory
{
	/**
	 * @brief Flat map class.
	 * This class is just a set, but using a vector compared to a binary tree using nodes.
	 *
	 * @tparam Type The value type.
	 */
	template <class Type>
	class flat_set final
	{
	public:
		using value_type = Type;
		using container_type = std::vector<value_type>;
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;

		/**
		 * @brief Comparison function used to compare when finding where an item is located.
		 *
		 * @param entry The container entry.
		 * @param value The they value to check.
		 * @return true if the entry is less than the value.
		 * @return false if the entry is grater than the value.
		 */
		static constexpr INV_NODISCARD bool comparison_function(const value_type &entry, const value_type &value) { return entry < value; }

	public:
		/**
		 * @brief Construct a new storage map object.
		 */
		constexpr flat_set() = default;

		/**
		 * @brief Destroy the storage map object.
		 */
		~flat_set() = default;

		/**
		 * @brief Insert a new value to the container.
		 *
		 * @param value The value to be inserted.
		 * @return constexpr decltype(auto) The resulting pair.
		 */
		constexpr INV_NODISCARD decltype(auto) insert(const value_type &value)
		{
			auto itr = find(value);
			if (itr != m_Container.end() && *itr == value)
				return std::make_pair(false, itr);

			itr = m_Container.emplace(itr, value);
			return std::make_pair(true, itr);
		}

		/**
		 * @brief Find an iterator to where a specific value is located.
		 *
		 * @param value The value to check.
		 * @return constexpr decltype(auto) The position of that value in the container.
		 */
		constexpr INV_NODISCARD decltype(auto) find(const value_type &value) { return std::lower_bound(m_Container.begin(), m_Container.end(), value, comparison_function); }

		/**
		 * @brief Find an iterator to where a specific value is located.
		 *
		 * @param value The value to check.
		 * @return constexpr decltype(auto) The position of that value in the container.
		 */
		constexpr INV_NODISCARD decltype(auto) find(const value_type &value) const { return std::lower_bound(m_Container.begin(), m_Container.end(), value, comparison_function); }

		/**
		 * @brief Check if a given value is present in the container.
		 *
		 * @param value The value to check.
		 * @return true If the value is present.
		 * @return false If the value is not present.
		 */
		constexpr INV_NODISCARD bool contains(const value_type &value) const
		{
			const auto itr = find(value);
			return itr != m_Container.end() && *itr == value;
		}

		/**
		 * @brief Remove a value from the container.
		 *
		 * @param value The value to remove.
		 */
		constexpr void remove(const value_type &value)
		{
			const auto itr = find(value);
			if (itr != m_Container.end() && *itr == value)
				m_Container.erase(itr);
		}

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) Begin iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) End iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() { return m_Container.end(); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) Begin iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) End iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const { return m_Container.end(); }

		/**
		 * @brief Get the number of types stored in the container.
		 *
		 * @return constexpr decltype(auto) The count.
		 */
		constexpr INV_NODISCARD decltype(auto) size() const { return m_Container.size(); }

	private:
		container_type m_Container = {};
	};
}