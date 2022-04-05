// Copyright (c) 2022 Dhiraj Wishal

#include "inventory/inventory.hpp"
#include "player.hpp"
#include "cat.hpp"

#include <iostream>

int main()
{
	engine gameEngine;

	auto registry = inventory::inventory<game_object_updater>();
	[[maybe_unused]] auto& p1 = registry.emplace_back<player>(gameEngine);
	[[maybe_unused]] auto& p2 = registry.emplace_back<player>(gameEngine);
	[[maybe_unused]] auto& p3 = registry.emplace_back<player>(gameEngine);
	[[maybe_unused]] auto& p4 = registry.emplace_back<player>(gameEngine);

	[[maybe_unused]] auto& c1 = registry.emplace_back<cat>(gameEngine);
	[[maybe_unused]] auto& c2 = registry.emplace_back<cat>(gameEngine);
	[[maybe_unused]] auto& c3 = registry.emplace_back<cat>(gameEngine);
	[[maybe_unused]] auto& c4 = registry.emplace_back<cat>(gameEngine);

	game_object_updater updater;
	for (int i = 0; i < 1000000; i++)
		registry.apply(updater);
	updater;
}