# Resource container format

Universal format that can represent any Pony Engine resource data. It's used as an intermediate build format.
Different compilers build it out of assets, 
and then other build tools may build game resources out of it that will actually be used at runtime.

It has several variants that allows to reuse the same data in different ways.

Layout:

| Size                | Description                                              |
|:-------------------:|:---------------------------------------------------------|
| 27                  | Magic word. Must be `PonyEngineResourceContainer`.       |
| sizeof(std::size_t) | Variant count.                                           |
| variable            | Variants. See the description below.                     |
| variable            | Resource data. All the other bytes till the end of file. |

Variant layout:

| Size                | Description              |
|:-------------------:|:-------------------------|
| 1                   | Variant ID size.         |
| [0, 255]            | Variant ID.              |
| 1                   | Resource type size.      |
| [0, 255]            | Resource type.           |
| sizeof(std::size_t) | Resource data meta size. |
| variable            | Resource data meta.      |
| sizeof(std::size_t) | Resource load meta size. |
| variable            | Resource load meta.      |
