# PonyEngine.Resource.Ext module

Resource extension API module. Provides interfaces for resource providers.

The resource service doesn't know how to load or access resource, it's just a mediator.
The resource providers know how to do that, they register resources and then provide them when requested.
It allows to add different ways of resource delivery.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Resource](../Resource)

## C\++ modules

### [PonyEngine.Resource.Ext](Source/Main.cppm)

#### [IResourceHub](Source/Main-IResourceHub.cppm)

Central service where resource collections and loaders are added to.

#### [IResourceProvider](Source/Main-IResourceProvider.cppm)

Provides resource data. It submits resources and tells how it's ready to provide an access to them.

#### [IResourceLoader](Source/Main-IResourceLoader.cppm)

Loads resources. It knows how to create runtime resources out of raw data from resource providers.

#### [ILoadableDataAccess](Source/Main-ILoadableDataAccess.cppm)

The most abstract data access that lets load data from an unknown source in async manner.

#### [IFileDataAccess](Source/Main-IFileDataAccess.cppm)

Data access that provides direct access to a resource data in a file.

#### [IMemoryDataAccess](Source/Main-IMemoryDataAccess.cppm)

Data access that provides direct access to a resource data in the memory.
