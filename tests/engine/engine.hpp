// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "components.hpp"

#include <inventory/container.hpp>

class engine final : public inventory::container<engine>
{
public:
	void update([[maybe_unused]] const model_component &component) const;
	void update([[maybe_unused]] const camera_component &component) const;
	void update([[maybe_unused]] const position_component &component) const;

	template <class Type>
	void operator()(Type &element)
	{
		element.update();
		element.update_components();
	}

	template <class Type>
	void operator()(const Type &element) const
	{
		element.update_components();
	}
};