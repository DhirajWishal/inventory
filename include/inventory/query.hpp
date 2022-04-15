// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "query_iterator.hpp"

namespace inventory
{
	/**
	 * @brief Query object.
	 * This object is used to filter and select a few components from the whole list.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bitset type.
	 */
	template <class EntityIterator, class BitSet>
	class query final
	{
		EntityIterator m_Begin;
		EntityIterator m_End;
		const BitSet m_BitSet;

	public:
		/**
		 * @brief Construct a new query object.
		 *
		 * @param first The first iterator.
		 * @param last The last iterator.
		 * @param bitset The bitset to check.
		 */
		explicit query(EntityIterator &&first, EntityIterator &&last, const BitSet bitset) : m_Begin(std::move(first)), m_End(std::move(last)), m_BitSet(bitset) {}

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() { return query_iterator<EntityIterator, BitSet>(m_Begin, m_End, m_BitSet); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() { return query_iterator<EntityIterator, BitSet>(m_End, m_End, m_BitSet); }
	};

	/**
	 * @brief Const query object.
	 * This object is used to filter and select a few components from the whole list.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam BitSet The bitset type.
	 */
	template <class EntityIterator, class BitSet>
	class const_query final
	{
		EntityIterator m_Begin;
		EntityIterator m_End;
		const BitSet m_BitSet;

	public:
		/**
		 * @brief Construct a new const query object.
		 *
		 * @param first The first iterator.
		 * @param last The last iterator.
		 * @param bitset The bitset to check.
		 */
		explicit const_query(EntityIterator &&first, EntityIterator &&last, const BitSet bitset) : m_Begin(std::move(first)), m_End(std::move(last)), m_BitSet(bitset) {}

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const { return const_query_iterator<EntityIterator, BitSet>(m_Begin, m_End, m_BitSet); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const { return const_query_iterator<EntityIterator, BitSet>(m_End, m_End, m_BitSet); }
	};
} // namespace inventory