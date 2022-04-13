// Copyright (c) 2022 Dhiraj Wishal

#include "player.hpp"
#include "cat.hpp"

int main()
{
	engine gameEngine;
	[[maybe_unused]] auto p = player(gameEngine);
	[[maybe_unused]] auto c = cat(gameEngine);

	gameEngine.update();
}