// Copyright (c) 2022 Dhiraj Wishal

#include "inventory/inventory.hpp"
#include "player.hpp"
#include "cat.hpp"

#include <iostream>

int main()
{
	engine gameEngine;

	auto registry = inventory::inventory<game_object_updater>();
	registry.emplace_back<player>(gameEngine);
	registry.emplace_back<player>(gameEngine);
	registry.emplace_back<player>(gameEngine);
	registry.emplace_back<player>(gameEngine);

	registry.emplace_back<cat>(gameEngine);
	registry.emplace_back<cat>(gameEngine);
	registry.emplace_back<cat>(gameEngine);
	registry.emplace_back<cat>(gameEngine);

	game_object_updater updater;
	registry.apply(updater);
}