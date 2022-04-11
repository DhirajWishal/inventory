#pragma once

#include "binary_map.hpp"
#include "entity.hpp"

namespace inventory
{
	template <class Index, class Type, class... Types>
	class storage : public storage<Types...>
	{
		using entity_type = entity<Index>;
		binary_map<entity_type, 
	};
} // namespace inventory
