# Pony.Text resource type

World definition resource type.

## Data meta

Must be empty.

## Load meta

Must be empty.

## Data

| Size                | Description            |
|:-------------------:|:-----------------------|
| 4                   | Entity count.          |
| sizeof(std::size_t) | Component table count. |
| variable            | Component tables.      |
| sizeof(std::size_t) | Object count.          |
| variable            | Objects.               |
| sizeof(std::size_t) | World data count.      |
| variable            | World data.            |

Component table layout:

| Size                | Description          |
|:-------------------:|:---------------------|
| 1                   | Type name size.      |
| [0, 255]            | Type name.           |
| 4                   | Entity count.        |
| 4 * entity count    | Entity indices.      |
| sizeof(std::size_t) | Component data size. |
| variable            | Component data.      |

Object layout:

| Size                | Description       |
|:-------------------:|:------------------|
| 1                   | Type name size.   |
| [0, 255]            | Type name.        |
| sizeof(std::size_t) | Object data size. |
| variable            | Object data.      |

World data layout:

| Size                | Description       |
|:-------------------:|:------------------|
| 1                   | Type name size.   |
| [0, 255]            | Type name.        |
| sizeof(std::size_t) | Object data size. |
| variable            | Object data.      |

The `Pony.WorldDef` format doesn't know how to deserialize custom types. So, for each component, object and world data type, separate deserializers must be added.

If a component has a reference to an entity or to an object, it must contain an index in its data in place of the reference.
The index must be `std::uint64_t`. Max value means no reference.

## Interface types

- `PonyEngine::World::WorldDefinition`
