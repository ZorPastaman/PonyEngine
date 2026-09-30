# PonyEngine.World.Hierarchy feature module

Provides hierarchy components for World service. Also, provides a hierarchy service interface - 
utility service that lets you easily manipulate the hierarchy components.

The idea is typical. Every entity that needs to participate in the scene hierarchy, has a local transform and a world transform.
It optionally may have a parent. In this case, its world transform inherits a world transform of its parent.

Usually, most of objects in a scene are static and don't need updating every frame. That's why you can use a dirty transform component.
Mark entities that need to be updated with it and call a special function in the hierarchy component that updates only marked entities.

The module provides 2D and 3D transforms. They work independently. But usually you don't want to mix them on one entity.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.World](../World)

## C\++ modules

### [PonyEngine.World.Hierarchy](Source/Hierarchy.cppm)

#### [Parent](Source/Hierarchy-Parent.cppm)

Component that references another entity as a parent of its entity.

#### [LocalTransform](Source/Hierarchy-LocalTransform.cppm)

Local transform.

#### [WorldTransform](Source/Hierarchy-WorldTransform.cppm)

World transform.

#### [DirtyTransform](Source/Hierarchy-DirtyTRansform.cppm)

Tag component that marks world transforms that must be updated.

#### [IHierarchyService](Source/Hierarchy-IHierarchyService.cppm)

Hierarchy service that provides useful function to manipulate the hierarchy entities and components.
