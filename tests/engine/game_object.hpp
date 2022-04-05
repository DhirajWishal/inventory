// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "engine.hpp"
#include "component_store.hpp"

#include <type_traits>

class game_object_interface
{
public:
	virtual void update() = 0;
	virtual void update_components() = 0;
	virtual void update_components() const = 0;
};

template <class... Types>
class game_object : public game_object_interface, private component_store<Types...>
{
	engine &m_Engine;

	template <class Component, class... Components>
	void update_components()
	{
		m_Engine.update(get_component<Component>());

		if constexpr (sizeof...(Components))
			update_components<Components...>();
	}

	template <class Component, class... Components>
	void update_components() const
	{
		m_Engine.update(get_component<Component>());

		if constexpr (sizeof...(Components))
			update_components<Components...>();
	}

public:
	game_object(engine &engine) : m_Engine(engine) {}

	template <class Type>
	Type &get_component() { return component_store<Type>::get(); }

	template <class Type>
	const Type &get_component() const { return component_store<Type>::get(); }

	void update_components() override final { update_components<Types...>(); }
	void update_components() const override final { update_components<Types...>(); }
};

struct game_object_updater
{
	template <class Type>
	void operator()(std::remove_const_t<Type> &element)
	{
		element.update();
		element.update_components();
	}

	template <class Type>
	void operator()([[maybe_unused]] const Type &element) const
	{
		element.update_components();
	}
};