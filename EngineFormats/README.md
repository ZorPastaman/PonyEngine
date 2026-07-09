# Custom formats

The engine uses different custom formats for different purposes. Here are their descriptions.

## File resource manifest

The file resource manifest declares resources that are stored as individual files in a game build.

The binary variant of the format is used in game builds and is optimized for the target platform. 
The text variant is used in source assets and during the build configuration process.

### Text

The text variant is based on TOML. One of the root properties must be `schema` in the format `PonyEngine/Manifest/Resource/File/<version>`.
All other properties are dependent on the version.

#### V0

Example.toml
```
schema = 'PonyEngine/Manifest/Resource/File/v0'

[[resources]]
id = 'ResourceID'
type = 'ResourceType'
path = 'path/to/runtime/resource/file'
```

It has an array of `resources` where each resource must have these properties:
- `id` - resource ID. Its size must be [0, 255].
- `type` - resource type. Its size must be [0, 255].
- `path` - path to a file containing the resource. It's a runtime build path. Must be relative to a game root. Its size must be [0, 255].

### Binary

The binary variant is used only in the final game builds. That's why only the newest format must be used.

#### V0

The format extension must be `.pfrm` - Pony Engine file resource manifest.

Layout:

| Size     | Description                                       |
|:--------:|:--------------------------------------------------|
| 13       | Magic header. Must be `PonyEngineFRM`.            |
| variable | Resource array. See the layout below for details. |

Resource array layout:

| Size     | Description                                                                |
|:--------:|:---------------------------------------------------------------------------|
| 1        | Resource ID size.                                                          |
| 1        | Resource type size.                                                        |
| 1        | Resource path size.                                                        |
| [0, 255] | Resource ID. Must be utf-8 string.                                         |
| [0, 255] | Resource type. Must be utf-8 string.                                       |
| [0, 255] | Resource file path. Must be relative to a game root. Must be utf-8 string. |

## Pack resource manifest

The manifest describes a binary file that acts as a container for resources. 
The container consists of a raw byte array, and the manifest specifies the location of each resource within it.

The binary variant of the format is used in game builds and is optimized for the target platform. 
The text variant is used in source assets and during the build configuration process.

### Text

The text variant is based on TOML. One of the root properties must be `schema` in the format `PonyEngine/Manifest/Resource/Pack/<version>`.
All other properties are dependent on the version.

#### V0

Example.toml
```
schema = 'PonyEngine/Manifest/Resource/File/v0'
pack = 'path/to/runtime/binary/container'

[[resources]]
id = 'ResourceID'
type = 'ResourceType'
path = 'path/to/source/resource/file'
```

It has a property `pack` that tells a path to a binary resource container in a game build. It must be relative to a game root.

It has an array of `resources` where each resource must have these properties:
- `id` - resource ID. Its size must be [0, 255].
- `type` - resource type. Its size must be [0, 255].
- `path` - path to a file containing the resource. It's a build time path. Must be relative to a folder that is used as a root by a manifest compiler. Its size must be [0, 255].

### Binary

The binary variant is used only in the final game builds. That's why only the newest format must be used.

#### V0

The format extension must be `.pprm` - Pony Engine pack resource manifest.

Layout:

| Size     | Description                                                                     |
|:--------:|:--------------------------------------------------------------------------------|
| 13       | Magic header. Must be `PonyEnginePRM`.                                          |
| 1        | Resource pack file path size.                                                   |
| [0, 255] | Resource pack file path. Must be relative to a game root. Must be utf-8 string. |
| variable | Resource array. See the layout below for details.                               |

Resource array layout:

| Size                | Description                                    |
|:-------------------:|:-----------------------------------------------|
| sizeof(std::size_t) | Resource offset within the resource pack file. |
| sizeof(std::size_t) | Resource size within the resource pack file.   |
| 1                   | Resource ID size.                              |
| 1                   | Resource type size.                            |
| [0, 255]            | Resource ID. Must be utf-8 string.             |
| [0, 255]            | Resource type. Must be utf-8 string.           |

The resource offset and size have a size of `std::size_t` of a target platform.
That's why the resource container max size is `std::numeric_limits<std::size_t>::max()`.
