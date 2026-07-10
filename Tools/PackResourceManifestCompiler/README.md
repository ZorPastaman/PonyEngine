# PonyTools.PackResourceManifestCompiler

Compiles text pack resource manifest to binary pack resource manifest and binary data container.

## Usage
```
ponyprmc <input> [options]

Arguments:
	<input>          Input manifest file.

Options:
	-po <output>     Output pack data file.
	-mo <output>     Output manifest file. The extension must be '.pprm'.
	-r <path>        Root path of resources in the source manifest.
	-d <path>        Dep file path.
	                 If set, it must be absolute.
	                 If not set, the input manifest directory is used as a root.
	--size-t         std::size_t size of a target platform. Can't be greater than host platform std::uintmax_t.
	--big-endian     Must be set if the target platform has big-endian memory; otherwise don't set it.
	--version        Display version information and exit.
	--verbose        Enable verbose output.
	--help           Display this help message and exit.
```

The input file must be pack resource manifest compatible.
The output file is two file: binary manifest and binary container. Both are optimized for a target platform.
See [EngineFormats](../../EngineFormats) for details.
