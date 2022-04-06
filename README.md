# inventory

Entity storage system for games based on Composition Over Inheritance.

## Why inventory?

While there are excellent solutions like [EnTT](https://github.com/skypjack/entt),
it more or less distances the connection between data and logic. Inventory can be
used to tightly couple game logic, and components together, and use compile time
goodness to optimize the storage system.
