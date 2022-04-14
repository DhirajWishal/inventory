// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

namespace engine
{
	void engine::update()
	{
		for (auto& entity : m_Registry)
		{
			update_component(m_Registry.get_component<model_component>(entity));
			update_component(m_Registry.get_component<camera_component>(entity));

			if (entity.is_registered_to<position_component>())
				update_component(m_Registry.get_component<position_component>(entity));
		}
	}

	void engine::update_primitive()
	{
		for (auto& ent : m_Registry.query<model_component, camera_component>())
		{
			update_component(m_Registry.get_component<model_component>(ent));
			update_component(m_Registry.get_component<camera_component>(ent));
		}

		for (auto& component : m_Registry.query<position_component>())
		{
			update_component(component);
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
}