# N'importe Quoi

## On bref
This is a personnal repository aiming to collecting some software utils, including some common used algorithms and micro-architectures.

## Modules
### Common
Common module include some basic utils for test.  
Many of these files could be replaced by some well-known 3rdparty projects.  
`log.hpp` Provide a simple log interface.  
`test.hpp` Provide a simple test framework, including a handle for exceptions, and a test register.  
`time.hpp` Provide a simple util to calculate time consumption.

### Data Structure
Provide some basic data structure and implementation of some related algorithms.

### Memory Pool
`MemoryPool<T>` Provide common interface of different implementations.  
`DummyMemoryPool` Provide the most basic implementation.  
`MultiListMemoryPool` Provide a memory pool implemented with a set of freelist of fix-size
 chunks.

### Ring Buffer
`RingBuffer<DataT>` Provide a fix-sized ring buffer for a customised data type.

### Thread Pool
`ThreadPool<ReturnT>` Provide a fix-sized thread pool for any type of tasks (callable) with same type of return value.

### File Writer
`MmapFileWriter` Provide a file writer that use mmap to offer a *fast* (with no engagemnt of kernal operation) writing service.

### Pipeline
**WIP** Provide a pipeline pattern that read from a configuration file and generate a DAG to process data.

### Factory
`Factory<BaseType>` Test a mechanism of auto-registeration to a factory and instance creation with name.

### Type Traits
**WIP** Provide some common tools for type traits.

### Algorithms
**WIP** Provide some implementations of common algorithms.