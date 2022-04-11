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

using camera_system = inventory::system<camera>;
using world_system = inventory::system<std::pair<model, position>>;

int main()
{
	inventory::entity_factory factory;
	auto entity = factory.create();

	camera_system cameraSystem;
	world_system worldSystem;

	worldSystem.link(cameraSystem);

	cameraSystem.register_entity(entity);
	worldSystem.register_entity(entity);

	for (auto &entry : worldSystem)
	{
		auto entity = entry.first;
		auto &component = entry.second;

		if (cameraSystem.is_registered(entity))
			auto &cameraComponent = cameraSystem.get(entity);
	}
}