// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

namespace entity
{
	void engine::update()
	{
		int counter = 0;
		const auto modelCameraView = m_Registry.view<model_component, camera_component>();
		for (auto entity : modelCameraView)
		{
			update_component(modelCameraView.get<model_component>(entity));
			update_component(modelCameraView.get<camera_component>(entity));
			[[maybe_unused]] volatile int x = 0;
		}

		const auto position = m_Registry.view<position_component>();
		for (auto entity : position)
		{
			update_component(position.get<position_component>(entity));
			[[maybe_unused]] volatile int x = 0;
		}
	}

	void engine::update_component(const model_component& component) const
	{
	}

	void engine::update_component(const camera_component &component) const
	{
	}

	void engine::update_component(const position_component &component) const
	{
	}
}