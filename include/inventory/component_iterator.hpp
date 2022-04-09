// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_store.hpp"

namespace inventory
{
	template <class Entity, class... Types>
	class component_iterator
	{
		std::vector<Entity> &m_Container;
	};
}