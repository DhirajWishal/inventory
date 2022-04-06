// Copyright (c) 2022 Dhiraj Wishal

#include "cat.hpp"

void cat::update()
{
	[[maybe_unused]] auto& model = inventory::get_component<model_component>(this);
	[[maybe_unused]] auto& camera = inventory::get_component<camera_component>(this);
	[[maybe_unused]] auto& pos = inventory::get_component<position_component>(this);
}