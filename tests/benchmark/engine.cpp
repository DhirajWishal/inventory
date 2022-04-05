// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"
#include "constants.hpp"
#include "inventory/inventory.hpp"
#include "engine/player.hpp"
#include "engine/cat.hpp"

namespace engine_test
{
	void test(benchmark::State &state)
	{
		engine gameEngine;

		auto registry = inventory::inventory<game_object_updater>();

		registry.reserve<player>(ObjectCount);
		registry.reserve<cat>(ObjectCount);

		for (int i = 0; i < ObjectCount; i++)
		{
			registry.emplace_back<player>(gameEngine);
			registry.emplace_back<cat>(gameEngine);
		}

		game_object_updater updater;
		for (auto _ : state)
			registry.apply(updater);
	}
}