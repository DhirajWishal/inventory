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
	template <int ObjectCount>
	inline void test(benchmark::State &state)
	{
		auto registry = inventory::inventory<engine::game_object_updater>();

		registry.reserve<engine::player>(ObjectCount);
		registry.reserve<engine::cat>(ObjectCount);

		engine::engine gameEngine;
		for (int i = 0; i < ObjectCount; i++)
		{
			[[maybe_unused]] auto &p = registry.emplace_back<engine::player>(gameEngine);
			[[maybe_unused]] auto &c = registry.emplace_back<engine::cat>(gameEngine);
		}

		engine::game_object_updater updater;
		for (auto _ : state)
			registry.apply(updater);
	}
}