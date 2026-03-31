# PonyEngine.Application.Ext module

Application extension API module. Provides interfaces to access to engine services, logging, and application context.

## C\++ modules

### [PonyEngine.Application.Ext](Source/Public/Main.cppm)

Main interfaces:

#### [IApplicationContext](Source/Public/Main-IApplicationContext.cppm)

Interface representing the engine application context. Provides access to application metadata, environment information, and the current application state.

Exposes the application logger and registered services, and allows control over the application lifecycle (e.g., stopping the application).

#### [IModule](Source/Public/Main-IModule.cppm)

Base interface for engine application modules. All application modules must implement this interface.

It has `StartUp()` and `ShutDown()` functions, which are called during the corresponding application lifecycle events.

See [Module lifecycle](#module-lifecycle) for details.

#### [IModuleContext](Source/Public/Main-IModuleContext.cppm)

Interface representing a module context. It's passed as an argument to `IModule.StartUp()` and `IModule.ShuftDown()`.

Exposes the application logger, logger module context, service module context, and allows to get and set application module data.
That data can be used by other modules which is useful when a module needs to provide a custom initialization interface.

#### [IService](Source/Public/Main-IService.cppm)

Interface representing an engine service. Services are the primary building blocks of the engine, while the application itself provides only minimal functionality.
Its main responsibility is to tick services, which define the game’s behavior.

See [Service lifecycle](#service-lifecycle) for details.

## C\++ headers

### [PonyEngine/Application/Module.h](Include/Public/PonyEngine/Application/Module.h)

Application module utilities.

| Define                                     | Description                                                                                   |
|:-------------------------------------------|:----------------------------------------------------------------------------------------------|
| `PONY_MODULE(function, moduleName, order)` | Makes an application module. See [docs below](#how-to-add-an-application-module) for details. |

## CMake functions

| Function name                | Script file                | Description                              |
|:-----------------------------|:---------------------------|:-----------------------------------------|
| `pony_validate_module_order` | [File](CMake/Module.cmake) | Validates a module order variable.       |
| `pony_validate_tick_order`   | [File](CMake/Module.cmake) | Validates a service tick order variable. |

## Custom application module

How to get an application module:

The [IApplicationContext](Source/Public/Main-IApplicationContext.cppm) has functions like `FindService<T>()` and `FindService(std::type_index_)` and their alternatives to find services.
Those functions work with public interfaces of the services.

How to add an application module:

1. Add required engine dependencies to your module target: `target_link_libraries(<MyModule> PUBLIC PonyEngine.Core PonyEngine.Application.Ext)`;
2. Make a class that inherits `PonyEngine::Application::IModule` from `PonyEngine.Application.Ext` C\++ module;
3. Make a function that returns a `PonyEngine::Application::IModule*` to an instance of your module class and takes no argument. The function must have the attribute `PONY_DLL_EXPORT` from `PonyEngine/Macro/Compiler.h` The instance must live for the lifetime of the application;
4. Include `PonyEngine/Application/Module.h` and use the macro `PONY_MODULE(<Module_Function>, <Unique_Module_Name>, <Module_Initialization_Order>)`. Module initialization order is defined by letters and follows alphabetical order;
5. Link your module target to the engine application target: `target_link_libraries(PonyEngine.Application.Impl PRIVATE <MyModule>)`.

Example of `PONY_MODULE` usage in a `.cpp` file:
```
#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Macro/Compiler.h"

import PonyEngine.Application.Ext;

namespace MyGame
{
	PONY_DLL_EXPORT PonyEngine::Application::IModule* GetGameModule()
	{
		static GameModule gameModule;
		return &gameModule;
	}
}

PONY_MODULE(MyGame::GetGameModule, MyGame, yz)
```

Make sure that your module order contains latin letters only and its first letter isn't `a` or `z`.
`PONY_MODULE` must be used in a public `.cpp` file.

## Module lifecycle

1. On the application start-up `IModule.StartUp()` is invoked on each added module. The order depends on a module initialization order passed to `PONY_MODULE` macro.
2. On the application shut-down `IModule.ShutDown()` is invoked on each added module. The order is reverse from start-up order.

The module must do nothing before its start-up and after its shut-down. Also, during start-up and shut-down phases it's recommended to access the engine API only on a main thread.

The module context passed to `IModule.StartUp()` and `IModule.ShutDown()` mustn't be used out of those functions.

## Custom service

How to add an application service:

1. Call `IModuleContext.ServiceModuleContext().AddService()` in `IModule.StartUp()`. 
The function takes a factory function `const std::function<std::shared_ptr<IService>(IApplicationContext&)>&` as an argument
and returns `ServiceHandle`.
2. Call `IModuleContext.ServiceModuleContext().RemoveService()` in `IModule.ShutDown()`.
The function takes the `ServiceHandle` that was returned by `AddService()`.

Example:

```
void ServiceModule::StartUp(Application::IModuleContext& context)
{
	serviceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
	{
		return std::make_shared<Service>(application);
	});
}

void ServiceModule::ShutDown(Application::IModuleContext& context)
{
	context.ServiceModuleContext().RemoveService(serviceHandle);
}
```

The factory function must return a correct newly created service. 
The application context it takes mustn't be shared and must be used only by the service.
The module must remove all the services it added.

### Service lifecycle

1. The service is constructed inside its module start-up. The service must be fully initialized in its constructor.
2. `IService.AddTickableServices(ITickableServiceAdder&)` is called. The service must add its tick functions via `ITickableServiceAdder.Add(ITickableService& tickable, std::int32_t tickOrder)`.
All the tick functions are sorted by their tick order. Each tick function must have a unique tick order to avoid ambiguity.
3. `IService.AddInterfaces(IServiceInterfaceAdder&)` is called. The service must add all its public interfaces via `IServiceInterfaceAdder.AddInterface()`.
Each interface type must be unique. Those interfaces will be available via `IApplicationContext.FindService`.
4. After all the module start-up functions are called, the `IService.Begin()` is called on each service in the same order they were added.
5. Each frame `ITickableService.Tick` is called in their custom order.
6. Before the module shut-down functions are called, the `IService.End()` is called on each service in the reverse order.
7. The service is destructed inside its module shut-down.

## Custom logger

How to add a custom logger:

1. Call `IModuleContext.LoggerModuleContext().SetLogger()` in `IModule.StartUp()`.
The function takes a factory function `const std::function<std::shared_ptr<Log::ILogger>(ILoggerContext&)>&` as an argument
and returns `LoggerHandle`.
2. Call `IModuleContext.LoggerModuleContext().UnsetLogger()` in `IModule.ShutDown()`.
The function takes the `LoggerHandle` that was return be `SetLogger()`.

Example:
```
void LoggerModule::StartUp(Application::IModuleContext& context)
{
	loggerHandle = context.LoggerModuleContext().SetLogger([&](Application::ILoggerContext& loggerContext)
	{
		return std::make_shared<Logger>(loggerContext);
	});
}

void LoggerModule::ShutDown(Application::IModuleContext& context)
{
	context.LoggerModuleContext().UnsetLogger(loggerHandle);
}
```

The factory function must return a correct newly created logger.
The logger context it takes mustn't be shared and must be used only by the logger.
The module must remove its logger it added.
Only one custom logger may be set at a time.
If no custom logger is set, the application uses a default logger.

The default logger just writes to a standard and a platform consoles.

### Logger lifecycle

The logger doesn't have a special lifecycle. It's constructed, added to the application, removed from the application and destructed.

When the logger is added to the application, it will receive log calls.

The logger context isn't `IApplicationContext` but `ILoggerContext`. The logger context has functions to get `IApplicationContext` and log to the standard and platform consoles.
