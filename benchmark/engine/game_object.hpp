// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "engine.hpp"

namespace engine
{
	class game_object
	{
		engine &m_Engine;
		entity m_Entity;

	public:
		explicit game_object(engine &engine) : m_Engine(engine), m_Entity(m_Engine.create_entity()) {}

		template <class Type, class... Types>
		Type& create_component(Types &&...arguments) { return m_Engine.register_to_system<Type>(m_Entity); }

		template <class Type>
		Type& get_component() const { return m_Engine.get_component<Type>(m_Entity); }

		virtual void update() = 0;
	};
}