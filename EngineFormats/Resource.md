# Resource format

Universal format that can represent any Pony Engine resource. Usually it's used as an intermediate build format.
Different compilers build it out of assets of different types, 
and then other build tools may build game resources out of it that will actually be used at runtime.

Has `.pr` extension - Pony Engine resource.

The format allows to put inside it multiple resources that use the same data.
It may be used to make resources that overlap by data but have different load meta.

Layout:

| Size     | Description                                                          |
|:--------:|:---------------------------------------------------------------------|
| 18       | Magic word. Must be `PonyEngineResource`.                            |
| 8        | Resource count.                                                      |
| variable | Resources. See the description below.                                |
| 8        | Resource data meta size.                                             |
| variable | Resource data meta. Its size is determined by the previous elements. |                                           
| variable | Resource data. All the other bytes till the end of file.             |

Resource layout:

| Size     | Description               |
|:--------:|:--------------------------|
| 1        | Resource ID size.         |
| [1, 255] | Resource ID.              |
| 1        | Resource type size.       |
| [1, 255] | Resource type.            |
| 8        | Resource load meta size . |
| variable | Resource load meta.       |

## Resource types

- [PonyText](PonyText.md)

