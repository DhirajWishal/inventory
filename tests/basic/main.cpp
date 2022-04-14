// Copyright (c) 2022 Dhiraj Wishal

#include <inventory/registry.hpp>

struct model
{
	std::array<float, 16> m_Matrix;
};

struct camera
{
	std::array<float, 16> m_View;
	std::array<float, 16> m_Proj;
};

struct position
{
	std::array<float, 3> m_Vector;
};

using world = std::pair<model, position>;
using registry = inventory::default_registry<camera, world>;

int main()
{
	registry entityRegistry;
	auto ent = entityRegistry.create_entity();

	entityRegistry.register_to_system<camera>(ent);
	entityRegistry.register_to_system<world>(ent);

	for (auto &entity : entityRegistry.query<camera, world>())
	{
		entityRegistry.get_component<world>(entity);
		entityRegistry.get_component<camera>(entity);
	}
}