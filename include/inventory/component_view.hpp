// Copyright (c) 2022 Dhiraj Wishal

#pragma once

namespace inventory
{
	template <class Type, class... Types>
	class component_view : public component_view<Type>, public component_view<Types...>
	{
	}

	template<class
}
