// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "storage.hpp"

#include <memory>
#include <typeindex>
#include <algorithm>

namespace inventory
{
	/**
	 * @brief Storage map class.
	 * This class is an associative container which stores all of its data in a vector.
	 * Key-value pairs are determined using a binary search, this makes is much more faster than the usual
	 * std::unordered_map<,>;
	 *
	 * @tparam Callable The callable type.
	 */
	template <class Callable>
	class storage_map final
	{
	public:
		using key_type = std::type_index;
		using storage_type = storage_interface<Callable>;
		using value_type = std::unique_ptr<storage_type>;
		using entry_type = std::pair<key_type, value_type>;
		using container_type = std::vector<entry_type>;
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;

		/**
		 * @brief Comparison function used to compare when finding where an item is located.
		 *
		 * @param entry The container entry.
		 * @param key The they value to check.
		 * @return true if the entry is less than the key.
		 * @return false if the entry is grater than the key.
		 */
		static bool comparison_function(const entry_type &entry, const key_type &key) { return entry.first < key; }

	public:
		/**
		 * @brief Construct a new storage map object.
		 */
		storage_map() = default;

		/**
		 * @brief Destroy the storage map object.
		 */
		~storage_map() = default;

		/**
		 * @brief Find an iterator to where a specific key is located.
		 *
		 * @param key The key to check.
		 * @return iterator The position of that key in the container.
		 */
		iterator find(const key_type &key) { return std::lower_bound(m_Container.begin(), m_Container.end(), key, comparison_function); }

		/**
		 * @brief Find an iterator to where a specific key is located.
		 *
		 * @param key The key to check.
		 * @return iterator The position of that key in the container.
		 */
		const_iterator find(const key_type &key) const { return std::lower_bound(m_Container.begin(), m_Container.end(), key, comparison_function); }

		/**
		 * @brief Check if a given key is present in the container.
		 *
		 * @param key The key to check.
		 * @return true If the key is present.
		 * @return false If the key is not present.
		 */
		bool contains(const key_type &key) const
		{
			const auto itr = find(key);
			return itr != m_Container.end() && itr->first == key;
		}

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return iterator Begin iterator.
		 */
		iterator begin() { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return iterator End iterator.
		 */
		iterator end() { return m_Container.end(); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return iterator Begin iterator.
		 */
		const_iterator begin() const { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return iterator End iterator.
		 */
		const_iterator end() const { return m_Container.end(); }

		/**
		 * @brief Subscript operator overload.
		 * This will allocate a new entry if the key does not exist within the container.
		 *
		 * @param key The key value to index.
		 * @return value_type& The value type reference.
		 */
		value_type &operator[](const key_type &key)
		{
			auto itr = find(key);

			// If the iterator points to the end or if the keys do not match, lets make a new entry.
			if (itr == m_Container.end() || itr->first != key)
				itr = m_Container.insert(itr, entry_type(key, value_type()));

			return itr->second;
		}

	private:
		container_type m_Container = {};
	};
}