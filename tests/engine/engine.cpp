// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"

#include <iostream>

void engine::update(const model_component &component) const
{
	std::cout << "Updating model component.\n";
}

void engine::update(const camera_component &component) const
{
	std::cout << "Updating camera component.\n";
}

void engine::update(const position_component &component) const
{
	std::cout << "Updating position component.\n";
}