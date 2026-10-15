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
