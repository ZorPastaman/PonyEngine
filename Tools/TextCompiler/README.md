# PonyTools.TextCompiler tool

Compiles any file to a resource container of `PonyText` type.

## How to use

```
PonyTextCompiler <input> [options]

Arguments:
	<input>                          Input asset file path, can be any file.

Options:
	-p <path>                        Text resource data params file path.
	-o <path>                        Resource data output file path.
	-l <params_path> <output_path>   Resource load params and load output file paths.
	-d <path>                        Dep file path.
	--version                        Display version information and exit.
	--verbose                        Enable verbose output.
	--help                           Display this help message and exit.
```

Put an asset file as `<input>`, data parameters as `-p` and data output as `-o`.
You can add as many load parameters as you like but it's required to add at least one.
Every load arguments consists of load parameters and load output.
You also would like to use `-d` to make CMake or other tool to track dependencies.

## Data parameters

TOML layout:

| Field name         | Type   | Default value | Description                                              |
|:-------------------|:-------|:--------------|:---------------------------------------------------------|
| schema             | string | N/A           | Must be `PonyEngine/Resource/Text/Data/v0`.              |
| removeFinalNewLine | bool   | true          | If true, the final new line in the data will be removed. |

## Load parameters

TOML layout:

| Field name           | Type   | Default value | Description                                            |
|:---------------------|:-------|:--------------|:-------------------------------------------------------|
| schema               | string | N/A           | Must be `PonyEngine/Resource/Text/Load/v0`.            |
| directResourceAccess | bool   | false         | Corresponds to direct resouce access in the load meta. |
