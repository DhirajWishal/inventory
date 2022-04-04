#include "../include/inventory/inventory.hpp"

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

int main()
{
	auto registry = inventory::inventory<Updater>();
	registry.emplace_back<Apple>();
	registry.emplace_back<Orange>();
	registry.emplace_back<Banana>();
	registry.emplace_back<Mango>();

	Updater updater;
	registry.apply(updater);
}