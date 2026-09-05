# PonyEngine.World module

World service API module.

The service provides world objects that allow to manage game data in ECS style.
It's pure data management (entities and components). The service doesn't provide anything for systems -
they can be implemented as needed for a game project.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.World](Source/Main.cppm)

#### [Entity](Source/Main-Entity.cppm)

Entity struct. It's just an ID and a generation.

The ID is the main part of an entity. Its generation is used for validation to ensure that an entity isn't used after its death. 
It allows to reuse the same ID for another entity.

#### [Component](Source/Main-Component.cppm)

Component concept. It requires a component to be a pod-like struct.

#### [ObjectHandle](Source/Main-ObjectHandle.cppm)

Because components must be pod, you can't have object references like `std::shared_ptr` in the them.
But the components sometimes need to have them to reference meshes, materials and other game resources.

To solve this problem, you can register an object inside a world and get an object handle which is a pure data struct
that can be used inside components.

#### [QueryParams](Source/Main-QueryParams.cppm)

Different structs and functions for world queries.

The main ones are `PonyEngine::World::QueryParams` and `PonyEngine::World::QueryItem` that world `Query()` function uses directly.
But they are too abstract and may be hard to use in a game code. That's why the API provides useful template helpers like
`PonyEngine::World::Query` and `PonyEngine::World::MakeQuery()`.

#### [IWorld](Source/Main-IWorld.cppm)

World interface. Each world is a totally separate from other worlds. It has its own entities and components.
Also, each world has its own object storage.

#### [IWorldService](Source/Main-IWorldService.cppm)

World service public interface. It provides functions for component registration and world creation.

## How to manage components

First of all each component type must be registered via `RegisterComponent()` function in `PonyEngine::World::IWorldService` before any usage.

Then you can freely add or remove components to entities in worlds. Every entity may have only one instance of a component.

## How to make queries

`PonyEngine::World::IWorld` has `Query()` function which may be used to query entities. You pass two arguments to it:

- QueryParams. It contains a list of required, excluded and optional component types.
- Callback function that receives a QueryItem. For each entity that satisfies the QueryParams, this callback will be called.
QueryItem contains pointers to required components (can't be nullptr) and to optional components (can be nullptr), an entity and a bool terminate parameter.
If you set the terminate parameter to `true`, the query will terminate immediately and won't try to find other entities.

The `QueryParams` and `QueryItem` are too abstract and can be hard to use in a game code. That's why the module has template helpers.
To create a query paramater use `PonyEngine::World::MakeQuery()` function. It takes a list of required, excluded and optional component types as template parameters
and returns `PonyEngine::World::Query` template instance. It has `QueryParams` member that contains correct query params to pass to `Query()` function.
It has functions `GetRequired()` and `GetOptional()` that take `QueryItem` and return a correct reference or pointer to a component inside that query item.

Example:

```
struct Position final
{
	PonyEngine::Math::Vector3<float> value;
};
struct Velocity final
{
	PonyEngine::Math::Vector3<float> value;
};

struct Immobilized final
{
};

struct Acceleration final
{
	float value;
};

constexpr auto query = PonyEngine::World::MakeQuery(PonyEngine::World::Required<Position, Velocity>(), 
	PonyEngine::World::Excluded<Immobilized>(),
	PonyEngine::World::Optional<Acceleration>());
world->Query(query.QueryParams, [](PonyEngine::World::QueryItem& item)
{
	Position& position = query.GetRequired<Position>(item);
	const Velocity& velocity = query.GetRequired<Velocity>(item);
	const Acceleration* const acceleration = query.GetOptional<Acceleration>(item);
	position.value += velocity.value * (acceleration ? acceleration->value : 1.f);
});
```

## How to manage objects

Add an object to the world object storage via the function `RegisterObject()` in the world. It will return a handle to it that can be used in components of this world.

To get an object by handle, use `GetObject()` function.

The world provides the function `CollectGarbage()` to remove unreferenced objects from the storage.
But to make it work right, you have to register all the component members that may use `ObjectHandle`.
To do it, use `RegisterComponentObjectHandleMember()` in the world service.
