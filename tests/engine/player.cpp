// Copyright (c) 2022 Dhiraj Wishal

#include "player.hpp"

#include <iostream>

void player::update()
{
	std::cout << "Updating Player...\n";
	auto &model = get_component<model_component>();
	auto &camera = get_component<camera_component>();
}