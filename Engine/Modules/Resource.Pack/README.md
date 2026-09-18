# PonyEngine.Resource.Pack feature module

Resource module extension that provides resources in packs.

Every pack consists of two files:

1. Manifest (.prpm) - contains meta info;
2. Data (.prpd) - contains actual resource data.

Both files must have the same name and be in the same folder. For more info, refer to the [EngineFormats](../../../EngineFormats).

Packs may be loaded from files and from memory.

Adds `PonyEngine.Resource.Pack` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)

## C\++ modules

### [PonyEngine.Resource.Pack](Source/Pack.cppm)

#### [IPackService](Source/Pack-IPackService.cppm)

Pack service. Mounts and unmounts packs. Both operations are done in async manner.
