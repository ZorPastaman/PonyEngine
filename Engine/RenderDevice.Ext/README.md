# PonyEngine.RenderDevice.Ext module

Render device extension API module. It provides interfaces for backend implementations.
The render device service doesn't have a support for any backend by default. They must be added via separate modules.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.RenderDevice](../RenderDevice)

## C\++ modules

### [PonyEngine.RenderDevice.Ext](Source/Public/Main.cppm)

Main interfaces:

#### [IBackend](Source/Public/Main-IBackend.cppm)

Backend interface. Each backend must implement it.

#### [IRenderDeviceContext](Source/Public/Main-IRenderDeviceContext.cppm)

Interface representing the render device service context. Provides access to the application context, logger and other functions.

#### [IRenderDeviceModuleContext](Source/Public/Main-IRenderDeviceModuleContext.cppm)

Interface representing the render device service module context. This interface is used by modules to add backends. It may be accessed via module data after the render device service module initialization.

## Custom render backend

Backends can be either active or inactive, but only one backend may be active at any given time. The render device service manages this by calling `Activate()` and `Deactivate()`.
When inactive, a backend should keep its state as minimal as possible. Upon `Activate()`, it must fully initialize itself so that all other functions can be safely used.
While inactive, a backend must not be used, except for querying basic information about its render API.

How to add a render backend:

1. Create a class that implements `PonyEngine::RenderDevice::IBackend` interface;
2. Create an engine module and add it to the engine application;
3. Set the module initialization order after the render device service module initialization order;
4. In the module `StartUp()` get `PonyEngine::RenderDevice::IRenderDeviceModuleContext`;
5. Add the backend to the render device service module context and save the returned `BackendHandle`.

The module must remove its backend on `ShutDown()`:

1. In the module `ShutDown()` get `PonyEngine::RenderDevice::IRenderDeviceModuleContext`;
2. Remove the backend using an `BackendHandle` that was returned on adding.

Example:

```
void InputProviderModule::StartUp(Application::IModuleContext& context)
{
	IRenderDeviceModuleContext* renderDeviceModuleContext = context.GetData<IRenderDeviceModuleContext>();
	backendHandle = renderDeviceModuleContext->AddBackend([](IRenderDeviceContext& renderDevice)
	{
		return std::make_shared<Backend>(renderDevice);
	});
}

void InputProviderModule::ShutDown(Application::IModuleContext& context)
{
	IRenderDeviceModuleContext* renderDeviceModuleContext = context.GetData<IRenderDeviceModuleContext>();
	rawInputModuleContext->RemoveSubLogger(backendHandle);
}
```
