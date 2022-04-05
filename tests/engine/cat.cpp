// Copyright (c) 2022 Dhiraj Wishal

#include "cat.hpp"

void cat::update()
{
	[[maybe_unused]] auto& model = get_component<model_component>();
	[[maybe_unused]] auto& camera = get_component<camera_component>();
	[[maybe_unused]] auto& pos = get_component<position_component>();
}