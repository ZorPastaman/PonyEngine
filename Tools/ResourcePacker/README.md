# PonyTools.ResourcePacker tool

Packs multiple resources into a single pack file.

It uses `ResourceContainer` as a resource source and packs them into `ResourcePack`.

## How to use

```
PonyResourcePacker [options]

Options:
	-p <path>                              Pack data parameters.
	-o <path>                              Pack data output path.
	-m <resource_list> <params> <output>   Pack manifest.
	-d <path>                              Dep file path.
	--size_t-size <number>                 Target platform std::size_t size.
	--big-endian                           If set, target platform is treated as big-endian.
	--version                              Display version information and exit.
	--verbose                              Enable verbose output.
	--help                                 Display this help message and exit.
```

Put a pack data parameters to `-p` and pack data output to `-o`.
Because a pack may have as many manifests as it needs, every manifest is added via `-m`.
You should set paths to a resource list file, to a manifest parameters and a pack manifest output.

The resource list format is simple. On each line you set a resource ID, a path to a resource data and a path to a resource load.
Like this:

```
Description "Text/TextData.bin" "Text/TextLoad.bin"
Character Meshes/CharacterMeshData.bin Meshes/CharacterMeshLoad.bin

```

## Data parameters

TOML layout:

| Field name    | Type   | Default value | Description                                                                             |
|:--------------|:-------|:--------------|:----------------------------------------------------------------------------------------|
| schema        | string | N/A           | Must be `PonyEngine/Resource/Pack/Data/v0`.                                             |
| deterministic | bool   | false         | If true, it guarantees that the same resource data set will produce the same pack data. |

## Manifest parameters

TOML layout:

| Field name           | Type   | Default value | Description                                     |
|:---------------------|:-------|:--------------|:------------------------------------------------|
| schema               | string | N/A           | Must be `PonyEngine/Resource/Pack/Manifest/v0`. |
| deduplicateTypes     | bool   | true          | If true, deduplicates resource types.           |
| deduplicateDataMetas | bool   | true          | If true, deduplicates resource data metas.      |
| deduplicateLoadMetas | bool   | true          | If true, deduplicates resource load metas.      |
| deduplicateRanges    | bool   | true          | If true, deduplicates resource data ranges.     |
