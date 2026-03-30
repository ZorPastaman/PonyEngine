# PonyEngine.Core module

Core utilities module.

The engine uses a left-handed coordinate system where X is right, Y is up, and Z is forward. The rotation order is ZXY (roll-pitch-yaw). The matrices are column-major.

The module requires a compiler specific implementation.

## C\++ modules

### [PonyEngine.Hash](Source/Public/Hash.cppm)

Utilities for calculating hashes.

Hash algorithms:
- [FNV-1a](Source/Public/Hash-FNV1a.cppm)

### [PonyEngine.Math](Source/Public/Math.cppm)

Math utilities.

Basic classes:
- [Vector](Source/Public/Math-Vector.cppm)
- [Matrix](Source/Public/Math-Matrix.cppm)
- [Quaternion](Source/Public/Math-Quaternion.cppm)

Utilities:
- [Common](Source/Public/Math-Common.cppm) - common math utilities;
- [Transformations](Source/Public/Math-Transformations.cppm) - transformation utilities: functions for transformation matrices, rotation conversions, etc.

Shapes:
- [Ball](Source/Public/Math-Ball.cppm)
- [Box](Source/Public/Math-Box.cppm)
- [CornerBox](Source/Public/Math-CornerBox.cppm)
- [Flat](Source/Public/Math-Flat.cppm)
- [OrientedBox](Source/Public/Math-OrientedBox.cppm)
- [Ray](Source/Public/Math-Ray.cppm)

Shape utilities:
- [Bounds](Source/Public/Math-Bounds.cppm) - utilities to calculate bounding shapes;
- [Insides](Source/Public/Math-Insides.cppm) - utilities to find out if a shape is fully inside another shape;
- [Intersections](Source/Public/Math-Intersections.cppm) - utilities to find out if two shapes are intersecting.

Special:
- [Color](Source/Public/Math-Color.cppm) - class to work with different color representations;
- [Transform](Source/Public/Math-Transform.cppm) - class that represents Transform2D and Transform3D.

### [PonyEngine.Meta](Source/Public/Meta.cppm)

Utilities for describing different meta info.

Classes:
- [Version](Source/Public/Meta-Version.cppm) - class that represents a standard 4-value version.

### [PonyEngine.Memory](Source/Public/Memory.cppm)

Utilities for memory management.

Classes:
- [Arena](Source/Public/Memory-Arena.cppm) - arena memory allocator;
- [Pool](Source/Public/Memory-Pool.cppm) - object pool.

### [PonyEngine.Serialization](Source/Public/Serialization.cppm)

Utilities for serialization/deserialization in binary and text formats.

Utilities:
- [Basic](Source/Public/Serialization-Basic.cppm) - utilities for serialization/deserialization of unique values;
- [Array](Source/Public/Serialization-Array.cppm) - utilities for serialization/deserialization of value arrays.

### [PonyEngine.Type](Source/Public/Type.cppm)

Utilities for C\++ type system.

Utilities:
- [Common](Source/Public/Type-Common.cppm) - common type utlities: basic type concepts;
- [Limits](Source/Public/Type-Limits.cppm) - extension for `std::numeric_limits`;
- [Variant](Source/Public/Type-Variant.cppm) - utilities for `std::variant`.

## C\++ headers

### [PonyEngine/Macro/Compiler.h](Include/Public/PonyEngine/Macro/Compiler.h)

Compiler utilities.

| Define                   | Description                                          |
|:-------------------------|:-----------------------------------------------------|
| `PONY_DLL_EXPORT`        | Sets `dllexport` attribute if `PONY_DLL` is defined. |
| `PONY_PRESERVE(symbol)`  | Prevents a compiler from removing the symbol.        |
| `PONY_SECTION(name)`     | Declares a section with the name.                    |
| `PONY_ALLOCATE(segment)` | Allocates the segment.                               |

### [PonyEngine/Macro/Text.h](Include/Public/PonyEngine/Macro/Text.h)

Text utilities.

| Define                     | Description                                                   |
|:---------------------------|:--------------------------------------------------------------|
| `PONY_STRINGIFY(x)`        | Returns a C-style string that contains `x`.                   |
| `PONY_STRINGIFY_VALUE(x)`  | Returns a C-style string that contains a value `x` variable.  |
| `PONY_CONCAT(a, b)`        | Returns a C-style string that contains `ab`.                  |
| `PONY_CONCAT_VALUES(a, b)` | Returns a C-style string that contains values of `a` and `b`. |

### [PonyEngine/Object/Body.h](Include/Public/PonyEngine/Object/Body.h)

Object body utilities.

| Define                                    | Description                                                                                                                                                       |
|:------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `PONY_INTERFACE_BODY(interfaceName)`      | Adds default constructors, destructor and assignment operators for an interface and makes next members public. Must be used inside a class named `interfaceName`. |
| `PONY_NON_CONSTRUCTIBLE_BODY(objectName)` | Makes an object non-constructible. Must be used inside a class named `objectName`.                                                                                |

### [PonyEngine/Type/Enum.h](Include/Public/PonyEngine/Type/Enum.h)

Enum utilities.

| Define                                                        | Description                                                                                                                       |
|:--------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------|
| `PONY_ENUM_VALUE_FORMATTER(Value, ValueNames)`                | Creates a formatter for a value enum.                                                                                             |
| `PONY_ENUM_MASK_FORMATTER(Mask, MaskNames)`                   | Creates a formatter for a mask enum.                                                                                              |
| `PONY_ENUM_MASK_OPERATORS(Mask)`                              | Creates bit-wise operators for a mask enum.                                                                                       |
| `PONY_ENUM_MASK_CHECKS(Mask)`                                 | Creates mask check functions like `All()`, `Any()` and `None()`.                                                                  |
| `PONY_ENUM_VALUE_MASK`                                        | Creates helper functions for a value-mask enum pair. Each value of the value enum must correspond to a bit-flag of the mask enum. |
| `PONY_ENUM_MASK_FEATURES(Mask)`                               | Shortcut for `PONY_ENUM_MASK_OPERATORS(Mask) PONY_ENUM_MASK_CHECKS(Mask)`.                                                        |
| `PONY_ENUM_VALUE_MASK_FEATURES(Value, Mask)`                  | Shortcut for `PONY_ENUM_MASK_FEATURES(Mask) PONY_ENUM_VALUE_MASK(Value, Mask)`.                                                   |
| `PONY_ENUM_VALUE_MASK_FORMATTER(Value, Mask, ValueMaskNames)` | Shortcut for `PONY_ENUM_VALUE_FORMATTER(Value, ValueMaskNames) PONY_ENUM_MASK_FORMATTER(Mask, ValueMaskNames)`.                   |

## CMake functions

| Function name                    | Script file                 | Description                                     |
|:---------------------------------|:----------------------------|:------------------------------------------------|
| `pony_make_module_group modules` | [File](CMake/Target.cmake)  | Makes a shared library out of static libraries. |

## Custom compiler

The module requires a compiler specific implementation. For that, some defines must be implemented by a compiler module.

1. The define `PONY_COMPILER_INCLUDE` must be set and contain a valid path a compiler implementation header file.
2. The header file must contain and implement these defines:

| Define                        | Description                                   |
|:------------------------------|:----------------------------------------------|
| `PONY_DLL_EXPORT_IMPL`        | Sets `dllexport` attribute.                   |
| `PONY_PRESERVE_IMPL(symbol)`  | Prevents a compiler from removing the symbol. |
| `PONY_SECTION_IMPL(name)`     | Declares a section with the name.             |
| `PONY_ALLOCATE_IMPL(segment)` | Allocates the segment.                        |
