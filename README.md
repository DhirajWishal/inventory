# inventory

Entity storage system for games based on Composition Over Inheritance.

## Why inventory?

While there are excellent solutions like [EnTT](https://github.com/skypjack/entt),
it more or less distances the connection between data and logic. Inventory can be
used to tightly couple game logic, and components together, and use compile time
goodness to optimize the storage system.

This library relies on inheritance. Most developers have this stigma with performance
and inheritance, but I need to stress this point, inheritance is not the issue, polymorphism
is. Dynamic dispatch and heap allocation (non-contentious) is the cause of all this rage.
Because of this, inventory tries its best to reduce polymorphism, and uses compile time
optimizations to overcome this issue.