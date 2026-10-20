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

## Component data layout

### `Pony.Name` - `PonyEngine::World::Meta::Name`

| Size               | Description  |
|:------------------:|:-------------|
| 1                  | Name length. |
| [0, MaxNameLength] | Name.        |

### `Pony.Description` - `PonyEngine::World::Meta::Description`

| Size | Description          |
|:----:|:---------------------|
| 8    | String object index. |

### `Pony.Parent` - `PonyEngine::World::Hierarchy::Parent`

| Size | Description          |
|:----:|:---------------------|
| 8    | Parent entity index. |

### `Pony.Transform2D` - `PonyEngine::World::Hierarchy::LocalTransform2D`

| Size | Description          |
|:----:|:---------------------|
| 8    | Position X.          |
| 8    | Position Y.          |
| 4    | Rotation in radians. |
| 4    | Scale X.             |
| 4    | Scale Y.             |

### `Pony.Transform3D` - `PonyEngine::World::Hierarchy::LocalTransform3D`

| Size | Description            |
|:----:|:-----------------------|
| 8    | Position X.            |
| 8    | Position Y.            |
| 8    | Position Z.            |
| 4    | Rotation X in radians. |
| 4    | Rotation Y in radians. |
| 4    | Rotation Z in radians. |
| 4    | Scale X.               |
| 4    | Scale Y.               |
| 4    | Scale Z.               |

## Object data layout

### `Pony.Resource`

| Size     | Description         |
|:--------:|:--------------------|
| 1        | Interface length.   |
| 1        | Resource ID length. |
| [0, 255] | Interface.          |
| [0, 255] | Resource ID.        |

Standard interface to type mapping:

| Interface     | Type               |
|:--------------|:-------------------|
| `Pony.String` | `std::string_view` |
