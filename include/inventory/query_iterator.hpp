// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_traits.hpp"

namespace inventory
{
	/**
	 * @brief Query iterator type.
	 * This type can be used to iterate over the required components.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The indexes of the components.
	 */
	template <class EntityIterator, class Indexes>
	class query_iterator final
	{
		EntityIterator m_Current;
		const EntityIterator m_Last;
		Indexes m_Indexes;

	public:
		using value_type = typename EntityIterator::value_type;
		using difference_type = typename EntityIterator::difference_type;
		using reference = query_iterator &;

		/**
		 * @brief Default constructor.
		 */
		constexpr query_iterator() = default;

		/**
		 * @brief Construct a new query iterator object.
		 *
		 * @param current The current iterator.
		 * @param indexes The indexes to check components.
		 */
		constexpr explicit query_iterator(EntityIterator &current, const EntityIterator &last, const Indexes &indexes) : m_Current(current), m_Last(last), m_Indexes(indexes) {}

		/**
		 * @brief Dereference operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator*() { return *m_Current; }

		/**
		 * @brief Dereference operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator*() const { return *m_Current; }

		/**
		 * @brief Pre-increment operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator++() { return ++m_Current; }

		/**
		 * @brief Post-increment operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator++(int) { return m_Current++; }

		/**
		 * @brief Pre-decrement operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator--() { return --m_Current; }

		/**
		 * @brief Post-decrement operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator--(int) { return m_Current--; }

		/**
		 * @brief Increment-Assign operator.
		 *
		 * @param number The number to add.
		 * @return constexpr decltype(auto) The object reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator+=(int64_t number) { return m_Current += number; }

		friend constexpr INV_NODISCARD query_iterator operator+(const query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD query_iterator operator+(int64_t number, const query_iterator &iterator);

		/**
		 * @brief Decrement-Assign operator.
		 *
		 * @param number The number to subtract.
		 * @return constexpr decltype(auto) The object reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator-=(int64_t number) { return m_Current -= number; }

		friend constexpr INV_NODISCARD query_iterator operator-(const query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD query_iterator operator-(int64_t number, const query_iterator &iterator);

		/**
		 * @brief Get the difference between this and another iterator.
		 *
		 * @param other The other iterator.
		 * @return constexpr decltype(auto) The difference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator-(const query_iterator &other) const { return m_Current - other.m_Current; }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator[](const int64_t index) { return *(m_Current + index); }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator[](const int64_t index) const { return *(m_Current + index); }

		/**
		 * @brief Less than operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is less than the other.
		 * @return false if this iterator is grater than or equal to the other iterator.
		 */
		constexpr INV_NODISCARD bool operator<(const query_iterator &iterator) const { return m_Current < iterator.m_Current; }

		/**
		 * @brief Less than or equal operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is less than or equal to the other.
		 * @return false if this iterator is grater than the other iterator.
		 */
		constexpr INV_NODISCARD bool operator<=(const query_iterator &iterator) const { return m_Current <= iterator.m_Current; }

		/**
		 * @brief Grater than operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is grater than the other.
		 * @return false if this iterator is less than or equal to the other iterator.
		 */
		constexpr INV_NODISCARD bool operator>(const query_iterator &iterator) const { return m_Current > iterator.m_Current; }

		/**
		 * @brief Grater than or equal operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is grater than or equal to the other.
		 * @return false if this iterator is less than the other iterator.
		 */
		constexpr INV_NODISCARD bool operator>=(const query_iterator &iterator) const { return m_Current >= iterator.m_Current; }

		/**
		 * @brief Not equal to operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is not equal to the other iterator.
		 * @return false if this iterator is equal to the other iterator.
		 */
		constexpr INV_NODISCARD bool operator!=(const query_iterator &iterator) const { return m_Current != iterator.m_Current; }
	};

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param iterator The iterator.
	 * @param number The number to increment.
	 * @return constexpr query_iterator<EntityIterator, Indexes> The incremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD query_iterator<EntityIterator, Indexes> operator+(const query_iterator<EntityIterator, Indexes> &iterator, int64_t number)
	{
		return query_iterator<EntityIterator, Indexes>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param number The number to increment.
	 * @param iterator The iterator.
	 * @return constexpr query_iterator<EntityIterator, Indexes> The incremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD query_iterator<EntityIterator, Indexes> operator+(int64_t number, const query_iterator<EntityIterator, Indexes> &iterator)
	{
		return query_iterator<EntityIterator, Indexes>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param iterator The iterator.
	 * @param number The number to decrement.
	 * @return constexpr query_iterator<EntityIterator, Indexes> The decremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD query_iterator<EntityIterator, Indexes> operator-(const query_iterator<EntityIterator, Indexes> &iterator, int64_t number)
	{
		return query_iterator<EntityIterator, Indexes>(iterator.m_Current - number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param number The number to decrement.
	 * @param iterator The iterator.
	 * @return constexpr query_iterator<EntityIterator, Indexes> The decremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD query_iterator<EntityIterator, Indexes> operator-(int64_t number, const query_iterator<EntityIterator, Indexes> &iterator)
	{
		return query_iterator<EntityIterator, Indexes>(iterator.m_Current - number);
	}

	/**
	 * @brief Const query iterator type.
	 * This type can be used to iterate over the required components.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The indexes of the components.
	 */
	template <class EntityIterator, class Indexes>
	class const_query_iterator final
	{
		EntityIterator m_Current;
		const EntityIterator m_Last;
		Indexes m_Indexes;

	public:
		using value_type = typename EntityIterator::value_type;
		using difference_type = typename EntityIterator::difference_type;
		using reference = const_query_iterator &;

		/**
		 * @brief Default constructor.
		 */
		constexpr const_query_iterator() = default;

		/**
		 * @brief Construct a new query iterator object.
		 *
		 * @param current The current iterator.
		 * @param indexes The indexes to check components.
		 */
		constexpr explicit const_query_iterator(const EntityIterator &current, const EntityIterator &last, const Indexes &indexes) : m_Current(current), m_Last(last), m_Indexes(indexes) {}

		/**
		 * @brief Dereference operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator*() const { return *m_Current; }

		/**
		 * @brief Pre-increment operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator++() { return ++m_Current; }

		/**
		 * @brief Post-increment operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator++(int) { return m_Current++; }

		/**
		 * @brief Pre-decrement operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator--() { return --m_Current; }

		/**
		 * @brief Post-decrement operator.
		 *
		 * @return decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator--(int) { return m_Current--; }

		/**
		 * @brief Increment-Assign operator.
		 *
		 * @param number The number to add.
		 * @return constexpr decltype(auto) The object reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator+=(int64_t number) { return m_Current += number; }

		friend constexpr INV_NODISCARD const_query_iterator operator+(const const_query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD const_query_iterator operator+(int64_t number, const const_query_iterator &iterator);

		/**
		 * @brief Decrement-Assign operator.
		 *
		 * @param number The number to subtract.
		 * @return constexpr decltype(auto) The object reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator-=(int64_t number) { return m_Current -= number; }

		friend constexpr INV_NODISCARD const_query_iterator operator-(const const_query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD const_query_iterator operator-(int64_t number, const const_query_iterator &iterator);

		/**
		 * @brief Get the difference between this and another iterator.
		 *
		 * @param other The other iterator.
		 * @return constexpr decltype(auto) The difference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator-(const const_query_iterator &other) const { return m_Current - other.m_Current; }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator[](const int64_t index) { return *(m_Current + index); }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr decltype(auto) The value reference.
		 */
		constexpr INV_NODISCARD decltype(auto) operator[](const int64_t index) const { return *(m_Current + index); }

		/**
		 * @brief Less than operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is less than the other.
		 * @return false if this iterator is grater than or equal to the other iterator.
		 */
		constexpr INV_NODISCARD bool operator<(const const_query_iterator &iterator) const { return m_Current < iterator.m_Current; }

		/**
		 * @brief Less than or equal operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is less than or equal to the other.
		 * @return false if this iterator is grater than the other iterator.
		 */
		constexpr INV_NODISCARD bool operator<=(const const_query_iterator &iterator) const { return m_Current <= iterator.m_Current; }

		/**
		 * @brief Grater than operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is grater than the other.
		 * @return false if this iterator is less than or equal to the other iterator.
		 */
		constexpr INV_NODISCARD bool operator>(const const_query_iterator &iterator) const { return m_Current > iterator.m_Current; }

		/**
		 * @brief Grater than or equal operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is grater than or equal to the other.
		 * @return false if this iterator is less than the other iterator.
		 */
		constexpr INV_NODISCARD bool operator>=(const const_query_iterator &iterator) const { return m_Current >= iterator.m_Current; }

		/**
		 * @brief Not equal to operator.
		 *
		 * @param iterator The other iterator.
		 * @return true if this iterator is not equal to the other iterator.
		 * @return false if this iterator is equal to the other iterator.
		 */
		constexpr INV_NODISCARD bool operator!=(const const_query_iterator &iterator) const { return m_Current != iterator.m_Current; }
	};

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param iterator The iterator.
	 * @param number The number to increment.
	 * @return constexpr const_query_iterator<EntityIterator, Indexes> The incremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, Indexes> operator+(const const_query_iterator<EntityIterator, Indexes> &iterator, int64_t number)
	{
		return const_query_iterator<EntityIterator, Indexes>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param number The number to increment.
	 * @param iterator The iterator.
	 * @return constexpr const_query_iterator<EntityIterator, Indexes> The incremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, Indexes> operator+(int64_t number, const const_query_iterator<EntityIterator, Indexes> &iterator)
	{
		return const_query_iterator<EntityIterator, Indexes>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param iterator The iterator.
	 * @param number The number to decrement.
	 * @return constexpr const_query_iterator<EntityIterator, Indexes> The decremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, Indexes> operator-(const const_query_iterator<EntityIterator, Indexes> &iterator, int64_t number)
	{
		return const_query_iterator<EntityIterator, Indexes>(iterator.m_Current - number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 * @param number The number to decrement.
	 * @param iterator The iterator.
	 * @return constexpr const_query_iterator<EntityIterator, Indexes> The decremented iterator.
	 */
	template <class EntityIterator, class Indexes>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, Indexes> operator-(int64_t number, const const_query_iterator<EntityIterator, Indexes> &iterator)
	{
		return const_query_iterator<EntityIterator, Indexes>(iterator.m_Current - number);
	}
} // namespace inventory
