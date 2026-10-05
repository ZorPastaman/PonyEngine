# Pony.WorldDefinition resource type

World definition resource type.

## Data meta

Must be empty.

## Load meta

Must be empty.

## Data

| Size                      | Description             |
|:-------------------------:|:------------------------|
| sizeof(std::size_t)       | Entity count.           |
| sizeof(std::size_t)       | Component table count.  |
| sizeof(std::size_t)       | Component object count. |
| variable                  | Component tables.       |
| variable                  | Component objects.      |

Component table layout:

| Size                               | Description          |
|:----------------------------------:|:---------------------|
| 1                                  | Type name size.      |
| [0, 255]                           | Type name.           |
| sizeof(std::size_t)                | Entity count.        |
| sizeof(std::size_t) * entity count | Entity indices.      |
| sizeof(std::size_t)                | Component data size. |
| variable                           | Component data.      |

Object layout:

| Size                | Description       |
|:-------------------:|:------------------|
| 1                   | Type name size.   |
| [0, 255]            | Type name.        |
| sizeof(std::size_t) | Object data size. |
| variable            | Object data.      |

The `Pony.WorldDefinition` format is type-agnostic: it does not contain information about component or object types.
For component deserialization, string component type names must be registered and mapped to their corresponding std::type_index. The loader then copies the serialized component data into the corresponding component definition data arrays.
Object deserialization is handled by type-specific sub-loaders, which must be provided for each object type used by the world.

If a component has a reference to an entity or to an object, it must contain an index in its data in place of the reference.
The index must be `std::uint64_t`. Max value means no reference.

## Interface types

- `PonyEngine::World::WorldDefinition`
