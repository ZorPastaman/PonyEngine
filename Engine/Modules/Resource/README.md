# PonyEngine.Resource module

Resource API module. Provides interfaces for a resource service.

Provides an access to game resources. It provides only raw byte data of the resources. 
Parsing and creating game objects is on more high-level modules.

Any resource can be accessible in 3 forms:

- Loadable resource - an abstract access that loads bytes into a provided span.
- File - a direct file reference.
- Memory - a direct memory reference.

A resource can be accessed in at least one of these forms.
If it's available in two or more forms, its data guaranteed to be the same in all the forms.

Every resource has its unique ID, and they're loaded by that ID.
Every resource has a type as well. The type is just a string (hashed). 
The resource service doesn't use it for anything. But it can be used by other modules for validation.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Resource](Source/Main.cppm)

Main sub-modules:

#### [IResourceService](Source/Main-IResourceService.cppm)

Resource service public interface.

#### [ResourceID](Source/Main-ResourceID.cppm)

Resource ID. It's a hash value of a resource ID string representation. The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

#### [ResourceType](Source/Main-ResourceType.cppm)

Resource type. It's a hash value of a resource type string representation. The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

#### [ResourceAvailability](Source/Main-ResourceAvailability.cppm)

Resource availability enum that represents different access forms.

#### [ILoadableResource](Source/Main-ILoadableResource.cppm)

Loadable resource interface.

#### [IFileResource](Source/Main-IFileResource.cppm)

File resource interface.

#### [IMemoryResource](Source/Main-IMemoryResource.cppm)

Memory resource interface.
