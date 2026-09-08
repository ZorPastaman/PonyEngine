# PonyText resource type

Text resource type.

## Data meta

Must be empty

## Load meta

| Size     | Description            |
|:--------:|:-----------------------|
| 1 (bool) | Direct resource usage. |

If the direct resource usage is enabled, the resource will directly reference a string in a resource data - the resource data must be in the memory and not compressed.
Otherwise, the loader creates a dedicated buffer for the text resource and loads data into it.

## Interface types

- `std::string_view`
