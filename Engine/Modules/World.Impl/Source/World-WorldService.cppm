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

export module PonyEngine.World.Impl:WorldService;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.World;

import :ObjectTable;
import :TypeRegistry;
import :World;

export namespace PonyEngine::World
{
	/// @brief World service.
	class WorldService final : public IWorldService
	{
	public:
		/// @brief Creates a world service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit WorldService(Application::IApplication& application) noexcept;
		WorldService(const WorldService&) = delete;
		WorldService(WorldService&&) = delete;

		~WorldService() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IWorld> CreateWorld() override;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IWorld> CreateWorld(const WorldDefinition& definition) override;

		WorldService& operator =(const WorldService&) = delete;
		WorldService& operator =(WorldService&&) = delete;

	protected:
		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) override;
		virtual void RegisterComponentObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset) override;
		virtual void RegisterEntityReferenceMember(std::type_index componentType, std::size_t componentOffset) override;

	private:
		[[nodiscard("Pure function")]]
		std::shared_ptr<World> MakeWorld();
		void AddToWorld(World& world, const WorldDefinition& definition) const;

		Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.

		TypeRegistry typeRegistry; ///< Type registry.

#ifndef NDEBUG
		std::atomic_size_t worldCount; ///< World count.
#endif
	};
}

namespace PonyEngine::World
{
	WorldService::WorldService(Application::IApplication& application) noexcept :
#ifndef NDEBUG
		worldCount(0uz),
#endif
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()}
	{
	}

	WorldService::~WorldService() noexcept
	{
#ifndef NDEBUG
		assert(worldCount.load(std::memory_order::relaxed) == 0uz && "Some worlds weren't destroyed.");
#endif
	}

	std::shared_ptr<IWorld> WorldService::CreateWorld()
	{
		return MakeWorld();
	}

	std::shared_ptr<IWorld> WorldService::CreateWorld(const WorldDefinition& definition)
	{
		std::shared_ptr<World> world = MakeWorld();
		AddToWorld(*world, definition);

		return world;
	}

	void WorldService::RegisterComponent(const std::type_index componentType, const std::size_t componentSize, const std::size_t componentAlignment)
	{
		PONY_LOG(logService, Log::LogType::Info, "Registering component type. Type name: '{}'; size: '{}'; alignment: '{}'.",
			componentType.name(), componentSize, componentAlignment);
		const std::shared_lock<std::shared_mutex> lock = typeRegistry.Lock();
		typeRegistry.AddComponentType(componentType, componentSize, componentAlignment);
	}

	void WorldService::RegisterComponentObjectHandleMember(const std::type_index objectType, const std::type_index componentType, const std::size_t componentOffset)
	{
		PONY_LOG(logService, Log::LogType::Info, "Registering component object handle member. Component type name: '{}'; Object type name: '{}'; Component offset: '{}'.",
			componentType.name(), objectType.name(), componentOffset);
		const std::shared_lock<std::shared_mutex> lock = typeRegistry.Lock();
		typeRegistry.RegisterComponentObjectHandleMember(objectType, componentType, componentOffset);
	}

	void WorldService::RegisterEntityReferenceMember(const std::type_index componentType, const std::size_t componentOffset)
	{
		PONY_LOG(logService, Log::LogType::Info, "Registering component entity reference. Component type name: '{}'; Reference offset: '{}'.",
			componentType.name(), componentOffset);
		const std::shared_lock<std::shared_mutex> lock = typeRegistry.Lock();
		typeRegistry.RegisterEntityReferenceMember(componentType, componentOffset);
	}

	std::shared_ptr<World> WorldService::MakeWorld()
	{
#ifndef NDEBUG
		const auto world = new World(*application, typeRegistry);
		worldCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<World>(world, [this](const World* const worldToDestroy) noexcept
				{
					delete worldToDestroy;
					worldCount.fetch_sub(1uz, std::memory_order::relaxed);
				});
		}
		catch (...)
		{
			delete world;
			worldCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<World>(*application, typeRegistry);
#endif
	}

	void WorldService::AddToWorld(World& world, const WorldDefinition& definition) const
	{
		const std::shared_lock<std::shared_mutex> lock = typeRegistry.Lock();

		std::size_t maxComponentCount = 0uz;
		for (const auto& [type, table] : definition.components)
		{
			if (!typeRegistry.IsValidComponent(type)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid component type");
			}

			for (const EntityID entity : table.entityBindings)
			{
				if (entity >= definition.entityCount) [[unlikely]]
				{
					throw std::invalid_argument("Invalid component binding");
				}
			}

			const std::size_t componentSize = typeRegistry.ComponentSize(type);
			if (table.data.size() != componentSize * table.entityBindings.size()) [[unlikely]]
			{
				throw std::invalid_argument("Invalid component data");
			}

			maxComponentCount = std::max(maxComponentCount, table.entityBindings.size());
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(definition.entityCount) +
			Memory::CalculateBufferSize<Entity, Entity>(maxComponentCount) +
			Memory::CalculateBufferSize<void*, Entity>(maxComponentCount) +
			Memory::CalculateBufferSize<TypelessObjectHandle, void*>(definition.objects.size());
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(definition.entityCount);
		const std::span<Entity> componentEntities = arena.AllocateArray<Entity>(maxComponentCount);
		const std::span<void*> components = arena.AllocateArray<void*>(maxComponentCount);
		const std::span<TypelessObjectHandle> objects = arena.AllocateArray<TypelessObjectHandle>(definition.objects.size());

		for (const auto& [type, data] : definition.worldData)
		{
			world.AddWorldData(type, data);
		}

		for (std::size_t i = 0uz; i < objects.size(); ++i)
		{
			const auto& [type, object] = definition.objects[i];
			objects[i] = world.RegisterObject(type, object);
		}

		world.CreateEntities(entities);

		for (const auto& [type, table] : definition.components)
		{
			const std::span<const EntityID> bindings = table.entityBindings;
			const std::span<const std::byte> componentData = table.data;

			for (std::size_t i = 0uz; i < bindings.size(); ++i)
			{
				componentEntities[i] = entities[bindings[i]];
			}

			const std::span<void*> thisComponents = components.subspan(0uz, bindings.size());
			world.AddComponents(componentEntities.subspan(0uz, bindings.size()), type, componentData, thisComponents);

			if (const std::span<const std::pair<std::size_t, std::type_index>> objectOffsets = typeRegistry.ObjectOffsets(type); !objectOffsets.empty())
			{
				for (void* const thisComponent : thisComponents)
				{
					const auto component = static_cast<std::byte*>(thisComponent);
					for (const auto offset : std::views::keys(objectOffsets))
					{
						std::byte* const handlePointer = component + offset;
						TypelessObjectHandle& handle = *reinterpret_cast<TypelessObjectHandle*>(handlePointer);
						const std::uint64_t objectIndex = *reinterpret_cast<std::uint64_t*>(handlePointer);

						if (objectIndex == std::numeric_limits<std::uint64_t>::max())
						{
							handle = TypelessObjectHandle{};
						}
						else if (objectIndex < objects.size()) [[likely]]
						{
							handle = objects[static_cast<std::size_t>(objectIndex)];
						}
						else [[unlikely]]
						{
							throw std::invalid_argument("Invalid object index");
						}
					}
				}
			}

			if (const std::span<const std::size_t> entityOffsets = typeRegistry.EntityReferences(type); !entityOffsets.empty())
			{
				for (void* const thisComponent : thisComponents)
				{
					const auto component = static_cast<std::byte*>(thisComponent);
					for (const std::size_t offset : entityOffsets)
					{
						std::byte* const entityPointer = component + offset;
						Entity& entity = *reinterpret_cast<Entity*>(entityPointer);
						const std::uint64_t entityIndex = *reinterpret_cast<std::uint64_t*>(entityPointer);

						if (entityIndex == std::numeric_limits<std::uint64_t>::max())
						{
							entity = Entity{};
						}
						if (entityIndex < entities.size()) [[likely]]
						{
							entity = entities[static_cast<std::size_t>(entityIndex)];
						}
						else [[unlikely]]
						{
							throw std::invalid_argument("Invalid entity index");
						}
					}
				}
			}
		}
	}
}
