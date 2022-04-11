// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include <benchmark/benchmark.h>

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
		engine::engine gameEngine;
		auto &playerVector = gameEngine.get_storage<engine::player>();
		auto &catVector = gameEngine.get_storage<engine::cat>();

		playerVector.resize(ObjectCount, engine::player(gameEngine));
		catVector.resize(ObjectCount, engine::cat(gameEngine));

		for (auto _ : state)
			gameEngine.apply();
	}
}