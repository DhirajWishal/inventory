# Copyright (c) 2022 Dhiraj Wishal

# Add the test executable.
add_executable(
	EngineTest
	main.cpp
	engine.cpp
	cat.cpp
	player.cpp
)

# Set the include directory.
target_include_directories(EngineTest PUBLIC ${INVENTORY_INCLUDE_DIR})

# Set the C++ standard as C++17.
set_property(TARGET EngineTest PROPERTY CXX_STANDARD 17)

# Add a test.
add_test(NAME EngineTest COMMAND EngineTest)