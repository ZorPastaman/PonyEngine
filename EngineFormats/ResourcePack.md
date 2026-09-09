# Resource pack format

Resource pack is a file format that contains several resources. It allows to reduce file count in a project build.

It consists of two files:

1. Manifest - contains resource metas;
2. Data - contains resource data.

## Manifest

It has info about resources in the pack and links to their data (data file offset and size).
It's a binary file, optimized for a target platform.

The file allows resources to link the same resource data via using the same resource range (data file offset and size).
All other resource parameters can be reused as well. That's why the resource is a bunch of indices to the list of those parameters.

Layout:

| Size                                                      | Description                                                                                                                       |
|:---------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------------------|
| 30                                                        | Magic word. Must be `PonyEngineResourcePackManifest`.                                                                             |
| sizeof(std::size_t)                                       | Resource type count.                                                                                                              |
| sizeof(std::size_t)                                       | Resource data meta count.                                                                                                         |
| sizeof(std::size_t)                                       | Load meta count.                                                                                                                  |
| sizeof(std::size_t)                                       | Range count.                                                                                                                      |
| 1 * resource type count                                   | Resource type size array.                                                                                                         |
| sizeof(std::size_t) * resource data meta count            | Resource data meta size array.                                                                                                    |
| sizeof(std::size_t) * resource load meta count            | Resource load meta size array.                                                                                                    |
| sizeof(std::pair<std::size_t, std::size_t>) * range count | Resource range array. First of every element is offset, second is size.                                                           |
| [0, 255] * resource type count                            | Resource type array. Every type is a string which length doesn't exceed 255 symbols.                                              |
| variable * resource data meta count                       | Resource data meta array. Every meta goes one after another.                                                                      |
| variable * resource load meta count                       | Resource load meta array. Every meta goes one after another.                                                                      |
| variable                                                  | Resource array till the end of file. Every element contains indices to other arrays and its ID. See the layout description below. |

Resource layout:

| Size                | Description               |
|:-------------------:|:--------------------------|
| sizeof(std::size_t) | Resource type index.      |
| sizeof(std::size_t) | Resource data meta index. |
| sizeof(std::size_t) | Resource load meta index. |
| sizeof(std::size_t) | Resource range index.     |
| 1                   | Resource ID size.         |
| [0, 255]            | Resource ID.              |

Because the file is optimized for a target platform and variables sizes are dependent on a target platform, the same manifest can't be reused for different platforms.
It must be built with all other parts of a project build.

## Data

It's a pure binary file that has resource binary data only. A manifest references it by a byte offset and size.

The same data file may be referenced by different manifest files.
