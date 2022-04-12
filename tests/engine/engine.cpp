// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

void engine::update()
{
	for (auto& models : m_ModelComponents)
	{
		update_component(models.component());
		if (models.entity().is_registered_to<camera_component>())
			update_component(m_CameraComponents.get(models.entity()));
	}

	for (auto& position : m_PositionComponents)
	{
		update_component(position.component());
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
