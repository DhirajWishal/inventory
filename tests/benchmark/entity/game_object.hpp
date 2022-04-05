// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "engine.hpp"

namespace entity
{
	class game_object
	{
		engine& m_Engine;
		entt::entity m_EntityID = {};

	public:
		explicit game_object(engine& engine) : m_Engine(engine), m_EntityID(m_Engine.create_entity()) {}

		template <class Type, class... Types>
		decltype(auto) create_component(Types &&...arguments) { return m_Engine.get_registry().emplace<Type>(m_EntityID, std::forward<Types>(arguments)...); }

		template <class Type>
		decltype(auto) get_component() const { return m_Engine.get_registry().get<Type>(m_EntityID); }

		virtual void update() = 0;
	};
}