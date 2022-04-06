// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

namespace entity
{
	void engine::update()
	{
		const auto modelCameraView = m_Registry.view<model_component, camera_component>();
		for (auto entity : modelCameraView)
		{
			update_component(modelCameraView.get<model_component>(entity));
			update_component(modelCameraView.get<camera_component>(entity));
		}

		const auto position = m_Registry.view<position_component>();
		for (auto entity : position)
		{
			update_component(position.get<position_component>(entity));
		}
	}

	void engine::update_component(model_component& component) const { volatile int x = 0; }
	void engine::update_component(camera_component& component) const { volatile int x = 0; }
	void engine::update_component(position_component& component) const { volatile int x = 0; }
}