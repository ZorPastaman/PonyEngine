# PonyTools.FileResourceManifestCompiler

Compiles text file resource manifest to binary file resource manifest.

## Usage
```
ponyfrmc <input> [options]

Arguments:
	<input>          Input manifest file.

Options:
	-o <output>      Output manifest file. The extension must be '.pfrm'.
	--version        Display version information and exit.
	--verbose        Enable verbose output.
	--help           Display this help message and exit.
```

The input file must be file resource manifest compatible.
The output file is binary and optimized for a target platform.
See [EngineFormats](../../EngineFormats) for details.

## Third party

- TOML++
