/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.World.Hierarchy.Impl:HierarchyService;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.World.Hierarchy;

export namespace PonyEngine::World::Hierarchy
{
	class HierarchyService final : public IHierarchyService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit HierarchyService(Application::IApplication& application);
		HierarchyService(const HierarchyService&) = delete;
		HierarchyService(HierarchyService&&) = delete;

		~HierarchyService() noexcept = default;

		virtual void RemoveInvalidParents(IWorld& world) const override;

		virtual void UpdateTransforms2D(IWorld& world) const override;
		virtual void UpdateTransforms3D(IWorld& world) const override;

		HierarchyService& operator =(const HierarchyService&) = delete;
		HierarchyService& operator =(HierarchyService&&) = delete;

	private:
		template<std::size_t Size>
		void AddLocalTransforms(IWorld& world) const;
		template<std::size_t Size>
		void UpdateTransforms(IWorld& world) const;

		Application::IApplication* application;
		Log::ILogService* logService;
	};
}

namespace PonyEngine::World::Hierarchy
{
	HierarchyService::HierarchyService(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()}
	{
		IWorldService& worldService = this->application->GetInterface<IWorldService>();
		worldService.RegisterComponent<Parent>();
		worldService.RegisterComponent<LocalTransform2D>();
		worldService.RegisterComponent<LocalTransform3D>();
		worldService.RegisterComponent<WorldTransform2D>();
		worldService.RegisterComponent<WorldTransform3D>();
	}

	void HierarchyService::RemoveInvalidParents(IWorld& world) const
	{
		static_assert(sizeof(Entity) == sizeof(Parent) && alignof(Entity) == alignof(Parent), "Invalid parent component");

		const std::size_t parentCount = world.CountComponents<Parent>();
		if (parentCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(parentCount) +
			Memory::CalculateBufferSize<Entity, Entity>(parentCount) +
			Memory::CalculateBufferSize<bool, Entity>(parentCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(parentCount);
		const std::span<Entity> parents = arena.AllocateArray<Entity>(parentCount);
		const std::span<bool> areValid = arena.AllocateArray<bool>(parentCount);

		world.GetComponents(entities, std::span(reinterpret_cast<Parent*>(parents.data()), parents.size()));

		if (!world.AreValid(parents, areValid))
		{
			std::size_t invalidCount = 0uz;
			for (std::size_t i = 0uz; i < parentCount; ++i)
			{
				entities[invalidCount] = entities[i];
				invalidCount += !areValid[i];
			}

			PONY_LOG(logService, Log::LogType::Debug, "Removing '{}' invalid parent components.", invalidCount);
			world.RemoveComponents<Parent>(entities.subspan(0uz, invalidCount));
		}
	}

	void HierarchyService::UpdateTransforms2D(IWorld& world) const
	{
		AddLocalTransforms<2>(world);
		UpdateTransforms<2>(world);
	}

	void HierarchyService::UpdateTransforms3D(IWorld& world) const
	{
		AddLocalTransforms<3>(world);
		UpdateTransforms<3>(world);
	}

	template<std::size_t Size>
	void HierarchyService::AddLocalTransforms(IWorld& world) const
	{
		static_assert(sizeof(Entity) == sizeof(Parent) && alignof(Entity) == alignof(Parent), "Invalid parent component");

		using LTransform = LocalTransform<Size>;

		const std::size_t parentCount = world.CountComponents<Parent>();
		if (parentCount == 0uz)
		{
			return;
		}

		const std::size_t maxEntityCount = parentCount * 2uz;
		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(maxEntityCount) +
			Memory::CalculateBufferSize<Entity, Entity>(parentCount) +
			Memory::CalculateBufferSize<bool, Entity>(maxEntityCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(maxEntityCount);
		const std::span<Entity> children = entities.subspan(0uz, parentCount);
		const std::span<Entity> parents = arena.AllocateArray<Entity>(parentCount);

		world.GetComponents(children, std::span(reinterpret_cast<Parent*>(parents.data()), parents.size()));

		std::size_t uniqueParentCount = 0uz;
		for (const Entity parent : parents)
		{
			parents[uniqueParentCount] = parent;
			uniqueParentCount += !std::ranges::contains(AsRawData(parents.subspan(0uz, uniqueParentCount)), AsRawData(parent));
		}

		const std::span<Entity> uniqueParents = parents.subspan(0uz, uniqueParentCount);

		std::size_t rootCount = 0uz;
		for (const Entity parent : uniqueParents)
		{
			entities[parentCount + rootCount] = parent;
			rootCount += !std::ranges::contains(AsRawData(children), AsRawData(parent));
		}

		const std::size_t hierarchyEntityCount = parentCount + rootCount;
		const std::span<Entity> hierarchyEntities = entities.subspan(0uz, hierarchyEntityCount);
		const std::span<bool> hasTransform = arena.AllocateArray<bool>(hierarchyEntityCount);

		if (!world.HasComponents<LTransform>(hierarchyEntities, hasTransform))
		{
			std::size_t transformlessEntityCount = 0uz;
			for (std::size_t i = 0uz; i < hierarchyEntityCount; ++i)
			{
				hierarchyEntities[transformlessEntityCount] = hierarchyEntities[i];
				transformlessEntityCount += !hasTransform[i];
			}

			world.AddComponents(hierarchyEntities.subspan(0uz, transformlessEntityCount), LTransform::Identity());
		}
	}

	template<std::size_t Size>
	void HierarchyService::UpdateTransforms(IWorld& world) const
	{
		using LTransform = LocalTransform<Size>;
		using WTransform = WorldTransform<Size>;
	}
}
