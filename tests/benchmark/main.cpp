// Copyright (c) 2022 Dhiraj Wishal

#include <benchmark/benchmark.h>

static void test([[maybe_unused]] benchmark::State &state)
{
	for (auto _ : state)
		;
}
BENCHMARK(test);

BENCHMARK_MAIN();