# Copyright (c) 2022 Dhiraj Wishal

# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.18.4)

# Set the basic project description.
project(
	inventory
	VERSION 1.0.0 
	DESCRIPTION "Entity storage system based on ECS and Composition Over Inheritance"
)

# Set the include directory.
set(INVENTORY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set a variable stating where the tests directory is.
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Set basic defines for google benchmark.
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

# Add the benchmark subdirectory.
add_subdirectory(tests/third_party/benchmark)

# Set the google benchmark include directory.
set(BENCHMARK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/third_party/benchmark/include)

# Set the EnTT library's include path.
set(ENTT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/third_party/entt/src)

# Add the test subdirectories.
add_subdirectory(${TESTS_DIR}/basic)
add_subdirectory(${TESTS_DIR}/engine)
add_subdirectory(${TESTS_DIR}/benchmark)

# Enable testing.
enable_testing()
