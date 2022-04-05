// Copyright (c) 2022 Dhiraj Wishal

#include "cat.hpp"

#include <iostream>

void cat::update()
{
	std::cout << "Updating Cat...\n";
	auto &model = get_component<model_component>();
	auto &camera = get_component<camera_component>();
	auto &pos = get_component<position_component>();
}