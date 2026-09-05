# PonyEngine.Job feature module

Job API module. Provides interfaces for a job service.

The job service is a simple way to utilize multi-threaded CPUs.
Users create tasks with optional dependencies, and the job service will automatically distribute them among threads.

Adds `PonyEngine.Job` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Job](Source/Job.cppm)

Main sub-modules:

#### [IJobService](Source/Job-IJobService.cppm)

Job service interface.

#### [JobHandle](Source/Job-JobHandle.cppm)

Handle of a scheduled job.
