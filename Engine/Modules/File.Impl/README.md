# PonyEngine.File.Impl feature module

File implementation module.

Adds `PonyEngine.File.Impl` target as a static library.

The module provides basic implementation classes but requires a platform specific implementation.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.File](../File)

## For Pony Engine developers

Main sub-modules:

- [FileInfo](Source/File-FileInfo.cppm) - file info holder;
- [Request](Source/File-Request.cppm) - request holder;
- [ReadRequest](Source/File-ReadRequest.cppm) - read request holder;
- [WriteRequest](Source/File-WriteRequest.cppm) - write request holder;
- [RequestVariant](Source/File-RequestVariant.cppm) - variant of read/write request holder.
