// Copyright (c) 2022 Dhiraj Wishal

#include <inventory/system.hpp>
#include <inventory/entity_factory.hpp>
#include <array>

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

using entity = inventory::entity<inventory::default_component_index_type, camera, std::pair<model, position>>;

using camera_system = inventory::system<entity, camera>;
using world_system = inventory::system<entity, std::pair<model, position>>;

int main()
{
	inventory::entity_factory<entity> factory;
	auto ent = factory.create();

	camera_system cameraSystem;
	world_system worldSystem;

	cameraSystem.register_entity(ent);
	worldSystem.register_entity(ent);

	for (auto &entry : worldSystem)
	{
		auto& entity = entry.entity();
		auto &component = entry.component();

		if (entity.is_registered_to<camera>())
			auto &cameraComponent = cameraSystem.get(entity);
	}
}