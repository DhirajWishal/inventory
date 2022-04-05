// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "game_object.hpp"

class cat final : public game_object<model_component, camera_component, position_component>
{
public:
	cat(engine &engine) : game_object(engine) {}
	void update() override;
};