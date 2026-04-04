# PonyEngine.Shader module

Shader utility module. Provides utilities for both C\++ and HLSL.
Includes classes and structs shared between the two languages, with implementations on both sides.

## Modules

On C\++ side all the utilities are contained in [PonyEngine.Shader](Source/Public/Main.cppm) module.
On HLSL side all the utilities are contained in different .hlsli file in [ShaderInclude](ShaderInclude).

The module sets a path to the HLSL include folder in the CMake target property `PONY_ENGINE_SHADER_INCLUDE`.
You can access it via `get_target_property(<MyProperty> PonyEngine.Shader PONY_ENGINE_SHADER_INCLUDE)`.
Add it to a list of includes to compile a shader.

## Utilities

### C\++: [Bool](Source/Public/Main-Bool.cppm); HLSL: -

4-byte bool. It may be useful for structs that are synced with HLSL 'cause it has 4-byte bool.

### C\++: -; HLSL: [PonyEngine/Core.hlsli](ShaderInclude/PonyEngine/Core.hlsli)

Contains core shader utilities.

#### Register utilities:

Contains defines `PONY_CBV_REGISTER(set, index)`, `PONY_SRV_REGISTER(set, index)`, `PONY_UAV_REGISTER(set, index)` and `PONY_SAMPLER_REGISTER(set, index)`.
These defines are used to declare registers in HLSL. For example, `StructuredBuffer<uint> VertexIndices : PONY_SRV_REGISTER(1, 2);`.
It's used instead of a classic hlsl `register(t2, space1)` because the shader must be compatible with different render APIs that have a different binding system.
That's why the engine uses those defines where you set a register type, descriptor set index and an object index in that set. You can't reuse the same set index and object index for different type.

### C\++: [Meshlet](Source/Public/Main-Meshlet.cppm); HLSL: [PonyEngine/Meshlet.hlsli](ShaderInclude/PonyEngine/Meshlet.hlsli)

Meshlet implementation. The meshlet is just a simple class that contains 4-byte vertex offset, 4-byte primitive offset, 1-byte vertex count and 1-byte primitive count.
The size of both C\++ and HLSL implementations is 12 bytes. 

A shader is expected to have such a structure:

```
StructuredBuffer<Pony_Meshlet> Meshlets : PONY_SRV_REGISTER(0, 0);
StructuredBuffer<uint> VertexIndices : PONY_SRV_REGISTER(0, 1);
StructuredBuffer<uint> Indices : PONY_SRV_REGISTER(0, 2);

StructuredBuffer<float3> Positions : PONY_SRV_REGISTER(1, 0);
StructuredBuffer<float4> Colors : PONY_SRV_REGISTER(1, 1);
// Other vertex data.
```

With vertex offset and count, `Pony_Meshlet` points to the `VertexIndices` that is an index array that points to different vertex data.
With primitive offset and count, `Pony_Meshlet` points to the `Indices` that contains meshlet indices that will be returned by a mesh shader.

Because meshlets can't contain more than 256 vertices, indices are expected to be 1-byte size. But HLSL natively works only with 4-byte values.
That's why indices are expected to be packed as 1-byte array into 4-byte array.
The [PonyEngine/Meshlet.hlsli](ShaderInclude/PonyEngine/Meshlet.hlsli) contains functions that help to unpack primitives:
`uint UnpackPoint()`, `uint2 UnpackLine()`, `uint3 UnpackTriangle()` and `uint4 UnpackQuad()`.
All those functions are templates and accept any array-like parameter and primitive index. Exactly primitive index, you don't pass a first index of a primitive but a triangle index, for example.
Functions have a `isFlipped` parameter that determines if a primitive is flipped. It can be used for a correct rendering with a negative scale, for example.
