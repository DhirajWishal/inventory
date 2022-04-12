// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "game_object.hpp"

class player final : public game_object
{
public:
	explicit player(engine& engine);

	void update() override;
};
