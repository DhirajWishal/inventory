// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include <benchmark/benchmark.h>

#include "player.hpp"
#include "cat.hpp"

namespace entt_test
{
	/**
	 * @brief Test function to test the engine.
	 *
	 * @param state The benchmark state.
	 */
	template <int ObjectCount>
	inline void test(benchmark::State &state)
	{
		entity::engine gameEngine;
		for (int i = 0; i < ObjectCount; i++)
		{
			[[maybe_unused]] auto p = entity::player(gameEngine);
			[[maybe_unused]] auto c = entity::cat(gameEngine);
		}

		for (auto _ : state)
			gameEngine.update();
	}
}