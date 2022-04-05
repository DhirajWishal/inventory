// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "game_object.hpp"

class player final : public game_object<model_component, camera_component>
{
public:
	explicit player(engine &engine) : game_object(engine) {}
	void update() override;
};