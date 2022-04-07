// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "game_object.hpp"

namespace engine
{
	class cat final : public game_object<model_component, camera_component, position_component>
	{
	public:
		explicit cat(engine& engine) : game_object(engine) {}
		void update() override;
	};
}