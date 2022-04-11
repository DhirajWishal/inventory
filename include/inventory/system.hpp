#pragma once

#include <typeindex>

namespace inventory
{
	class system_interface
	{
		std::type_index m_ThisTypeIndex;

	public:
		constexpr explicit system_interface(std::type_index &&index) : m_ThisTypeIndex(std::move(index)) {}
	};

	template <class... Components>
	class complex_system : public system_interface
	{
	public:
		constexpr complex_system() : system_interface(std::type_index(typeid(complex_system<Components...>))) {}
	};
} // namespace inventory
