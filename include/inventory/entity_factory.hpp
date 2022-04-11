#pragma once

#include "entity.hpp"

namespace inventory
{
	/**
	 * @brief Entity factory class.
	 * This class is responsible for creating new unique entities and keeping track of them.
	 *
	 * @tparam Index The entity index type. Default is default_index_type.
	 */
	template <class Index = default_index_type>
	class entity_factory
	{
		using entity_type = entity<Index>;

		Index m_Index = 0;
		std::vector<entity_type> m_ActiveEntities;

	public:
		/**
		 * @brief Create a new entity.
		 *
		 * @return constexpr decltype(auto) The created entity.
		 */
		constexpr INV_NODISCARD decltype(auto) create() { return m_ActiveEntities.emplace_back(m_Index++); }

		/**
		 * @brief Destroy a given entity.
		 *
		 * @param e The entity to destroy.
		 */
		constexpr void destroy(const entity_type &e)
		{
			const auto itr = std::lower_bound(m_ActiveEntities.begin(), m_ActiveEntities.end(), e);
			if (itr != m_ActiveEntities.end() && *itr == e)
				m_ActiveEntities.erase(itr);
		}

		/**
		 * @brief Check if an entity is active.
		 * Active entities are entities that are currently being used by a system.
		 *
		 * @param e The entity to check.
		 * @return true if the entity is active.
		 * @return false if the entity is not active.
		 */
		constexpr INV_NODISCARD bool is_entity_active(const entity_type &e) const
		{
			const auto itr = std::lower_bound(m_ActiveEntities.begin(), m_ActiveEntities.end(), e);
			if (itr != m_ActiveEntities.end() && *itr == e)
				return true;

			return false;
		}
	};
} // namespace inventory
