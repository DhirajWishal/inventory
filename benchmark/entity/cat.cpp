// Copyright (c) 2022 Dhiraj Wishal

#include "cat.hpp"

namespace entity
{
	cat::cat(engine &engine) : game_object(engine)
	{
		[[maybe_unused]] auto &m = create_component<model_component>();
		[[maybe_unused]] auto &c = create_component<camera_component>();
		[[maybe_unused]] auto &p = create_component<position_component>();
	}

	void cat::update()
	{
		[[maybe_unused]] auto &m = get_component<model_component>();
		[[maybe_unused]] auto &c = get_component<camera_component>();
		[[maybe_unused]] auto &p = get_component<position_component>();
	}
} // namespace entity