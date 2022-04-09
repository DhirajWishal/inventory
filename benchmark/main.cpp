// Copyright (c) 2022 Dhiraj Wishal

#include "engine/benchmark.hpp"
#include "entity/benchmark.hpp"

BENCHMARK(entt_test::test<1>);
BENCHMARK(ivnt_test::test<1>);

BENCHMARK(entt_test::test<10>);
BENCHMARK(ivnt_test::test<10>);

BENCHMARK(entt_test::test<100>);
BENCHMARK(ivnt_test::test<100>);

BENCHMARK(entt_test::test<1000>);
BENCHMARK(ivnt_test::test<1000>);

BENCHMARK(entt_test::test<10000>);
BENCHMARK(ivnt_test::test<10000>);

BENCHMARK(entt_test::test<100000>);
BENCHMARK(ivnt_test::test<100000>);

BENCHMARK(entt_test::test<1000000>);
BENCHMARK(ivnt_test::test<1000000>);

BENCHMARK_MAIN();