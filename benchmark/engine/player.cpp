// Copyright (c) 2022 Dhiraj Wishal

#include "player.hpp"

namespace engine
{
	void player::update()
	{
		[[maybe_unused]] auto& model = inventory::get_component<model_component>(this);
		[[maybe_unused]] auto& camera = inventory::get_component<camera_component>(this);
	}
}