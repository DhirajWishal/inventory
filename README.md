# inventory

Entity and component storage system for games based on Composition Over Inheritance.

## Why inventory?

While there are excellent solutions like [EnTT](https://github.com/skypjack/entt),
it more or less distances the connection between data and logic. Inventory can be
used to tightly couple game logic, and components together, and use compile time
goodness to optimize the storage system.

This can be especially useful if your game framework uses C++ to code the game logic,
like what we have in Unreal Engine.

## How it works

Inventory works just like an array of entities, but here, unlike other ECS implementation
where entities are just integers, entities are classes which contains the components as
member variables. Inventory provides an component storage system which works much like
`std::tuple`. Having the components locally means that we can easily access them at runtime
opposed to adding additional mechanisms to index those components.

But the difference between containers like `std::vector` and inventory is that, here you can
store almost any type of instantiate-able object, and can be accessed and updated using a callable.
The only requirement for a callable is that it should be invocable, meaning that it could also be
a function.

We try to keep things as simple as possible, and let the compiler handle most of the things rather
than relying on the runtime to resolve different functionalities, which would obviously take more
resources.

## How to use

Since this library is header-only, all you need to do is, clone this repository and set the include
directory to `{CLONE DIR}/include` and you can start by including the `inventory/inventory.hpp` file.

### Simple demo

```cpp
#include <inventory/inventory.hpp>
#include <inventory/entity.hpp>

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

int main()
{
    entity_storage storage;

    populate_entities(storage);
    update_entities(storage);
}
```

### Complex demo

And now to show a complex demonstration, lets take a simple scenario. Let's say that our game framework
is based on C++, and we have some components.

```cpp
struct position { vec3 m_Coordinates; };
struct transform { mat4 m_Matrix; };
struct rotation { mat4 m_Matrix; };
struct camera { mat4 m_View; mat4 m_Proj; };
...
```

And now we have a central object, called `game_object`. This class is templated, and inherits the
`inventory::component_store` class.

```cpp
#include <inventory/component_store.hpp>

class game_object_interface
{
public:
    virtual void update() = 0;
    virtual void update_components() = 0;
    virtual void update_components() const = 0;
};

template <class... Types>
class game_object : public game_object_interface, public inventory::component_store<Types...>
{
    engine &m_Engine;

    template <class Component, class... Components>
    void update_components()
    {
        m_Engine.update(inventory::get_component<Component>(this));

        if constexpr (sizeof...(Components) > 0)
            update_components<Components...>();
    }

    template <class Component, class... Components>
    void update_components() const
    {
        m_Engine.update(inventory::get_component<Component>(this));

        if constexpr (sizeof...(Components) > 0)
            update_components<Components...>();
    }

public:
    explicit game_object(engine &engine) : m_Engine(engine) {}

    void update_components() final { update_components<Types...>(); }
    void update_components() const final { update_components<Types...>(); }
};
```

The game engine is responsible for updating the components. This is where we have to have an instance
of the `inventory::inventory` class. This also needs a callable which will be used to update the game
objects and its components.

```cpp
#include <inventory/inventory.hpp>

class engine
{
    inventory::inventory<game_object_updater> m_Inventory;
    game_object_updater m_Updater;

public:
    engine() = default;

    template <class Type, class... Args>
    Type &create(Args &&...arguments) { return m_Inventory.emplace_back<Type>(*this, std::forward<Args>(arguments)...); }

    void update([[maybe_unused]] const position &component) const { ... }
    void update([[maybe_unused]] const transform &component) const { ... }
    void update([[maybe_unused]] const rotation &component) const { ... }
    void update([[maybe_unused]] const camera &component) const { ... }

    void update_entities() { m_Inventory.apply(m_Updater); }
};
```

Now we need the callable `game_object_updater` `struct`, which is used to update the entity and its
components.

```cpp
struct game_object_updater
{
    template <class Type>
    void operator()(Type &element)
    {
        if constexpr (std::is_base_of_v<game_object_interface, Type>)
        {
            element.update();
            element.update_components();
        }
    }

    template <class Type>
    void operator()(const Type &element) const
    {
        if constexpr (std::is_base_of_v<game_object_interface, Type>)
        {
            element.update_components();
        }
    }
};
```

Finally, we can create the entities and put everything together.

```cpp
class player final : public game_object<position, transform, rotation, camera>
{
public:
    player(engine &engine) : game_object(engine) {}

    void update() override { auto [pos, trans, cam] = inventory::get_components<position, transform, camera>(this); }
}

class car final : public game_object<position, transform, camera>
{
public:
    car(engine &engine) : game_object(engine) {}

    void update() override { auto [pos, trans, cam] = inventory::get_components<position, transform, camera>(this); }
}

class tree final : public game_object<transform, camera>
{
public:
    tree(engine &engine) : game_object(engine) {}

    void update() override { auto &cam = inventory::get_component<camera>(this); }
}

// Entry point
int main()
{
    engine game_engine;

    game_engine.create<player>();
    game_engine.create<car>();
    game_engine.create<tree>();

    game_engine.update_entities();
}
```

Optionally you can inherit from the `inventory::inventory` class but that's up to the developer. I wouldn't expect
any significant (performance) gain from it other than some API differences.

## Built in entity

This library also comes with a build-in entity which basically resembles a normal entity that we can find with
other ECS implementation, but again, it's a class not an integer. You can instantiate them by providing the
components as template arguments.

## Benchmarks

The workflow contains a simple benchmark, basically `inventory` against `entt`. Note that this is not to say that
`entt` is bad, it sucks or whatever, this is to show that `inventory` has a slight edge over that library thanks
to compile time optimizations and higher data locality.

On average, `inventory` is 2 to 4 times faster than `entt` when iterating over entities and updating components.

## License

This repository is licensed under MIT.
