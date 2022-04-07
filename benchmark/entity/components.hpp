// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include <array>

namespace entity
{
	using vec2 = std::array<float, 2>;
	using vec3 = std::array<float, 3>;
	using vec4 = std::array<float, 4>;

	using mat33 = std::array<vec3, 3>;
	using mat44 = std::array<vec4, 4>;

	struct model_component final
	{
		mat44 m_Matrix;
	};

	struct camera_component final
	{
		mat44 m_View;
		mat44 m_Proj;
	};

	struct position_component final
	{
		vec3 m_Position;
	};
}