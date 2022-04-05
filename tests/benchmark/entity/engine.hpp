// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "engine/components.hpp"

#include <entt/entt.hpp>

namespace entity
{
	class engine final
	{
		entt::registry m_Registry;

	public:
		engine() = default;

		entt::entity create_entity() { return m_Registry.create(); }
		entt::registry& get_registry() { return m_Registry; }

		void update();

		void update_component([[maybe_unused]] model_component& component) const;
		void update_component([[maybe_unused]] camera_component& component) const;
		void update_component([[maybe_unused]] position_component& component) const;
	};
}