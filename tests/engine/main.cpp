// Copyright (c) 2022 Dhiraj Wishal

#include "player.hpp"
#include "cat.hpp"

#include <iostream>

int main()
{
	engine gameEngine;

	[[maybe_unused]] auto& p1 = gameEngine.emplace_back<player>(gameEngine);
	[[maybe_unused]] auto& p2 = gameEngine.emplace_back<player>(gameEngine);
	[[maybe_unused]] auto& p3 = gameEngine.emplace_back<player>(gameEngine);
	[[maybe_unused]] auto& p4 = gameEngine.emplace_back<player>(gameEngine);

	[[maybe_unused]] auto& c1 = gameEngine.emplace_back<cat>(gameEngine);
	[[maybe_unused]] auto& c2 = gameEngine.emplace_back<cat>(gameEngine);
	[[maybe_unused]] auto& c3 = gameEngine.emplace_back<cat>(gameEngine);
	[[maybe_unused]] auto& c4 = gameEngine.emplace_back<cat>(gameEngine);

	for (int i = 0; i < 1000000; i++)
		gameEngine.apply();
}