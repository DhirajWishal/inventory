// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_traits.hpp"
#include "bit_set.hpp"

namespace inventory
{
	/**
	 * @brief Query iterator type.
	 * This type can be used to iterate over the required components.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 */
	template <class EntityIterator, class BitSet>
	class query_iterator final
	{
		EntityIterator m_Current;
		const EntityIterator m_Last;
		const BitSet m_BitSet;

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
		 * @param bitset The bitset to check.
		 */
		constexpr explicit query_iterator(EntityIterator &current, const EntityIterator &last, const BitSet bitset) : m_Current(current), m_Last(last), m_BitSet(bitset) {}

		/**
		 * @brief Dereference operator.
		 *
		 * @return value_type& The value reference.
		 */
		constexpr INV_NODISCARD value_type &operator*() { return *m_Current; }

		/**
		 * @brief Dereference operator.
		 *
		 * @return const value_type& The value reference.
		 */
		constexpr INV_NODISCARD const value_type &operator*() const { return *m_Current; }

		/**
		 * @brief Pre-increment operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD reference operator++()
		{
			while (++m_Current != m_Last && !check())
				;
			return *this;
		}

		/**
		 * @brief Post-increment operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD query_iterator operator++(int)
		{
			auto thisCopy = *this;

			while (++m_Current != m_Last && !check())
				;
			return thisCopy;
		}

		/**
		 * @brief Pre-decrement operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD reference operator--()
		{
			while (--m_Current != m_Last && !check())
				;
			return *this;
		}

		/**
		 * @brief Post-decrement operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD query_iterator operator--(int)
		{
			auto thisCopy = *this;

			while (--m_Current != m_Last && !check())
				;
			return thisCopy;
		}

		/**
		 * @brief Increment-Assign operator.
		 *
		 * @param number The number to add.
		 * @return constexpr reference The object reference.
		 */
		constexpr INV_NODISCARD reference operator+=(int64_t number)
		{
			m_Current += number;
			*this;
		}

		friend constexpr INV_NODISCARD query_iterator operator+(const query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD query_iterator operator+(int64_t number, const query_iterator &iterator);

		/**
		 * @brief Decrement-Assign operator.
		 *
		 * @param number The number to subtract.
		 * @return constexpr reference The object reference.
		 */
		constexpr INV_NODISCARD reference operator-=(int64_t number)
		{
			m_Current -= number;
			*this;
		}

		friend constexpr INV_NODISCARD query_iterator operator-(const query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD query_iterator operator-(int64_t number, const query_iterator &iterator);

		/**
		 * @brief Get the difference between this and another iterator.
		 *
		 * @param other The other iterator.
		 * @return constexpr difference_type The difference.
		 */
		constexpr INV_NODISCARD difference_type operator-(const query_iterator &other) const { return m_Current - other.m_Current; }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr value_type& The value reference.
		 */
		constexpr INV_NODISCARD value_type &operator[](const int64_t index) { return *(m_Current + index); }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr value_type& The value reference.
		 */
		constexpr INV_NODISCARD const value_type &operator[](const int64_t index) const { return *(m_Current + index); }

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

	private:
		/**
		 * @brief Check if the entity's bitset contains all the values we need.
		 *
		 * @return true if the current entity uses the components.
		 * @return false if the current entity does not use the components.
		 */
		constexpr INV_NODISCARD bool check() const { return m_Current->get_bits() && m_BitSet; }
	};

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param iterator The iterator.
	 * @param number The number to increment.
	 * @return constexpr query_iterator<EntityIterator, BitSet> The incremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD query_iterator<EntityIterator, BitSet> operator+(const query_iterator<EntityIterator, BitSet> &iterator, int64_t number)
	{
		return query_iterator<EntityIterator, BitSet>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param number The number to increment.
	 * @param iterator The iterator.
	 * @return constexpr query_iterator<EntityIterator, BitSet> The incremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD query_iterator<EntityIterator, BitSet> operator+(int64_t number, const query_iterator<EntityIterator, BitSet> &iterator)
	{
		return query_iterator<EntityIterator, BitSet>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param iterator The iterator.
	 * @param number The number to decrement.
	 * @return constexpr query_iterator<EntityIterator, BitSet> The decremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD query_iterator<EntityIterator, BitSet> operator-(const query_iterator<EntityIterator, BitSet> &iterator, int64_t number)
	{
		return query_iterator<EntityIterator, BitSet>(iterator.m_Current - number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param number The number to decrement.
	 * @param iterator The iterator.
	 * @return constexpr query_iterator<EntityIterator, BitSet> The decremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD query_iterator<EntityIterator, BitSet> operator-(int64_t number, const query_iterator<EntityIterator, BitSet> &iterator)
	{
		return query_iterator<EntityIterator, BitSet>(iterator.m_Current - number);
	}

	/**
	 * @brief Const query iterator type.
	 * This type can be used to iterate over the required components.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 */
	template <class EntityIterator, class BitSet>
	class const_query_iterator final
	{
		EntityIterator m_Current;
		const EntityIterator m_Last;
		const BitSet m_BitSet;

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
		 * @param bitset The bitset to check.
		 */
		constexpr explicit const_query_iterator(const EntityIterator &current, const EntityIterator &last, const BitSet bitset) : m_Current(current), m_Last(last), m_BitSet(bitset) {}

		/**
		 * @brief Dereference operator.
		 *
		 * @return const value_type& The value reference.
		 */
		constexpr INV_NODISCARD const value_type &operator*() const { return *m_Current; }

		/**
		 * @brief Pre-increment operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD reference operator++()
		{
			while (++m_Current != m_Last && !check())
				;
			return *this;
		}

		/**
		 * @brief Post-increment operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD const_query_iterator operator++(int)
		{
			auto thisCopy = *this;

			while (++m_Current != m_Last && !check())
				;
			return thisCopy;
		}

		/**
		 * @brief Pre-decrement operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD reference operator--()
		{
			while (--m_Current != m_Last && !check())
				;
			return *this;
		}

		/**
		 * @brief Post-decrement operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD const_query_iterator operator--(int)
		{
			auto thisCopy = *this;

			while (--m_Current != m_Last && !check())
				;
			return thisCopy;
		}

		/**
		 * @brief Increment-Assign operator.
		 *
		 * @param number The number to add.
		 * @return constexpr reference The object reference.
		 */
		constexpr INV_NODISCARD reference operator+=(int64_t number)
		{
			m_Current += number;
			*this;
		}

		friend constexpr INV_NODISCARD const_query_iterator operator+(const const_query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD const_query_iterator operator+(int64_t number, const const_query_iterator &iterator);

		/**
		 * @brief Decrement-Assign operator.
		 *
		 * @param number The number to subtract.
		 * @return constexpr reference The object reference.
		 */
		constexpr INV_NODISCARD reference operator-=(int64_t number)
		{
			m_Current -= number;
			*this;
		}

		friend constexpr INV_NODISCARD const_query_iterator operator-(const const_query_iterator &iterator, int64_t number);
		friend constexpr INV_NODISCARD const_query_iterator operator-(int64_t number, const const_query_iterator &iterator);

		/**
		 * @brief Get the difference between this and another iterator.
		 *
		 * @param other The other iterator.
		 * @return constexpr difference_type The difference.
		 */
		constexpr INV_NODISCARD difference_type operator-(const const_query_iterator &other) const { return m_Current - other.m_Current; }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr value_type& The value reference.
		 */
		constexpr INV_NODISCARD value_type &operator[](const int64_t index) { return *(m_Current + index); }

		/**
		 * @brief Subscript operator.
		 *
		 * @param index The index to access.
		 * @return constexpr value_type& The value reference.
		 */
		constexpr INV_NODISCARD const value_type &operator[](const int64_t index) const { return *(m_Current + index); }

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

	private:
		/**
		 * @brief Check if the entity uses the required components.
		 *
		 * @return true if the current entity uses the components.
		 * @return false if the current entity does not use the components.
		 */
		constexpr INV_NODISCARD bool check() const { return m_Current->get_bits() && m_BitSet; }
	};

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param iterator The iterator.
	 * @param number The number to increment.
	 * @return constexpr const_query_iterator<EntityIterator, BitSet> The incremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, BitSet> operator+(const const_query_iterator<EntityIterator, BitSet> &iterator, int64_t number)
	{
		return const_query_iterator<EntityIterator, BitSet>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend increment operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param number The number to increment.
	 * @param iterator The iterator.
	 * @return constexpr const_query_iterator<EntityIterator, BitSet> The incremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, BitSet> operator+(int64_t number, const const_query_iterator<EntityIterator, BitSet> &iterator)
	{
		return const_query_iterator<EntityIterator, BitSet>(iterator.m_Current + number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param iterator The iterator.
	 * @param number The number to decrement.
	 * @return constexpr const_query_iterator<EntityIterator, BitSet> The decremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, BitSet> operator-(const const_query_iterator<EntityIterator, BitSet> &iterator, int64_t number)
	{
		return const_query_iterator<EntityIterator, BitSet>(iterator.m_Current - number);
	}

	/**
	 * @brief Friend decrement operator.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bit set type.
	 * @param number The number to decrement.
	 * @param iterator The iterator.
	 * @return constexpr const_query_iterator<EntityIterator, BitSet> The decremented iterator.
	 */
	template <class EntityIterator, class BitSet>
	constexpr INV_NODISCARD const_query_iterator<EntityIterator, BitSet> operator-(int64_t number, const const_query_iterator<EntityIterator, BitSet> &iterator)
	{
		return const_query_iterator<EntityIterator, BitSet>(iterator.m_Current - number);
	}
} // namespace inventory