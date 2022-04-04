# Copyright (c) 2022 Dhiraj Wishal

# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.22.2)

# Set the basic project description.
project(
	inventory
	VERSION 1.0.0 
	DESCRIPTION "Entity storage system based on ECS and Composition Over Inheritance"
)

# Set the include directory.
set(INVENTORY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the test executable.
add_executable(
	Tests
	tests/main.cpp
)

# Set the include directory.
target_include_directories(Tests PUBLIC ${INVENTORY_INCLUDE_DIR})

# Set the C++ standard as C++20.
set_property(TARGET Tests PROPERTY CXX_STANDARD 20)