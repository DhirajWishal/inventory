// Copyright (c) 2022 Dhiraj Wishal

#include "engine/benchmark.hpp"
#include "entity/benchmark.hpp"

BENCHMARK(entt_test::insertion_test);
BENCHMARK(ivnt_test::insertion_test);

BENCHMARK(entt_test::deletion_test);
BENCHMARK(ivnt_test::deletion_test);

// 2 Objects.
BENCHMARK(entt_test::iteration_test<1>);
BENCHMARK(ivnt_test::iteration_test_query<1>);
BENCHMARK(ivnt_test::iteration_test_primitive<1>);

// 20 Objects.
BENCHMARK(entt_test::iteration_test<10>);
BENCHMARK(ivnt_test::iteration_test_query<10>);
BENCHMARK(ivnt_test::iteration_test_primitive<10>);

// 200 Objects.
BENCHMARK(entt_test::iteration_test<100>);
BENCHMARK(ivnt_test::iteration_test_query<100>);
BENCHMARK(ivnt_test::iteration_test_primitive<100>);

// 2000 Objects.
BENCHMARK(entt_test::iteration_test<1000>);
BENCHMARK(ivnt_test::iteration_test_query<1000>);
BENCHMARK(ivnt_test::iteration_test_primitive<1000>);

// 20000 Objects.
BENCHMARK(entt_test::iteration_test<10000>);
BENCHMARK(ivnt_test::iteration_test_query<10000>);
BENCHMARK(ivnt_test::iteration_test_primitive<10000>);

// 200000 Objects.
BENCHMARK(entt_test::iteration_test<100000>);
BENCHMARK(ivnt_test::iteration_test_query<100000>);
BENCHMARK(ivnt_test::iteration_test_primitive<100000>);

// 2000000 Objects.
BENCHMARK(entt_test::iteration_test<1000000>);
BENCHMARK(ivnt_test::iteration_test_query<1000000>);
BENCHMARK(ivnt_test::iteration_test_primitive<1000000>);

BENCHMARK_MAIN();