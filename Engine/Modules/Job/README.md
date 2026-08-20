# PonyEngine.Job module

Job API module. Provides interfaces for a job service.

The job service is a simple way to utilize multi-threaded CPUs.
Users create tasks with optional dependencies, and the job service will automatically distribute them among threads.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Job](Source/Main.cppm)

Main sub-modules:

#### [IJobService](Source/Main-IJobService.cppm)

Job service interface.

#### [JobHandle](Source/Main-JobHandle.cppm)

Handle of a scheduled job.
