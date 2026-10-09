# PonyEngine.Resource.World feature module

Resource module extension that adds support of world resources.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)
- [PonyEngine.World](../World)

## C\++ modules

### [PonyEngine.Resource.World](Source/World.cppm)

#### [IWorldDefinitionLoader](Source/World-IWorldDefinitionLoader.cppm)

World definition loader. It knows how to read the serialized data and parses it.
But it doesn't know how to parse component and object types. For this separate component and object deserializes must be registered.

#### [IComponentDeserializer / IInlineComponentDeserializer](Source/World-IComponentDeserializer.cppm)

Component deserializer. It's registered for each type. The usual deserializer makes a request and executes in async manner,
while the inline deserializer executes immediately.

#### [IObjectDeserializer / IInlineObjectDeserializer](Source/World-IObjectDeserializer.cppm)

Object deserializer. It's registered for each type. The usual deserializer makes a request and executes in async manner,
while the inline deserializer executes immediately.
