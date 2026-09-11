# Resource container format

Universal format that can represent any Pony Engine resource. It's used as an intermediate build format.
Different compilers build it out of assets, 
and then other build tools may build game resources out of it that will actually be used at runtime.

It consists of two files:

1. Data - contains resource data and data meta
2. Load - contains resource load meta

Both files are binary.

One resource may have many load files but only one data file.

## Data

Layout:

| Size                | Description                                     |
|:-------------------:|:------------------------------------------------|
| 22                  | Magic word. Must be `PonyEngineResourceData`.   |
| 1                   | Resource type size.                             |
| [0, 255]            | Resource type.                                  |
| sizeof(std::size_t) | Resource data meta size.                        |
| variable            | Resource data meta.                             |
| variable            | All other bytes till the end are resource data. |

## Load

Layout:

| Size                | Description                                   |
|:-------------------:|:----------------------------------------------|
| 22                  | Magic word. Must be `PonyEngineResourceLoad`. |
| sizeof(std::size_t) | Resource load meta size.                      |
| variable            | Resource load meta.                           |
