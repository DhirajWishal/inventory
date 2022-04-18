# inventory

Entity Component System but a bit bulky, but fast!

Note that this repository is made for fun, and to explore what ECS actually looks like under the hood. If you feel like giving it a shot, the
provided demo would be a great start. Apart from that, you can check out the tests and benchmark code to get a basic understanding and I should
say, good luck soldier!

## How it works

This system works on the following principals.

1. Components are stored in systems.
2. A system is responsible for creating new components, managing them and for iterating over them.
3. Entities are registered to these systems.
4. Entities does not hold the component itself, but rather holds the component index which can be used to get the component from the system.
5. A registry is used to manage entities and systems and also contains other features.
6. All the possible component types needs to be known at compile time by the registry (this might be subjected to changes).

Using those principals, we can largely optimize the library, by making it more memory efficient and adhering to cache friendly-ness. And
since entities are aware of the components that they are bound to, we can easily access them using the component index. And since we use
a custom bitset implementation, the overhead to check if an entity uses a component is basically 1 bit, and it's just one array index away.

By knowing all the components that are to be stored by the registry, we can optimize the storage and retrieval of those systems from the
registry. Because of this, we don't have to rely on legacy methods, like using inheritance. But one large downside, that we must admit,
is that this would require a single bulky `using` alias in most cases, as we need to know all the components once. One way to deal with this
is by optimizing the entities by letting it only connect to a selected number of entities, essentially partitioning the system into tiny
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
size would be `(sizeof(std::vector<>) * 3) + (sizeof(std::vector<>) * 5 * component_count)`) and may result in bad performance. Passing by
reference/ pointer or moving it to wherever needed will be the safest option.

And fun fact, it can store any type of data! :)

## How to use

Since this library is header-only, all you need to do is, clone this repository and set the include
directory to `{CLONE DIR}/include` and you can start by including the `inventory/registry.hpp` file.

## Simple demo

```cpp
#include <inventory/registry.hpp>

using vec3 = std::array<float, 3>;
using mat4 = std::array<float, 16>;

struct model
{
    mat4 m_Matrix;
};

struct camera
{
    mat4 m_View;
    mat4 m_Proj;
};

struct position
{
    vec3 m_Vector;
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
```

## Benchmarks

The workflow contains a simple benchmark, basically `inventory` against `entt`. Note that this is not to say that `entt` is bad,
it sucks or whatever (it's clearly superior to this implementation), this is to show that `inventory` has a slight edge over that
library thanks to compile time optimizations and quick lookups (both to check if an entity is registered or to get the component index).

## License

This repository is licensed under MIT.
