# PonyEngine.Application.Impl module

Application implementation module. Implements [PonyEngine.Application.Ext](../Application.Ext).

The module also has `main()` function.

The module requires a platform specific implementation.

### CMake variables

These variables are used to configure the build of the module:

| Variable name                | Default value | Description                                             |
|:-----------------------------|:-------------:|:--------------------------------------------------------|
| `PONY_ENGINE_DEFAULT_LOGGER` | ON            | Enable default logger. It logs everything to a console. |
| `PONY_ENGINE_CONSOLE_LOG`    | ON            | Enable standard c++ console.                            |
