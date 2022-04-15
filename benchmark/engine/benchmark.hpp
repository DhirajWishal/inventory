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
	inline void iteration_test_primitive(benchmark::State &state)
	{
		engine::engine gameEngine;
		for (int i = 0; i < ObjectCount; i++)
		{
			[[maybe_unused]] auto p = engine::player(gameEngine);
			[[maybe_unused]] auto c = engine::cat(gameEngine);
		}

		for (auto _ : state)
			gameEngine.update_primitive();
	}

	/**
	 * @brief Test function to test the engine.
	 *
	 * @param state The benchmark state.
	 */
	template <int ObjectCount>
	inline void iteration_test_query(benchmark::State &state)
	{
		engine::engine gameEngine;
		for (int i = 0; i < ObjectCount; i++)
		{
			[[maybe_unused]] auto p = engine::player(gameEngine);
			[[maybe_unused]] auto c = engine::cat(gameEngine);
		}

		for (auto _ : state)
			gameEngine.update();
	}

	/**
	 * @brief Insertion test.
	 * This will take the time taken by this implementation to insert 2 entities.
	 *
	 * @param state The state counter.
	 */
	inline void insertion_test(benchmark::State &state)
	{
		engine::engine gameEngine;
		for (auto _ : state)
		{
			[[maybe_unused]] auto p = engine::player(gameEngine);
			[[maybe_unused]] auto c = engine::cat(gameEngine);
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
		engine::engine gameEngine;
		for (auto _ : state)
		{
			[[maybe_unused]] auto p = engine::player(gameEngine);
			[[maybe_unused]] auto c = engine::cat(gameEngine);

			gameEngine.get_registry().destroy_entity(p.get_entity());
			gameEngine.get_registry().destroy_entity(c.get_entity());
		}
	}
}