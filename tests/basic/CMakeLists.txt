# Copyright (c) 2022 Dhiraj Wishal

# Add the test executable.
add_executable(
	BasicTest
	main.cpp
)

# Set the include directory.
target_include_directories(BasicTest PUBLIC ${INVENTORY_INCLUDE_DIR})

# Set the C++ standard as C++20.
set_property(TARGET BasicTest PROPERTY CXX_STANDARD 20)

# Add a test.
add_test(NAME BasicTest COMMAND BasicTest)