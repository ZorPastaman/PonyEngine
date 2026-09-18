# PonyEngine.Resource module feature module

Resource API module. Provides interfaces for a resource service.

Provides an access to game resources. The resource can be any type. One resource may be of many types at the same time.
Every resource has its unique ID, and they're loaded by that ID. Only async loads are supported.

Adds `PonyEngine.Resource` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Resource](Source/Resource.cppm)

#### [IResourceService](Source/Resource-IResourceService.cppm)

Resource service public interface.

#### [ResourceID](Source/Resource-ResourceID.cppm)

Resource ID. It's a hash value of a resource ID string representation. The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

#### [IResourceRequest](Source/Resource-IResourceRequest.cppm)

Resource request. It's a result of load function. When the request is finished, you can get your resource.
