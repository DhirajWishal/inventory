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
	 * @tparam Indexes The component indexes.
	 */
	template <class EntityIterator, class Indexes>
	class query final
	{
		EntityIterator m_Begin;
		EntityIterator m_End;
		Indexes m_Indexes;

	public:
		/**
		 * @brief Construct a new query object.
		 *
		 * @param first The first iterator.
		 * @param last The last iterator.
		 * @param indexes The indexes to access.
		 */
		explicit query(EntityIterator &&first, EntityIterator &&last, Indexes &&indexes) : m_Begin(std::move(first)), m_End(std::move(last)), m_Indexes(std::move(indexes)) {}

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() { return query_iterator<EntityIterator, Indexes>(m_Begin, m_End, m_Indexes); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() { return query_iterator<EntityIterator, Indexes>(m_End, m_End, m_Indexes); }
	};

	/**
	 * @brief Const query object.
	 * This object is used to filter and select a few components from the whole list.
	 *
	 * @tparam EntityIterator The entity iterator type.
	 * @tparam Indexes The component indexes.
	 */
	template <class EntityIterator, class Indexes>
	class const_query final
	{
		EntityIterator m_Begin;
		EntityIterator m_End;
		Indexes m_Indexes;

	public:
		/**
		 * @brief Construct a new const query object.
		 *
		 * @param first The first iterator.
		 * @param last The last iterator.
		 * @param indexes The indexes to access.
		 */
		explicit const_query(EntityIterator &&first, EntityIterator &&last, Indexes &&indexes) : m_Begin(std::move(first)), m_End(std::move(last)), m_Indexes(std::move(indexes)) {}

		/**
		 * @brief Get the begin iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) begin() const { return const_query_iterator<EntityIterator, Indexes>(m_Begin, m_End, m_Indexes); }

		/**
		 * @brief Get the end iterator.
		 *
		 * @return constexpr decltype(auto) The iterator.
		 */
		constexpr INV_NODISCARD decltype(auto) end() const { return const_query_iterator<EntityIterator, Indexes>(m_End, m_End, m_Indexes); }
	};
} // namespace inventory