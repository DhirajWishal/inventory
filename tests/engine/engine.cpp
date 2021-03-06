// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

void engine::update()
{
	for (auto& ent : m_Registry)
	{
		update_component(m_Registry.get_component<model_component>(ent));
		update_component(m_Registry.get_component<camera_component>(ent));
	}

	for (auto& ent : m_Registry)
	{
		if (ent.is_registered_to<position_component>())
			update_component(m_Registry.get_component<position_component>(ent));
	}
}

void engine::update_component(const model_component& component) const
{
	[[maybe_unused]] volatile int x = 0;
}

void engine::update_component(const camera_component& component) const
{
	[[maybe_unused]] volatile int x = 0;
}

void engine::update_component(const position_component& component) const
{
	[[maybe_unused]] volatile int x = 0;
}
