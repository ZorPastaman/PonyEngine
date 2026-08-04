# PonyEngine.Job.Impl module

Job implementation module.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Job](../Job)
- [PonyEngine.Log](../Log)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                           | Default value | Description                                                                                       |
|:----------------------------------------|:-------------:|:--------------------------------------------------------------------------------------------------|
| `PONY_ENGINE_JOB_ORDER`                 | p             | PonyEngine.Job.Impl module initialization order.                                                  |
| `PONY_ENGINE_JOB_RESERVED_THREAD_COUNT` | 3             | PonyEngine.Job.Impl service reserved thread count. Those are threads reserved for other purposes. |
| `PONY_ENGINE_JOB_MIN_THREAD_COUNT`      | 2             | PonyEngine.Job.Impl service minimal thread count.                                                 |
| `PONY_ENGINE_JOB_POOL_SIZE`             | 64            | PonyEngine.Job.Impl pool size of jobs per thread.                                                 |
| `PONY_ENGINE_JOB_THREAD_ROLE`           | Worker        | PonyEngine.Job.Impl worker thread role.                                                           |

## For Pony Engine developers

Main sub-modules:

- [Job](Source/Main-Job.cppm) - job implementation;
- [JobPool](Source/Main-JobPool.cppm) - job pool;
- [Worker](Source/Main-Worker.cppm) - worker thread implementation;
- [JobService](Source/Main-JobService.cppm) - job service implementation;
- [JobServiceModule](Source/Main-JobServiceModule.cppm) - job service implementation module.
