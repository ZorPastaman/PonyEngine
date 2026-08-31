# PonyEngine.Resource.Pack module

Resource module extension that provides resources in packs.

Every pack consists of two files:

1. Manifest - contains meta info;
2. Data - contains actual resource data.

Packs may be loaded from files and from memory.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)

## C\++ modules

### [PonyEngine.Resource.Pack](Source/Main.cppm)

#### [IPackService](Source/Main-IPackService.cppm)

Pack service. Mounts and unmounts packs. Both operations are done in async manner.
