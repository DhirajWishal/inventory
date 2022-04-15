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
	inline void iteration_test(benchmark::State &state)
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

	/**
	 * @brief Insertion test.
	 * This will take the time taken by entt to insert 2 entities.
	 *
	 * @param state The state counter.
	 */
	inline void insertion_test(benchmark::State &state)
	{
		entity::engine gameEngine;
		for (auto _ : state)
		{
			[[maybe_unused]] auto p = entity::player(gameEngine);
			[[maybe_unused]] auto c = entity::cat(gameEngine);
		}
	}

	/**
	 * @brief Deletion test.
	 * This will take the time taken by this implementation to delete 2 entities.
	 *
	 * @param state The state counter.
	 */
	inline void deletion_test(benchmark::State &state)
	{
		entity::engine gameEngine;
		for (auto _ : state)
		{
			[[maybe_unused]] auto p = entity::player(gameEngine);
			[[maybe_unused]] auto c = entity::cat(gameEngine);

			gameEngine.get_registry().destroy(p.get_entity());
			gameEngine.get_registry().destroy(c.get_entity());
		}
	}
}