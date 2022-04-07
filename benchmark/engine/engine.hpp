// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include <benchmark/benchmark.h>

#include "components.hpp"

class engine final
{
public:
	void update([[maybe_unused]] const model_component& component) const;
	void update([[maybe_unused]] const camera_component& component) const;
	void update([[maybe_unused]] const position_component& component) const;
};