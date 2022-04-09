// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "engine.hpp"
#include "inventory/component_store.hpp"

#include <type_traits>

class game_object_interface
{
public:
	virtual void update() = 0;
	virtual void update_components() = 0;
	virtual void update_components() const = 0;
};

template <class... Types>
class game_object : public game_object_interface, public inventory::component_store<Types...>
{
	engine &m_Engine;

	template <class Component, class... Components>
	void update_components()
	{
		m_Engine.update(inventory::get_component<Component>(this));

		if constexpr (sizeof...(Components) > 0)
			update_components<Components...>();
	}

	template <class Component, class... Components>
	void update_components() const
	{
		m_Engine.update(inventory::get_component<Component>(this));

		if constexpr (sizeof...(Components) > 0)
			update_components<Components...>();
	}

public:
	explicit game_object(engine &engine) : m_Engine(engine) {}

	void update_components() final { update_components<Types...>(); }
	void update_components() const final { update_components<Types...>(); }
};
