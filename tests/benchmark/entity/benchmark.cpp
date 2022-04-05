// Copyright (c) 2022 Dhiraj Wishal

#include "benchmark.hpp"
#include "../constants.hpp"
#include "player.hpp"
#include "cat.hpp"

namespace entity
{
	void test(benchmark::State &state)
	{
		engine gameEngine;

		for (int i = 0; i < ObjectCount; i++)
		{
			[[maybe_unused]] auto p = player(gameEngine);
			[[maybe_unused]] auto c = cat(gameEngine);
		}

		for (auto _ : state)
			gameEngine.update();
	}
}