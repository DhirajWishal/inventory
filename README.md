# inventory

Entity Component System but a bit bulky, but fast!

## How it works

This system works on the following principals.

1. Components are stored in systems, and they're aware of the entities that they're bound to.
2. A system is responsible for creating new components, managing them and for iterating over them.
3. Entities are registered to these systems.
4. Entities does not hold the component itself, but rather holds the component index which can be used to get the component from the system.
5. A registry is used to manage entities and systems.
6. All the possible component types needs to be known at compile time by the registry.

Using those principals, we can largely optimize the library, by making it more memory efficient and adhering to cache friendly-ness. And
since entities are aware of the components that they are bound to, we can easily access them using the component index. Same thing applies to
components, since they know about who owns them, we can easily query the entity and get its information.

By knowing all the components that are to be stored by the registry, we can optimize the storage and retrieval of those systems from the
registry. Because of this, we don't have to rely on legacy methods, like using inheritance. But one large downside, that we must admit,
is that this would require a single bulky `using` alias, as we need to know all the components once. One way to deal with this is by
optimizing the entities by letting it only connect to a selected number of entities, essentially partitioning the system into tiny
systems, which is totally up to you. The worst you can get is something like this (I'm citing Unity here),

```cpp
using registry = inventory::registry<
    inventory::default_index_type,
    inventory::default_index_type, 

    AudioChorusFilter,
    AudioDistortionFilter,
    AudioEchoFilter,
    AudioHighPassFilter,
    AudioListener,
    AudioLowPassFilter,
    AudioReverbFilter,
    AudioReverbZone,
    AudioSource,

    HaloEffect,
    LenseFlair,
    LineRenderer,
    ParticleSystem,
    Projector, 
    TrailRenderer,
    VisualEffect,

    EventSystem,
    EventTrigger,
    ...
```

Note that the `inventory::registry` can be copied, but should not be done often, as it is a heavy object (typically the `sizeof(inventory::registry)`
size would be `(sizeof(std::vector<>) * 3) + (sizeof(std::vector<>) * 3 * component_count)`) and may result in bad performance. Passing by
reference/ pointer or moving it to wherever needed will be the safest option.

And fun fact, it can store any type of data! :)

## How to use

Since this library is header-only, all you need to do is, clone this repository and set the include
directory to `{CLONE DIR}/include` and you can start by including the `inventory/registry.hpp` file.

## Simple demo

```cpp
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

    for (auto &entity : entityRegistry.query_components<camera, world>())
    {
        entityRegistry.get_component<world>(entity);
        entityRegistry.get_component<camera>(entity);
    }
}
```

## Benchmarks

The workflow contains a simple benchmark, basically `inventory` against `entt`. Note that this is not to say that
`entt` is bad, it sucks or whatever, this is to show that `inventory` has a slight edge over that library thanks
to compile time optimizations and higher data locality.

## License

This repository is licensed under MIT.
