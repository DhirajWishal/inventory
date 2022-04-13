// Copyright (c) 2022 Dhiraj Wishal

#include "player.hpp"

namespace engine
{
	player::player(engine& engine) : game_object(engine)
	{
		[[maybe_unused]] auto& m = create_component<model_component>();
		[[maybe_unused]] auto& c = create_component<camera_component>();
	}

	void player::update()
	{
		[[maybe_unused]] auto& m = get_component<model_component>();
		[[maybe_unused]] auto& c = get_component<camera_component>();
	}
}