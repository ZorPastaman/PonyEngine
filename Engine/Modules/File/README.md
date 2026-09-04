# PonyEngine.File feature module

File API module. Provides interfaces for a file service.

The file service is a simple way to utilize modern SSDs with totally async read/write operations.

Adds `PonyEngine.File` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.File](Source/File.cppm)

Main sub-modules:

#### [IFile](Source/File-IFile.cppm)

File interface. Creates requests to a file.

#### [IFileService](Source/File-IFileService.cppm)

File service interface. Opens files.
