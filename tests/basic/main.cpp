// Copyright (c) 2022 Dhiraj Wishal

#include <inventory/container.hpp>
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

	struct Updater final : public inventory::container<Updater>
	{
		void operator()([[maybe_unused]] Apple &component) {}
		void operator()([[maybe_unused]] const Apple &component) const {}

		void operator()([[maybe_unused]] Orange &component) {}
		void operator()([[maybe_unused]] const Orange &component) const {}

		void operator()([[maybe_unused]] Banana &component) {}
		void operator()([[maybe_unused]] const Banana &component) const {}

		void operator()([[maybe_unused]] Mango &component) {}
		void operator()([[maybe_unused]] const Mango &component) const {}
	};
	Updater updater;
	[[maybe_unused]] auto &a = updater.emplace_back<Apple>();
	[[maybe_unused]] auto &o = updater.emplace_back<Orange>();
	[[maybe_unused]] auto &b = updater.emplace_back<Banana>();
	[[maybe_unused]] auto &m = updater.emplace_back<Mango>();

	updater.apply();

	updater.apply_custom(std::type_index(typeid(Apple)));
	updater.apply_manual<Apple>();

	updater.apply_custom(std::type_index(typeid(Orange)));
	updater.apply_manual<Orange>();

	updater.apply_custom(std::type_index(typeid(Banana)));
	updater.apply_manual<Banana>();

	updater.apply_custom(std::type_index(typeid(Mango)));
	updater.apply_manual<Mango>();
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
struct updater final : public inventory::container<updater>
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
using entity_storage = updater;

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
	storage.apply();

	storage.apply_custom(std::type_index(typeid(player)));
	storage.apply_custom(std::type_index(typeid(ghost)));

	storage.apply_manual<player>();
	storage.apply_manual<ghost>();
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