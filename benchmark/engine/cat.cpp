// Copyright (c) 2022 Dhiraj Wishal

#include "cat.hpp"

void cat::update()
{
	[[maybe_unused]] auto [model, camera, pos] = inventory::get_components<model_component, camera_component, position_component>(this);
}