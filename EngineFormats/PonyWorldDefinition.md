# Pony.WorldDefinition resource type

World definition resource type.

## Data meta

Must be empty.

## Load meta

Must be empty.

## Data

| Size                                        | Description                    |
|:-------------------------------------------:|:-------------------------------|
| sizeof(std::size_t)                         | Entity count.                  |
| sizeof(std::size_t)                         | Component table count.         |
| sizeof(std::size_t)                         | Object count.                  |
| 1 * component table count                   | Component table type lengths.  |
| sizeof(std::size_t) * component table count | Component table entity counts. |
| 1 * object count                            | Object type lengths.           |
| sizeof(std::size_t) * component table count | Component table data sizes.    |
| sizeof(std::size_t) * object count          | Object data sizes.             |
| variable                                    | Component serialized types.    |
| variable                                    | Component entity indices.      |
| variable                                    | Object serialized types.       |
| variable                                    | Component table data.          |
| variable                                    | Object data.                   |

The component and object data require separate deserializers that are added to a world definition loader.

If a component has a reference to an entity or to an object, it must contain an index in its data in place of the reference.
The index must be `std::uint64_t`. Max value means no reference.

## Interface types

- `PonyEngine::World::WorldDefinition`
