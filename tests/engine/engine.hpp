// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "components.hpp"

#include <inventory/registry.hpp>

using registry = inventory::default_registry<model_component, camera_component, position_component>;
using entity = typename registry::entity_index_type;

class engine final
{
	registry m_Registry;

public:
	engine() = default;

	entity create_entity() { return m_Registry.create_entity(); }

	template <class Component>
	decltype(auto) register_to_system(entity& e)
	{
		if constexpr (std::is_same_v<Component, model_component>)
			return m_Registry.register_to_system<model_component>(e);

		else if constexpr (std::is_same_v<Component, camera_component>)
			return m_Registry.register_to_system<camera_component>(e);

		else if constexpr (std::is_same_v<Component, position_component>)
			return m_Registry.register_to_system<position_component>(e);
	}

	template <class Component>
	decltype(auto) get_component(const entity& e)
	{
		if constexpr (std::is_same_v<Component, model_component>)
			return m_Registry.get_component<model_component>(e);

		else if constexpr (std::is_same_v<Component, camera_component>)
			return m_Registry.get_component<camera_component>(e);

		else if constexpr (std::is_same_v<Component, position_component>)
			return m_Registry.get_component<position_component>(e);
	}

	void update();

	void update_component([[maybe_unused]] const model_component& component) const;
	void update_component([[maybe_unused]] const camera_component& component) const;
	void update_component([[maybe_unused]] const position_component& component) const;
};