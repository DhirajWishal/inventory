#pragma once

#include "platform.hpp"
#include "system.hpp"

#include <vector>
#include <cstdint>
#include <typeindex>
#include <algorithm>

namespace inventory
{
	// Set the default index type.
	using default_index_type = uint32_t;

	/**
	 * @brief Entity class.
	 * This class acts as a single entity and it contains information regarding all the systems it has been registered to.
	 *
	 * @tparam Index The index type. Default is default_index_type.
	 */
	template <class Index = default_index_type>
	class entity final
	{
		std::vector<std::reference_wrapper<system_interface>> m_RegisteredSystems;
		Index m_EntityID = 0;

	public:
        /**
         * @brief Default constructor.
         */
        constexpr entity() = default;

		/**
		 * @brief Explicit constructor.
		 *
		 * @param ID The entity ID of the object.
		 */
		constexpr explicit entity(Index ID) : m_EntityID(ID) {}

		/**
		 * @brief Destructor.
		 */
		~entity()
		{
			for (auto &systems : m_RegisteredSystems)
			{
			}
		}

		/**
		 * @brief Check if the entity is registered to a system.
		 * This operation takes O(log n) on average.
		 *
		 * @tparam Components The components of the system.
		 * @return true if this entity is registered to the required system.
		 * @return false if this entity is not registered to the required system.
		 */
		template <class... Components>
		constexpr INV_NODISCARD bool is_registered_to() const
		{
			// const auto systemIndex = std::type_index(typeid(system<Components...>));
			// const auto itr = std::lower_bound(m_RegisteredSystems.begin(), m_RegisteredSystems.end(), systemIndex);
			//
			// if (itr != m_RegisteredSystems.end() && *itr == systemIndex)
			//	return true;

			return false;
		}

		/**
		 * @brief Less than operator.
		 * This operator is used to index the entity in a binary map, using std::less.
		 *
		 * @param other The other entity.
		 * @return true if the other entity is less than this.
		 * @return false if the other entity is grater than this.
		 */
		constexpr INV_NODISCARD bool operator<(const entity &other) const { return m_EntityID < other.m_EntityID; }

		/**
		 * @brief Is equal to operator.
		 *
		 * @param other The other entity.
		 * @return true if the two entities are equal.
		 * @return false if the two entities are not equal.
		 */
		constexpr INV_NODISCARD bool operator==(const entity &other) const { return m_EntityID == other.m_EntityID; }
	};
} // namespace inventory
