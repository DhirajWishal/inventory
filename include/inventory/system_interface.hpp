// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "defaults.hpp"

#include <typeindex>
#include <algorithm>

namespace inventory
{
	/**
	 * @brief System interface class.
	 * This class is used for system abstraction.
	 */
	 template<index_type Index>
	class system_interface
	{
		std::type_index m_ThisTypeIndex;

	public:
		/**
		 * @brief Explicit constructor.
		 *
		 * @param index The type index of the derived class.
		 */
		constexpr explicit system_interface(std::type_index &&index) : m_ThisTypeIndex(std::move(index)) {}
	};
} // namespace inventory
