// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "game_object.hpp"

namespace engine
{
	class cat final : public game_object
	{
	public:
		explicit cat(engine& engine);

		void update() override;
	};
}