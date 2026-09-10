# PonyTools.TextCompiler tool

Compiles any file to a resource of `PonyText` type.

## How to use

```
PonyTextCompiler <input> [options]

Arguments:
	<input>          Input asset file, can be any file.

Options:
	-p <path>        Text resource params file.
	-o <path>        Resource output file.
	-d <path>        Dep file path.
	--version        Display version information and exit.
	--verbose        Enable verbose output.
	--help           Display this help message and exit.
```

Put an asset file as `<input>`, parameters as `-p` and output as `-o`.
You also would like to use `-d` to make CMake or other tool to track dependencies.

## Parameters

The parameters file is a TOML file.

Example:

```
schema = 'PonyEngine/Resource/Text/v0'

[[variant]]
id = 'Text'

[[variant]]
id = 'TextIndirect'
directResourceAccess = false

[[variant]]
id = 'TextDirect'
directResourceAccess = true
```

### Layout

Root layout:

| Field name | Type   | Description                           |
|:-----------|:-------|:--------------------------------------|
| schema     | string | Must be `PonyEngine/Resource/Text/v0` |
| variant    | array  | See its layout below.                 |

Variant layout:

| Field name           | Type   | Description                                                       |
|:---------------------|:-------|:------------------------------------------------------------------|
| id                   | string | Variant ID. Must be unique.                                       |
| directResourceAccess | bool   | Enable direct resource access. Optional, by default it's `false`. |
