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
		Indexes m_Indexes;
		EntityIterator m_Current;
		const EntityIterator m_Last;

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
		 * @brief Pre increment operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD reference operator++()
		{
			do
			{
				++m_Current;
			} while (m_Current != m_Last && !unpack_check(m_Indexes));

			return *this;
		}

		/**
		 * @brief Post increment operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD query_iterator operator++(int)
		{
			auto thisCopy = *this;

			do
			{
				m_Current++;
			} while (m_Current != m_Last && !unpack_check(m_Indexes));

			return thisCopy;
		}

		/**
		 * @brief Pre decrement operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD reference operator--()
		{
			do
			{
				--m_Current;
			} while (m_Current != m_Last && !unpack_check(m_Indexes));

			return *this;
		}

		/**
		 * @brief Post decrement operator.
		 *
		 * @return reference The value reference.
		 */
		constexpr INV_NODISCARD query_iterator operator--(int)
		{
			auto thisCopy = *this;

			do
			{
				m_Current--;
			} while (m_Current != m_Last && !unpack_check(m_Indexes));

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
		 * @brief Unpack the integer sequence and check the components.
		 *
		 * @tparam ComponentIndex The component index type.
		 * @tparam Indexes The component indexes.
		 * @param indexes The indexes to access.
		 * @return constexpr true if the components are available in the current entity.
		 * @return constexpr false if the components are not available in the current entity.
		 */
		template <class ComponentIndex, ComponentIndex... Indexes>
		constexpr INV_NODISCARD bool unpack_check([[maybe_unused]] const std::integer_sequence<ComponentIndex, Indexes...> &indexes) const { return check<ComponentIndex, Indexes...>(); }

		/**
		 * @brief Check if the component index is active.
		 *
		 * @tparam Index The index to check.
		 * @tparam ComponentIndexes The rest of the indexes
		 * @return true if the current entity uses the component.
		 * @return false if the current entity does not use the component.
		 */
		template <index_type ComponentIndex, ComponentIndex Index, ComponentIndex... ComponentIndexes>
		constexpr INV_NODISCARD bool check() const
		{
			const bool result = m_Current->is_registered_to<Index>();

			if constexpr (sizeof...(ComponentIndexes))
				return result && check<ComponentIndex, ComponentIndexes...>();

			else
				return result;
		}
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
} // namespace inventory
