# Copyright (c) 2022 Dhiraj Wishal

# Add the test executable.
add_executable(
	Benchmark
	main.cpp
	engine/engine.cpp

	entity/benchmark.cpp
	entity/cat.cpp
	entity/engine.cpp
	entity/player.cpp
 "engine/cat.cpp" "engine/cat.hpp" "engine/component_store.hpp" "engine/components.hpp"   "engine/game_object.hpp" "engine/player.cpp" "engine/player.hpp")

# Set the include directory.
target_include_directories(Benchmark PUBLIC ${INVENTORY_INCLUDE_DIR} ${BENCHMARK_INCLUDE_DIR} ${ENTT_INCLUDE_DIR} ${TESTS_DIR})

# Set the C++ standard as C++20.
set_property(TARGET Benchmark PROPERTY CXX_STANDARD 20)

# Add a test.
add_test(NAME Benchmark COMMAND Benchmark)

# Add the benchmark library as a target link library.
target_link_libraries(Benchmark benchmark::benchmark)