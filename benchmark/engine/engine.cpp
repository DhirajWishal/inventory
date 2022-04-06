// Copyright (c) 2022 Dhiraj Wishal

#include "engine.hpp"
#include "../constants.hpp"
#include "inventory/inventory.hpp"
#include "player.hpp"
#include "cat.hpp"

void engine::update(const model_component& component) const
{
	volatile int x = 0;
}

void engine::update(const camera_component& component) const
{
	volatile int x = 0;
}

void engine::update(const position_component& component) const
{
	volatile int x = 0;
}

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
			[[maybe_unused]] auto& p = registry.emplace_back<player>(gameEngine);
			[[maybe_unused]] auto& c = registry.emplace_back<cat>(gameEngine);
		}

		game_object_updater updater;
		for (auto _ : state)
			registry.apply(updater);
	}
}