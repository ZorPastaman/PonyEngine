# PonyTools.FileResourceManifestGenerator

Creates and modifies text file resource manifest.

## Usage
```
ponyfrmg <input> [options]

Arguments:
	<input>             Input manifest file.

Options:
	--create            Create new file.
	--add <resource>    Add resource to manifest.
	                    <resource> format: '<id>,<type>,<path>'.
	--remove <id>       Remove resource from manifest.
	--upgrade           Upgrade manifest to the last version.
	--version           Display version information and exit.
	--verbose           Enable verbose output.
	--help              Display this help message and exit.
```

The input file must be file resource manifest compatible.
See [EngineFormats](../../EngineFormats) for details.
