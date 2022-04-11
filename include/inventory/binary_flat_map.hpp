#pragma once

#include "platform.hpp"

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace inventory
{
	/**
	 * @brief Missing entry error.
	 * This error gets thrown if trying to access a key-value pair which was not inserted to the map prior to accessing.
	 */
	class missing_entry_error final : public std::runtime_error
	{
	public:
		/**
		 * @brief Construct a new missing entry error object.
		 *
		 * @param message The message to be thrown.
		 */
		explicit missing_entry_error(const std::string &message) : std::runtime_error(message.c_str()) {}

		/**
		 * @brief Construct a new missing entry error object.
		 *
		 * @param message The message to be thrown.
		 */
		explicit missing_entry_error(const char *message) : std::runtime_error(message) {}
	};

	/**
	 * @brief Binary flap map class.
	 * This is an associative container, which is quite different to other implementations.
	 * Usually, associative containers comes in the form of binary trees and hash maps. This container takes the
	 * binary tree approach but uses the data locality as a main advantage, by "flattening" out the binary tree
	 * to a vector. This makes indexing (lookup) and iterating extremely fast (thanks to data locality).
	 *
	 * Not that deletion is not it's strong point, as it takes a considerable amount of time to delete an item
	 * (same as in a vector, O(n)).
	 *
	 * @tparam _key The key type.
	 * @tparam _value The value type.
	 * @tparam _compare The comparison type. It is std::less<_key> by default.
	 */
	template <class _key, class _value, class _compare = std::less<_key>>
	class binary_flat_map : public _compare
	{
	public:
		using key_type = _key;
		using value_type = _value;
		using entry_type = std::pair<key_type, value_type>;
		using compare_type = _compare;
		using container_type = std::vector<entry_type>;

	private:
		/**
		 * @brief Compare function.
		 * This function is used to find the entry using the entry type in the container using binary search.
		 *
		 * @param lhs The left hand side argument.
		 * @param rhs The right hand side argument.
		 * @return true if the lhs value is less than the rhs value.
		 * @return false if the rhs value is less than the lhs value.
		 */
		static constexpr INV_NODISCARD bool compare_function(const entry_type &lhs, const key_type &rhs)
		{
			constexpr compare_type comparator;
			return comparator(lhs.first, rhs);
		}

	public:
		/**
		 * @brief Default constructor.
		 */
		constexpr binary_flat_map() = default;

		/**
		 * @brief Default destructor.
		 */
		constexpr ~binary_flat_map() = default;

	public:
		/**
		 * @brief Find an entry from the container.
		 *
		 * @param key The key to search for.
		 * @return constexpr decltype(auto) The iterator of the key.
		 */
		constexpr INV_NODISCARD decltype(auto) find(const key_type &key) { return std::lower_bound(m_Container.begin(), m_Container.end(), key, compare_function); }

		/**
		 * @brief Find an entry from the container.
		 *
		 * @param key The key to search for.
		 * @return constexpr decltype(auto) The iterator of the key.
		 */
		constexpr INV_NODISCARD decltype(auto) find(const key_type &key) const { return std::lower_bound(m_Container.begin(), m_Container.end(), key, compare_function); }

		/**
		 * @brief Get a component at a given key position.
		 * If a key-value pair was not found, it'll automatically create one.
		 *
		 * @param key The key to access.
		 * @return constexpr value_type& The value reference.
		 */
		constexpr INV_NODISCARD value_type &at(const key_type &key)
		{
			auto itr = find(key);
			if (itr == m_Container.end() || itr->first != key)
				itr = m_Container.insert(itr, std::make_pair(key, value_type()));

			return itr->second;
		}

		/**
		 * @brief Get a component at a given key position.
		 * If a key-value pair was not found, it'll throw an exception.
		 *
		 * @param key The key to access.
		 * @return constexpr const value_type& The value reference.
		 */
		constexpr INV_NODISCARD const value_type &at(const key_type &key) const
		{
			const auto itr = find(key);
			if (itr == m_Container.end() || itr->first != key)
				throw missing_entry_error("The required key-value pair was not found!");

			return itr->second;
		}

	public:
		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() noexcept { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() noexcept { return m_Container.end(); }

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const noexcept { return m_Container.begin(); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const noexcept { return m_Container.end(); }

		/**
		 * @brief Get the cons begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cbegin() const noexcept { return m_Container.cbegin(); }

		/**
		 * @brief Get the const end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) cend() const noexcept { return m_Container.cend(); }

	public:
		/**
		 * @brief Check if an item exists in the container.
		 *
		 * @param key The key to search for.
		 * @return true if the item exists.
		 * @return false if the item does not exists.
		 */
		constexpr INV_NODISCARD bool contains(const key_type &key) const
		{
			const auto itr = find(key);
			return itr == end() || itr->first == key;
		}

		/**
		 * @brief Check if the container is empty.
		 *
		 * @return constexpr decltype(auto) Boolean value stating if its empty or not.
		 */
		constexpr INV_NODISCARD decltype(auto) empty() const noexcept { return m_Container.empty(); }

		/**
		 * @brief Get the size of the container.
		 *
		 * @return constexpr decltype(auto) The size.
		 */
		constexpr INV_NODISCARD decltype(auto) size() const noexcept { return m_Container.size(); }

		/**
		 * @brief Get the capacity of the container.
		 *
		 * @return constexpr decltype(auto) The capacity.
		 */
		constexpr INV_NODISCARD decltype(auto) capacity() const noexcept { return m_Container.capacity(); }

		/**
		 * @brief Get the maximum size of the container.
		 *
		 * @return constexpr decltype(auto) The maximum size.
		 */
		constexpr INV_NODISCARD decltype(auto) max_size() const noexcept { return m_Container.max_size(); }

	public:
		/**
		 * @brief Clear the container.
		 */
		constexpr void clear() noexcept { m_Container.clear(); }

		/**
		 * @brief Insert a new entry to the container.
		 *
		 * @param entry The entry to be inserted.
		 * @return constexpr decltype(auto) The iterator to where it's found/ where it was emplaced and whether if it's inserted or not.
		 */
		constexpr decltype(auto) insert(const entry_type &entry)
		{
			const auto itr = find(entry.first);
			if (itr == m_Container.end() || itr->first != entry.first)
				return std::make_pair(m_Container.insert(itr, entry), true);

			return std::make_pair(itr, false);
		}

		/**
		 * @brief Insert a new entry to the container.
		 *
		 * @param entry The entry to be inserted.
		 * @return constexpr decltype(auto) The iterator to where it's found/ where it was emplaced and whether if it's inserted or not.
		 */
		constexpr decltype(auto) insert(entry_type &&entry)
		{
			auto itr = find(entry.first);
			if (itr == m_Container.end() || itr->first != entry.first)
				return std::make_pair(m_Container.insert(itr, std::move(entry)), true);

			return std::make_pair(itr, false);
		}

	public:
		/**
		 * @brief Subscript operator.
		 *
		 * @param key The key to index.
		 * @return constexpr value_type& The value reference.
		 */
		constexpr value_type &operator[](const key_type &key)
		{
			auto itr = find(key);
			if (itr == m_Container.end() || itr->first != key)
				itr = m_Container.insert(itr, std::make_pair(key, value_type()));

			return itr->second;
		}

	private:
		container_type m_Container = {};
	};
} // namespace inventory