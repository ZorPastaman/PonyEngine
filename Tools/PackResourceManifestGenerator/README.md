# PonyTools.PackResourceManifestGenerator

Creates and modifies text pack resource manifest.

## Usage
```
ponyprmg <input> [options]

Arguments:
	<input>          Input manifest file.

Options:
	--create <path>     Create new file and sets runtime pack path to <path>.
	--add <resource>    Add resource to manifest.
	                    <resource> format: '<id>,<type>,<path>'.
	--remove <id>       Remove resource from manifest.
	--upgrade           Upgrade manifest to the last version.
	--version           Display version information and exit.
	--verbose           Enable verbose output.
	--help              Display this help message and exit.
```

The input file must be pack resource manifest compatible.
See [EngineFormats](../../EngineFormats) for details.
