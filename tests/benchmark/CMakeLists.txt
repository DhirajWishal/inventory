# Copyright (c) 2022 Dhiraj Wishal

# Add the test executable.
add_executable(
	Benchmark
	main.cpp
)

# Set the include directory.
target_include_directories(Benchmark PUBLIC ${INVENTORY_INCLUDE_DIR} ${BENCHMARK_INCLUDE_DIR})

# Set the C++ standard as C++17.
set_property(TARGET Benchmark PROPERTY CXX_STANDARD 17)

# Add a test.
add_test(NAME Benchmark COMMAND Benchmark)

# Add the benchmark library as a target link library.
target_link_libraries(Benchmark benchmark::benchmark)