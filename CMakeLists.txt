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

# Add the test subdirectories.
add_subdirectory(tests/basic)
add_subdirectory(tests/engine)