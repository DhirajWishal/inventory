// Copyright (c) 2022 Dhiraj Wishal

#include <inventory/inventory.hpp>
#include <inventory/entity.hpp>

void basic_test()
{
	struct Component
	{
		unsigned char byte = 0;
	};

	struct Apple final : Component
	{
	};

	struct Orange final : Component
	{
	};

	struct Banana final : Component
	{
	};

	struct Mango final : Component
	{
	};

	struct Updater
	{
		void operator()(Apple &component) {}
		void operator()(const Apple &component) const {}

		void operator()(Orange &component) {}
		void operator()(const Orange &component) const {}

		void operator()(Banana &component) {}
		void operator()(const Banana &component) const {}

		void operator()(Mango &component) {}
		void operator()(const Mango &component) const {}
	};
	auto registry = inventory::inventory<Updater>();
	[[maybe_unused]] auto &a = registry.emplace_back<Apple>();
	[[maybe_unused]] auto &o = registry.emplace_back<Orange>();
	[[maybe_unused]] auto &b = registry.emplace_back<Banana>();
	[[maybe_unused]] auto &m = registry.emplace_back<Mango>();

	Updater updater;
	registry.apply(updater);
}

// Setup the basic components.
struct model final
{
	float m_Matrix[4][4];
};
struct camera final
{
	float m_View[4][4], m_Proj[4][4];
};

// Setup the basic entities.
using player = inventory::entity<model, camera>;
using ghost = inventory::entity<model>;

// Templated update methods.
template <class Type>
void update(Type &data) {}

template <class Type>
void update(const Type &data) {}

// Player specialization of the update method.
template <>
void update<player>(player &p) { auto [mod, cam] = inventory::get_components<model, camera>(p); }

template <>
void update<player>(const player &p) { auto [mod, cam] = p.get_components<model, camera>(); }

// Ghost specialization of the update method.
template <>
void update<ghost>(ghost &g) { auto mod = inventory::get_component<model>(g); }

template <>
void update<ghost>(const ghost &g) { auto mod = g.get_component<model>(); }

// Setup the updater callable.
struct updater final
{
	template <class Type>
	void operator()(Type &entity)
	{
		update(entity);
	}

	template <class Type>
	void operator()(const Type &entity) const
	{
		update(entity);
	}
};

// Create the alias for the inventory where the callable is updater.
using entity_storage = inventory::inventory<updater>;

// Populate the storage with entities.
void populate_entities(entity_storage &storage)
{
	auto &p = storage.emplace_back<player>();
	auto &g = storage.emplace_back<ghost>();
}

// Update the entities.
void update_entities(entity_storage &storage)
{
	updater myUpdater;
	storage.apply(myUpdater);
}

void entity_test()
{
	entity_storage storage;

	populate_entities(storage);
	update_entities(storage);
}

int main()
{
	basic_test();
	entity_test();
}