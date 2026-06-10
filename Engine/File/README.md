# PonyEngine.File module

File API module. Provides interfaces for a file service.

The file service is a simple way to utilize modern SSDs with totally async read/write operations.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.File](Source/Main.cppm)

Main sub-modules:

#### [IFile](Source/Main-IFile.cppm)

File interface. Creates requests to a file.

#### [IFileService](Source/Main-IFileService.cppm)

File service interface. Opens files.
