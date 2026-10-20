# World asset

Describes a world in TOML format.

## Layout

Main layout:

| Field name | Type   | Default value | Description                          |
|:-----------|:-------|:--------------|:-------------------------------------|
| schema     | string | N/A           | Must be `PonyEngine/Asset/World/v0`. |
| entity     | array  | Empty         | Entity array. See its layout below.  |
| object     | array  | Empty         | Object array. See its layout below.  |

Entity layout:

| Field name | Type   | Default value | Description                                                 |
|:-----------|:-------|:--------------|:------------------------------------------------------------|
| id         | string | N/A           | Must have a unique entity ID. Used for in-asset references. |
| component  | array  | Empty         | Component array. See its layout below.                      |

Component layout:

| Field name | Type   | Default value | Description                      |
|:-----------|:-------|:--------------|:---------------------------------|
| type       | string | N/A           | Component type.                  |
| ...        |        |               | Other fields are type dependent. |

Object layout:

| Field name | Type   | Default value | Description                                                 |
|:-----------|:-------|:--------------|:------------------------------------------------------------|
| id         | string | N/A           | Must have a unique object ID. Used for in-asset references. |
| type       | string | N/A           | Must have an object type.                                   |
| ...        |        |               | Other fields are type dependent.                            |

### Component layouts

#### `PonyEngine::World::Hierarchy::Parent`

Type: `Pony.Parent`

Layout:

| Field name | Type   | Default value | Description       |
|:-----------|:-------|:--------------|:------------------|
| parent     | string | N/A           | Parent entity ID. |

#### `PonyEngine::World::Hierarchy::LocalTransform2D`

Type: `Pony.Transform2D`

Layout:

| Field name | Type   | Default value | Description         |
|:-----------|:-------|:--------------|:--------------------|
| position   | table  | N/A           | Position.           |
| position.x | double | N/A           | Position X.         |
| position.y | double | N/A           | Position Y.         |
| rotation   | float  | N/A           | Rotation in degrees.|
| scale      | table  | N/A           | Scale.              |
| scale.x    | float  | N/A           | Scale X.            |
| scale.y    | float  | N/A           | Scale Y.            |

#### `PonyEngine::World::Hierarchy::LocalTransform3D`

Type: `Pony.Transform3D`

Layout:

| Field name | Type   | Default value | Description            |
|:-----------|:-------|:--------------|:-----------------------|
| position   | table  | N/A           | Position.              |
| position.x | double | N/A           | Position X.            |
| position.y | double | N/A           | Position Y.            |
| position.z | double | N/A           | Position Z.            |
| rotation   | table  | N/A           | Rotation in degrees.   |
| rotation.x | float  | N/A           | Rotation X in degrees. |
| rotation.y | float  | N/A           | Rotation Y in degrees. |
| rotation.z | float  | N/A           | Rotation Z in degrees. |
| scale      | table  | N/A           | Scale.                 |
| scale.x    | float  | N/A           | Scale X.               |
| scale.y    | float  | N/A           | Scale Y.               |
| scale.z    | float  | N/A           | Scale Z.               |

### Object layouts

## Example

```
schema = 'PonyEngine/Asset/World/v0'

[[entity]]
id = 'Char'
[[entity.component]]
type = 'Pony.Transform3D'
position = { x = 10.0, y = -5.5, z = 4.3 }
rotation = { x = 45.0, y = -87.5, z = -110.87 }
scale = { x = 1.0, y = 1.2, z = 0.7 }

[[entity]]
id = 'Sub-Char'
[[entity.component]]
type = 'Pony.Transform3D'
position = { x = 5.0, y = -8.5, z = 4.1 }
rotation = { x = 5.0, y = -8.5, z = -118.1 }
scale = { x = -1.0, y = 1.0, z = -0.7 }
[[entity.component]]
type = 'Pony.Parent'
parent = 'Char'

```
