# PonyEngine.Resource.Ext module

Resource extension API module. Provides interfaces for resource providers.

The resource service doesn't know how to load or access resource, it's just a mediator.
The resource providers know how to do that, they register resources and then provide them when requested.
It allows to add different ways of resource delivery.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application](../Application)
- [PonyEngine.Resource](../Resource)

## C\++ modules

### [PonyEngine.RawInput.Ext](Source/Main.cppm)

Main interfaces:

#### [IResourceProvider](Source/Main-IResourceProvider.cppm)

Resource provider interface. Each resource provider added to the resource service must implement it.

#### [IResourceContext](Source/Main-IResourceContext.cppm)

Interface representing the resource service context. Provides access to the application, logger and resource management functions.

#### [IResourceModuleContext](Source/Main-IResourceModuleContext.cppm)

Interface representing the resource service module context. This interface is used by modules to add resource providers. It may be accessed via module data after the resource service module initialization.

#### [IResourceRegistry](Source/Main-IResourceRegistry.cppm)

Interface that's used to register and unregister resources.
If a resource is loaded and kept alive, the resource provider must still keep the resource valid even if it unregistered the resource.

#### [ResourceParams](Source/Main-ResourceParams.cppm)

Resource parameters that are used to register a resource. The most important here is index cause later the resource will be loaded just by it for better performance.

The resource availability is very important as well. If the resource provider stated that a resource is available in some form, it must then return a correct corresponding data access:

- [ILoadableResourceData](Source/Main-ILoadableResourceData.cppm)
- [IFileResourceData](Source/Main-IFileResourceData.cppm)
- [IMemoryResourceData](Source/Main-IMemoryResourceData.cppm)

## Custom input provider

Input providers are ticked every frame, and they must update devices and input of their devices in their tick. They mustn't do it out of their ticks.

How to add a resource provider:

1. Create a class that implements `PonyEngine::Resource::IResourceProvider` interface;
2. Create an engine module and add it to the engine application;
3. Set the module initialization order after the resource service module initialization order;
4. In the module `StartUp()` get `PonyEngine::Resource::IResourceModuleContext`;
5. Add the resource provider to the resource service module context and save the returned `ResourceProviderHandle`.

The module must remove its resource provider on `ShutDown()`:

1. In the module `ShutDown()` get `PonyEngine::Resource::IResourceModuleContext`;
2. Remove the resource provider using an `ResourceProviderHandle` that was returned on adding.

Example:

```
void InputProviderModule::StartUp(Application::IModuleContext& context)
{
	IResourceModuleContext* const resourceModuleContext = context.GetData<IResourceModuleContext>();
	providerHandle = resourceModuleContext->AddProvider([](IResourceContext& resourceContext)
	{
		return std::make_shared<MyResourceProvider>(resourceContext);
	});
}

void InputProviderModule::ShutDown(Application::IModuleContext& context)
{
	IResourceModuleContext* const resourceModuleContext = context.GetData<IResourceModuleContext>();
	resourceModuleContext->RemoveProvider(providerHandle);
}
```

## Resource provider lifecycle

1. On resource service begin, `IResourceProvider.Begin()` is called on each resource provider in the order they were added;
2. Every frame, `IResourceProvider.Tick()` is called on each resource provider in the order they were added;
3. On resource service end, `IResourceProvider.End()` is called on each resource provider in the reverse order.

How to add a resource:

Resource providers get [IResourceRegistry](Source/Main-IResourceRegistry.cppm) in its `Begin()`, `End()` and `Tick()`.
It must add and remove resources only via the provided interface and only on a main thread.
