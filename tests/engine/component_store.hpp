// Copyright (c) 2022 Dhiraj Wishal

#pragma once

template <class Type, class... Types>
class component_store : public component_store<Type>, public component_store<Types...>
{
};

template <class Type>
class component_store<Type>
{
	Type m_Component;

public:
	Type &get() { return m_Component; }
	const Type &get() const { return m_Component; }
};