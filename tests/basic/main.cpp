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
	const auto index = entityRegistry.attach_on_register_callback<camera>([](registry& reg, const registry::entity_index_type index) {});

	auto ent = entityRegistry.create_entity();

	[[maybe_unused]] auto& c = entityRegistry.register_to_system<camera>(ent);
	[[maybe_unused]] auto& w = entityRegistry.register_to_system<world>(ent);

	for (auto& entity : entityRegistry.query<camera, world>())
	{
		[[maybe_unused]] auto& cc = entityRegistry.get_component<world>(entity);
		[[maybe_unused]] auto& cw = entityRegistry.get_component<camera>(entity);
	}

	entityRegistry.detach_on_register_callback<camera>(index);
}