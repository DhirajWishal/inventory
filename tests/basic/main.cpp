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
using registry = inventory::registry<inventory::default_index_type, inventory::default_index_type, camera, world>;

int main()
{
	registry entityRegistry;
	auto ent = entityRegistry.create_entity();

	entityRegistry.register_to_system<camera>(ent);
	entityRegistry.register_to_system<world>(ent);

	auto something = entityRegistry.query_components<camera, world>();

	for (auto &entity : entityRegistry)
	{
		entityRegistry.get_component<world>(entity);
		if (entity.is_registered_to<camera>())
			auto &cameraComponent = entityRegistry.get_component<camera>(entity);
	}
}