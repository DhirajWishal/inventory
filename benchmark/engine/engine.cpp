// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

namespace engine
{
	void engine::update()
	{
		auto& entities = m_Registry.query<model_component, camera_component>();
		for (auto &ent : entities)
		{
			update_component(m_Registry.get_component<model_component>(ent));
			update_component(m_Registry.get_component<camera_component>(ent));
		}

		for (auto &component : m_Registry.query<position_component>())
		{
			update_component(component);
		}

		[[maybe_unused]] volatile int x = 0;
	}

	void engine::update_component(const model_component &component) const
	{
		[[maybe_unused]] volatile int x = 0;
	}

	void engine::update_component(const camera_component &component) const
	{
		[[maybe_unused]] volatile int x = 0;
	}

	void engine::update_component(const position_component &component) const
	{
		[[maybe_unused]] volatile int x = 0;
	}
}