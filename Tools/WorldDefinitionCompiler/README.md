# PonyTools.WorldDefinitionCompiler tool

Compiles a world asset to a resource container of `Pony.WorldDefinition` type.

## How to use

```
PonyWorldDefinitionCompiler <input> [options]

Arguments:
	<input>                          Input asset file path, must be toml.
Options:
	-o <path>                        Resource data output file path.
	-s <path>                        Serializer library file path.
	-d <path>                        Dep file path.
	--size_t-size <number>           Target platform std::size_t size.
	--big-endian                     If set, target platform is treated as big-endian.
	--version                        Display version information and exit.
	--verbose                        Enable verbose output.
	--help                           Display this help message and exit.
```

Put an asset file as `<input>` and data output as `-o`.
The compiler doesn't use resource data or load parameters. It doesn't produce resource load file as well.
You also would like to use `-d` to make CMake or other tool to track dependencies.

## Custom serializer

Custom serializers must export the functions mentioned below. A serializer may export either component or object functions or both.

### Component serialization

#### `GetComponentTypes`

Signature: `std::span<const std::string_view>()`

Description: Gets component types.

#### `GetComponentSize`

Signature: `std::size_t(std::size_t typeIndex, const toml::table& componentTable, std::size_t sizeTSize)`

Description: Gets component size. Max value means error.

#### `SerializeComponentFunction`

Signature: `bool(std::size_t typeIndex, const toml::table& componentTable, std::span<std::byte> componentData, const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex, const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool isBigEndian)`

Description: Serializes component. If it returns false, it means failure. If it returns true, it means success.

### Object serialization

#### `GetObjectTypes`

Signature: `std::span<const std::string_view>()`

Description: Gets object types.

#### `GetObjectSize`

Signature: `std::size_t(std::size_t typeIndex, const toml::table& objectTable, std::size_t sizeTSize)`

Description: Gets object size. Max value means error.

#### `SerializeObjectFunction`

Signature: `bool(std::size_t typeIndex, const toml::table& objectTable, std::span<std::byte> objectData, std::size_t sizeTSize, bool isBigEndian)`

Description: Serializes object. If it returns false, it means failure. If it returns true, it means success.
