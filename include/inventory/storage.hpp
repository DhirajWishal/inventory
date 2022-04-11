// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "binary_flat_map.hpp"
#include "entity.hpp"

namespace inventory
{
	template <class Index, class Type, class... Types>
	class storage : public storage<Types...>
	{
		using entity_type = entity<Index>;
	};
} // namespace inventory
