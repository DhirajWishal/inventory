// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "inventory/inventory.hpp"
#include "player.hpp"
#include "cat.hpp"

namespace inventory_test
{
	/**
	 * @brief Test function to test the engine.
	 *
	 * @param state The benchmark state.
	 */
	template<int ObjectCount>
	inline void test(benchmark::State& state)
	{
		auto registry = inventory::inventory<game_object_updater>();

		registry.reserve<player>(ObjectCount);
		registry.reserve<cat>(ObjectCount);

		engine gameEngine;
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