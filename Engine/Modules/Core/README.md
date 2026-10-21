# PonyEngine.Core feature module

Core utilities module.

Adds `PonyEngine.Core` target as a static library.

## C\++ modules

### [PonyEngine.Async](Source/Async.cppm)

Utilities for async operations.

### [PonyEngine.Chrono](Source/Chrono.cppm)

Utilities for `std::chrono`.

Utilities:
- [Conversion](Source/Chrono-Conversion.cppm) - chrono conversion utilities.

### [PonyEngine.Container](Source/Container.cppm)

Utilities for standard containers.

Allocators:
- [AlignedAllocator](Source/Container-AlignedAllocator.cppm) - aligned allocator.

### [PonyEngine.FileSystem](Source/FileSystem.cppm)

Utilities for file system.

Utilities:
- [DynamicLibrary](Source/FileSystem-DynamicLibrary.cppm) - Dynamic library raii wrapper.

The module requires a platform specific implementation of these functions:

- Library.cppm
```
	/// @brief Loads a library by the path.
	/// @param path Library path.
	/// @return Library.
	[[nodiscard("Must be used")]]
	void* AcquireLibrary(const std::filesystem::path& path);
	/// @brief Frees the library.
	/// @param library Library pointer.
	void ReleaseLibrary(void* library);
	/// @brief Gets a library address by the name.
	/// @param library Library. Must be valid.
	/// @param name Name.
	/// @return Library address.
	[[nodiscard("Pure function")]]
	void* GetAddress(void* library, const char* name);
```

### [PonyEngine.Format](Source/Format.cppm)

Utilities for std::format.

Utilities:
- [Optional](Source/Format-Optional.cppm) - std::optional formatter.

### [PonyEngine.Hash](Source/Hash.cppm)

Utilities for calculating hashes.

Hash algorithms:
- [FNV-1a](Source/Hash-FNV1a.cppm)

### [PonyEngine.Math](Source/Math.cppm)

Math utilities.

The engine uses a left-handed coordinate system where X is right, Y is up, and Z is forward. 
The rotation order is ZXY (roll-pitch-yaw). The matrices are column-major.

Basic classes:
- [Vector](Source/Math-Vector.cppm)
- [Matrix](Source/Math-Matrix.cppm)
- [Quaternion](Source/Math-Quaternion.cppm)

Utilities:
- [Common](Source/Math-Common.cppm) - common math utilities;
- [Transformations](Source/Math-Transformations.cppm) - transformation utilities: functions for transformation matrices, rotation conversions, etc.

Shapes:
- [Ball](Source/Math-Ball.cppm)
- [Box](Source/Math-Box.cppm)
- [CornerBox](Source/Math-CornerBox.cppm)
- [Flat](Source/Math-Flat.cppm)
- [OrientedBox](Source/Math-OrientedBox.cppm)
- [Ray](Source/Math-Ray.cppm)

Shape utilities:
- [Bounds](Source/Math-Bounds.cppm) - utilities to calculate bounding shapes;
- [Insides](Source/Math-Insides.cppm) - utilities to find out if a shape is fully inside another shape;
- [Intersections](Source/Math-Intersections.cppm) - utilities to find out if two shapes are intersecting.

Special:
- [Color](Source/Math-Color.cppm) - class to work with different color representations;
- [Transform](Source/Math-Transform.cppm) - class that represents Transform2D and Transform3D.

### [PonyEngine.Meta](Source/Meta.cppm)

Utilities for describing different meta info.

Classes:
- [Version](Source/Meta-Version.cppm) - class that represents a standard 4-value version.

### [PonyEngine.Memory](Source/Memory.cppm)

Utilities for memory management.

Classes:
- [Arena](Source/Memory-Arena.cppm) - arena memory allocator;
- [Utility](Source/Memory-Utility.cppm) - utilities for memory management.

### [PonyEngine.Utilty](Source/Utility.cppm)

Basic utilities.

Utilities:
- [Concepts](Source/Utility-Concepts.cppm) - basic concepts;
- [Overload](Source/Utility-Overload.cppm) - overload pattern implementation.

## C\++ headers

### [PonyEngine/Macro/Compiler.h](Include/Public/PonyEngine/Macro/Compiler.h)

Compiler utilities. They must be implemented by a modification module that adds a compiler support.

| Define                   | Description                 |
|:-------------------------|:----------------------------|
| `PONY_DLL_EXPORT`        | Sets `dllexport` attribute. |

### [PonyEngine/Macro/Text.h](Include/Public/PonyEngine/Macro/Text.h)

Macro text utilities.

| Define                     | Description                                                   |
|:---------------------------|:--------------------------------------------------------------|
| `PONY_STRINGIFY(x)`        | Returns a C-style string that contains `x`.                   |
| `PONY_STRINGIFY_VALUE(x)`  | Returns a C-style string that contains a value `x` variable.  |
| `PONY_CONCAT(a, b)`        | Returns a C-style string that contains `ab`.                  |
| `PONY_CONCAT_VALUES(a, b)` | Returns a C-style string that contains values of `a` and `b`. |

### [PonyEngine/Utility/Body.h](Include/Public/PonyEngine/Utility/Body.h)

Object body utilities.

| Define                                    | Description                                                                                                                                                       |
|:------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `PONY_INTERFACE_BODY(interfaceName)`      | Adds default constructors, destructor and assignment operators for an interface and makes next members public. Must be used inside a class named `interfaceName`. |
| `PONY_NON_CONSTRUCTIBLE_BODY(objectName)` | Makes an object non-constructible. Must be used inside a class named `objectName`.                                                                                |

### [PonyEngine/Utility/Enum.h](Include/Public/PonyEngine/Utility/Enum.h)

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
