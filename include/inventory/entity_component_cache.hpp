#pragma once

#include "defaults.hpp"
#include "bit_set.hpp"
#include "flat_set.hpp"
#include "flat_map.hpp"

#include <stdexcept>

#ifdef INV_USE_UNSEQ
#include <execution>

#endif

namespace inventory
{
	/**
	 * @brief Sequence not registered error.
	 * This error is thrown if the required sequence does not exist.
	 */
	class sequence_not_registered_error final : public std::runtime_error
	{
	public:
		/**
		 * @brief Construct a new sequence not registered error object
		 *
		 * @param message The message to be thrown.
		 */
		explicit sequence_not_registered_error(const char *message) : std::runtime_error(message) {}
	};

	/**
	 * @brief Entity component cache.
	 * This object allows us to easily index all the entities with the required components attached to it.
	 *
	 * @tparam EntityIndex
	 * @tparam ComponentCount
	 */
	template </*index_type*/ class EntityIndex, uint64_t ComponentCount>
	class entity_component_cache final
	{
		using bit_set_type = bit_set<ComponentCount>;
		flat_map<bit_set_type, flat_set<EntityIndex>> m_Cache;

	public:
		/**
		 * @brief Default constructor.
		 */
		constexpr entity_component_cache() = default;

		/**
		 * @brief Check if the sequence exists in the container.
		 *
		 * @tparam Type The type of the index.
		 * @tparam Indexes The indexes.
		 * @param sequence The sequence.
		 * @return true if the sequence exists.
		 * @return false if the sequence does not exist.
		 */
		template <class Type, Type... Indexes>
		constexpr decltype(auto) sequence_exists([[maybe_unused]] const std::integer_sequence<Type, Indexes...> &sequence) const
		{
			bit_set_type bitSet;
			(bitSet.toggle_true(Indexes), ...);

#ifdef INV_USE_UNSEQ
			return std::any_of(std::execution::unseq, m_Cache.begin(), m_Cache.end(), [bitSet](const auto &entry)
							   { return entry.first && bitSet; });

#else
			return std::any_of(m_Cache.begin(), m_Cache.end(), [bitSet](const auto &entry)
							   { return entry.first && bitSet; });

#endif
		}

		/**
		 * @brief Get all the entities containing the index sequence.
		 *
		 * @tparam Type The type of the index.
		 * @tparam Indexes The indexes.
		 * @param sequence The sequence.
		 * @return constexpr decltype(auto) The entities.
		 */
		template <class Type, Type... Indexes>
		constexpr decltype(auto) get_entities([[maybe_unused]] const std::integer_sequence<Type, Indexes...> &sequence) const
		{
			bit_set_type bitSet;
			(bitSet.toggle_true(Indexes), ...);

			for (const auto &[set, entities] : m_Cache)
			{
				// This container is what we want. So we can return the entities.
				if (set && bitSet)
					return entities;
			}

			throw sequence_not_registered_error("The required sequence is not there in the system. Make sure to call sequence_exists() before calling this method.");
		}

		/**
		 * @brief Get all the entities containing the index sequence.
		 *
		 * @tparam Type The type of the index.
		 * @tparam Indexes The indexes.
		 * @param sequence The sequence.
		 * @return constexpr decltype(auto) The entities.
		 */
		template <class Type, Type... Indexes>
		constexpr decltype(auto) get_entities([[maybe_unused]] const std::integer_sequence<Type, Indexes...> &sequence)
		{
			bit_set_type bitSet;
			(bitSet.toggle_true(Indexes), ...);

			for (auto &[set, entities] : m_Cache)
			{
				// This container is what we want. So we can return the entities.
				if (set && bitSet)
					return entities;
			}

			throw sequence_not_registered_error("The required sequence is not there in the system. Make sure to call sequence_exists() before calling this method.");
		}

		/**
		 * @brief Add a new entity to the cache.
		 *
		 * @param bits The bits of the entity.
		 * @param index The entity index.
		 */
		constexpr void add_entity(const bit_set_type bits, const EntityIndex index)
		{
#ifdef INV_USE_UNSEQ
			std::for_each(std::execution::unseq, m_Cache.begin(), m_Cache.end(), [bits, index](auto &entry)
						  { if (entry.first || bits) entry.second.insert(index); });

#else
			std::for_each(m_Cache.begin(), m_Cache.end(), [bits, index](auto &entry)
						  { if (entry.first || bits) entry.second.insert(index); });

#endif

			m_Cache[bits].insert(index);
		}

		/**
		 * @brief Remove an entity from the cache.
		 *
		 * @param bits The bits of the entity.
		 * @param index The entity index.
		 */
		constexpr void remove_entity(const bit_set_type bits, const EntityIndex index)
		{
#ifdef INV_USE_UNSEQ
			std::for_each(std::execution::unseq, m_Cache.begin(), m_Cache.end(), [bits, index](auto &entry)
						  { if (entry.first || bits) entry.second.remove(index); });

#else
			std::for_each(m_Cache.begin(), m_Cache.end(), [bits, index](auto &entry)
						  { if (entry.first || bits) entry.second.remove(index); });

#endif
		}
	};
} // namespace inventory
