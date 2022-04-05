// Copyright (c) 2022 Dhiraj Wishal

#include "inventory/inventory.hpp"
#include "player.hpp"
#include "cat.hpp"

#include <iostream>

int main()
{
	engine gameEngine;

	auto registry = inventory::inventory<game_object_updater>();
	auto& p1 = registry.emplace_back<player>(gameEngine);
	auto& p2 = registry.emplace_back<player>(gameEngine);
	auto& p3 = registry.emplace_back<player>(gameEngine);
	auto& p4 = registry.emplace_back<player>(gameEngine);

	auto& c1 = registry.emplace_back<cat>(gameEngine);
	auto& c2 = registry.emplace_back<cat>(gameEngine);
	auto& c3 = registry.emplace_back<cat>(gameEngine);
	auto& c4 = registry.emplace_back<cat>(gameEngine);

	game_object_updater updater;
	registry.apply(updater);
}