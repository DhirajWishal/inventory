// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "inventory/inventory.hpp"
#include "player.hpp"
#include "cat.hpp"

namespace ivnt_test
{
	/**
	 * @brief Test function to test the engine.
	 *
	 * @param state The benchmark state.
	 */
	template <int ObjectCount>
	inline void test(benchmark::State &state)
	{
		auto registry = inventory::inventory<engine::engine>();
		auto &playerVector = registry.get_storage<engine::player>();
		auto &catVector = registry.get_storage<engine::cat>();

		engine::engine gameEngine;
		playerVector.resize(ObjectCount, engine::player(gameEngine));
		catVector.resize(ObjectCount, engine::cat(gameEngine));

		for (auto _ : state)
		{
			registry.apply_manual<engine::player>(gameEngine);
			registry.apply_manual<engine::cat>(gameEngine);
		}
	}
}