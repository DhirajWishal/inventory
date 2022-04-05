# Copyright (c) 2022 Dhiraj Wishal

# Add the core source files as a library, so we can reuse them from other tests.
add_library(
	Engine
	STATIC
	cat.cpp
	engine.cpp
	player.cpp
)

# Add the test executable.
add_executable(
	EngineTest
	main.cpp
)

# Set the include directory.
target_include_directories(EngineTest PUBLIC ${INVENTORY_INCLUDE_DIR})

# Add the engine as a target link library.
target_link_libraries(EngineTest Engine)

# Set the C++ standard as C++17.
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
set_property(TARGET EngineTest PROPERTY CXX_STANDARD 17)

# Add a test.
add_test(NAME EngineTest COMMAND EngineTest)