#pragma once

#include "system.hpp"

namespace inventory
{
	template <class Indexes, class Iterator, class... Iterators>
	class system_view_iterator final
	{
	public:
	};

	template <class System, class... Systems>
	class system_storage : public system_storage<Systems...>
	{
		System &m_System;

	public:
		explicit system_storage(System &system, Systems &&...systems) : m_System, system_storage<Systems...>(std::forward<Systems>(systems)...) {}
		System &get_system_ref() { return m_System; }
	};

	template <class System>
	class system_storage<System>
	{
		System &m_System;

	public:
		explicit system_storage(System &system) : m_System {}
		System &get_system_ref() { return m_System; }
	};

	template <class Indexes, class System, class... Systems>
	class system_view final : public system_storage<Systems...>
	{
		System &m_System;

	public:
		explicit system_view(System &system, Systems &&...systems) : m_System(system), system_storage<System, Systems...>(std::forward<Systems>(systems)...) {}

		template <class ComponentSystem>
		constexpr ComponentSystem &get_system() { return this->get_system_ref(); }

		template <class ComponentSystem>
		constexpr ComponentSystem::iterator get_system_begin() { return get_system<ComponentSystem>().begin(); }

		template <class ComponentSystem>
		constexpr ComponentSystem::iterator get_system_end() { return get_system<ComponentSystem>().end(); }

		constexpr decltype(auto) begin() { return system_view_iterator<Indexes, System, Systems...>(m_System.begin(), get_system_begin<Systems>()...); }
	};
} // namespace inventory
