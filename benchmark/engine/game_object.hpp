// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "engine.hpp"

#include <type_traits>

namespace engine
{
	class game_object_interface
	{
	public:
		virtual void update() = 0;
	};

	template <class... Types>
	class game_object : public game_object_interface, public inventory::component_store<Types...>
	{
		engine &m_Engine;

	public:
		explicit game_object(engine &engine) : m_Engine(engine) {}
	};
}