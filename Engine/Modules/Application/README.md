# PonyEngine.Application module

Application API module. Provides interfaces to access main engine info, to register interfaces and tickables.
It also controls the engine initialization and main loop.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Application](Source/Main.cppm)

#### [IApplication](Source/Main-IApplication.cppm)

Interface representing the engine application. Provides access to application metadata, environment information, and the current application state.

Exposes the registered interfaces, and allows control over the application lifecycle (e.g., stopping the application).

#### [IModule](Source/Main-IModule.cppm)

Base interface for engine application modules. All application modules must implement this interface.

It has `StartUp()` and `ShutDown()` functions, which are called during the corresponding application lifecycle events.

See [Module lifecycle](#module-lifecycle) for details.

#### [IModuleContext](Source/Main-IModuleContext.cppm)

Interface representing a module context. It's passed as an argument to `IModule.StartUp()` and `IModule.ShuftDown()`.

Exposes functions to register interfaces and tickables.

#### [ITickable](Source/Main-ITickable.cppm)

Tickable interface. A tickable is an object that reacts to the application main loop: `Begin()`, `End()` and `Tick()` functions.

## C\++ headers

### [PonyEngine/Application/Module.h](Include/Public/PonyEngine/Application/Module.h)

Application module utilities.

| Define                                                         | Description                                                                                                                                         |
|:---------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------|
| `PONY_EARLY_MODULE(function, moduleName, order)`               | Makes an application module with an early registration. It's a group for log modules. The application tries to find a log service after this group. |
| `PONY_NORMAL_MODULE(function, moduleName, order)`              | Makes an application module with a normal registration. It's a group for engine modules.                                                            |
| `PONY_LATE_MODULE(function, moduleName, order)`                | Makes an application module with a late registration. It's a group for game modules.                                                                |
| `PONY_LOG_MODULE(function, moduleName, order)`                 | Synonym to `PONY_EARLY_MODULE(function, moduleName, order)`.                                                                                        |
| `PONY_ENGINE_MODULE(function, moduleName, order)`              | Synonym to `PONY_NORMAL_MODULE(function, moduleName, order)`.                                                                                       |
| `PONY_PROJECT_MODULE(function, moduleName, order)`             | Synonym to `PONY_LATE_MODULE(function, moduleName, order)`.                                                                                         |

## CMake functions

| Function name                | Script file                | Description                              |
|:-----------------------------|:---------------------------|:-----------------------------------------|
| `pony_validate_module_order` | [File](CMake/Module.cmake) | Validates a module order variable.       |
| `pony_validate_tick_order`   | [File](CMake/Module.cmake) | Validates a service tick order variable. |

## Custom application module

How to add an application module:

1. Make a class that inherits `PonyEngine::Application::IModule`;
2. Make a function that returns an `std::shared_ptr<PonyEngine::Application::IModule>` to an instance of your module class and takes no argument. The function must have the attribute `PONY_DLL_EXPORT` from `PonyEngine/Macro/Compiler.h`;
3. Include `PonyEngine/Application/Module.h` and use the macro `PONY_<GROUP>_MODULE(<Module_Function>, <Unique_Module_Name>, <Module_Initialization_Order>)` in a public code file. Module initialization order is defined by letters and follows alphabetical order;
4. Link your module target to the engine application target. The default implementation is [PonyEngine.Application.Impl](../Application.Impl).

Example of `PONY_PROJECT_MODULE` usage in a `.cpp` file:
```
#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Macro/Compiler.h"

import std;

import PonyEngine.Application;

namespace MyGame
{
	PONY_DLL_EXPORT std::shared_ptr<PonyEngine::Application::IModule> CreateGameModule()
	{
		return std::make_shared<GameModule>();
	}
}

PONY_PROJECT_MODULE(MyGame::CreateGameModule, MyGame, yz)
```

Make sure that your module order contains small latin letters only and its first letter isn't `a` or `z`.
`PONY_<GROUP>_MODULE` must be used in a public `.cpp` file.

## Module lifecycle

1. On the application start-up `IModule.StartUp()` is invoked on each added module. The order depends on a module initialization order passed to `PONY_<GROUP>_MODULE` macro and on a chosen group.
2. On the application shut-down `IModule.ShutDown()` is invoked on each added module. The order is reverse from start-up order.

The module must do nothing with the application before its start-up and after its shut-down. Also, during start-up and shut-down phases the application and module context are single-threaded and their API can be used only on a main thread.

The module context passed to `IModule.StartUp()` and `IModule.ShutDown()` mustn't be used out of those functions.

## Tickables

Tickables are object that get main loop callbacks. They have 3 main functions:

- Begin() - is called before a first tick.
- End() - is called after a last tick.
- Tick() - is called each tick.

Tickables must be registered during start-up in modules. Call `IModuleContext.AddTickable()`. You also pass a begin and tick orders. The end order is always a reverse to begin.
All the added tickables must be removed during shut-down via `IModuleContext.RemoveTickable()`.

## Interfaces

Interfaces are just pointers to some classes. Modules may provide different services to other modules via them.

Add interfaces via `IModuleContext.AddInterface()` during start-up and remove them via `IModuleContext.RemoveInterface()` during shut-down.
To find other interfaces use `IApplication.FindInterface()` or `IApplication.GetInterface()`.
