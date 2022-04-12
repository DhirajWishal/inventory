// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

namespace engine
{
	void engine::update()
	{
		for (auto &models : m_ModelComponents)
		{
			update_component(models.second);
		}

		for (auto &camera : m_CameraComponents)
		{
			update_component(camera.second);
		}

		for (auto &position : m_PositionComponents)
		{
			update_component(position.second);
		}
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