/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Impl:ObjectRegistry;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Job;
import PonyEngine.World;

import :World;

template<>
struct std::hash<std::pair<void*, std::type_index>> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const std::pair<void*, std::type_index>& pair) const noexcept
	{
		const std::size_t pointerHash = std::hash<void*>()(pair.first);
		const std::size_t typeHash = pair.second.hash_code();
		return pointerHash ^ (typeHash + 0x9E3779B9 + (pointerHash << 6) + (pointerHash >> 2));
	}
};

export namespace PonyEngine::World
{
	class ObjectRegistry final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ObjectRegistry(Application::IApplicationContext& application) noexcept;

		void RegisterComponentObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset);

		[[nodiscard("Weird call")]]
		std::pair<HandleID, HandleVersion> RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object);
		void UnregisterObject(std::type_index objectType, HandleID handleId, HandleVersion handleVersion);

		[[nodiscard("Pure function")]]
		bool IsObjectValid(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<void>& GetObject(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) const;

		void CollectGarbage(std::span<const std::weak_ptr<const World>> worlds);

	private:
		struct Object final
		{
			std::shared_ptr<void> object;
			std::type_index type;
			HandleVersion version;
		};

		struct FlagDeleter final
		{
			void operator ()(bool* ptr) const noexcept;
		};

		struct GarbageCollectionTask final : Job::ITask
		{
			const ObjectRegistry* registry;
			HandleID offset;
			HandleID count;

			virtual void Execute() noexcept override;

		private:
			[[nodiscard("Pure function")]]
			bool IsAlive(HandleID handleId) const noexcept;
		};

		void RemoveObject(HandleID handleId);

		Application::IApplicationContext* application;
		Job::IJobService* jobService;

		std::unordered_map<std::type_index, std::unordered_map<std::type_index, std::vector<std::size_t>>> objectOffsets;

		std::vector<Object> objects;
		std::vector<HandleID> objectFreeList;
		std::unordered_map<std::pair<void*, std::type_index>, HandleID> objectIndices;

		std::vector<std::shared_ptr<const World>> worldsGarbage;
		std::vector<HandleID> aliveObjectIndicesGarbage;
		std::unique_ptr<bool[], FlagDeleter> aliveObjectFlagsGarbage;
		std::size_t aliveObjectFlagsGarbageCapacity;
		std::vector<std::shared_ptr<GarbageCollectionTask>> tasksGarbage;
		std::vector<Job::JobHandle> jobHandlesGarbage;

		static_assert(sizeof(HandleID) <= sizeof(std::size_t), "HandleID is greater than std::size_t.");
	};
}

namespace PonyEngine::World
{
	ObjectRegistry::ObjectRegistry(Application::IApplicationContext& application) noexcept :
		application{&application},
		jobService{&this->application->GetService<Job::IJobService>()},
		aliveObjectFlagsGarbageCapacity{0uz}
	{
	}

	void ObjectRegistry::RegisterComponentObjectHandleMember(const std::type_index objectType, const std::type_index componentType, const std::size_t componentOffset)
	{
		std::vector<std::size_t>& offsets = objectOffsets[objectType][componentType];

		if (const auto position = std::ranges::lower_bound(offsets, componentOffset); position == offsets.cend() || *position != componentOffset) [[likely]]
		{
			offsets.insert(position, componentOffset);
		}
	}

	std::pair<HandleID, HandleVersion> ObjectRegistry::RegisterObject(const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		const auto objectTypePair = std::pair(object.get(), objectType);

		if (const auto position = objectIndices.find(objectTypePair); position != objectIndices.cend())
		{
			const HandleID handleId = position->second;
			const HandleVersion handleVersion = objects[handleId].version;
			return std::pair(handleId, handleVersion);
		}

		if (objectFreeList.empty())
		{
			if (objects.size() >= std::numeric_limits<HandleID>::max()) [[unlikely]]
			{
				throw std::logic_error("Object list is full");
			}

			const HandleID handleId = static_cast<HandleID>(objects.size());
			constexpr HandleVersion handleVersion = 1u;
			objects.push_back(Object{.object = object, .type = objectType, .version = handleVersion});
			try
			{
				objectIndices[objectTypePair] = handleId;
			}
			catch (...)
			{
				objects.pop_back();
				throw;
			}

			return std::pair(handleId, handleVersion);
		}

		const HandleID handleId = objectFreeList.back();
		objectIndices[objectTypePair] = handleId;
		const HandleVersion handleVersion = objects[handleId].version + 1u;
		objects[handleId] = Object{.object = object, .type = objectType, .version = handleVersion};
		objectFreeList.pop_back();

		return std::pair(handleId, handleVersion);
	}

	void ObjectRegistry::UnregisterObject(const std::type_index objectType, const HandleID handleId, const HandleVersion handleVersion)
	{
#ifndef NDEBUG
		if (!IsObjectValid(objectType, handleId, handleVersion)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle");
		}
#endif

		RemoveObject(std::size_t{handleId});
	}

	bool ObjectRegistry::IsObjectValid(const std::type_index objectType, const HandleID handleId, const HandleVersion handleVersion) const noexcept
	{
		return handleId < objects.size() && objects[handleId].type == objectType && objects[handleId].version == handleVersion;
	}

	const std::shared_ptr<void>& ObjectRegistry::GetObject(const std::type_index objectType, const HandleID handleId, const HandleVersion handleVersion) const
	{
#ifndef NDEBUG
		if (!IsObjectValid(objectType, handleId, handleVersion)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle");
		}
#endif

		const std::size_t index = std::size_t{handleId};
		return objects[index].object;
	}

	void ObjectRegistry::CollectGarbage(const std::span<const std::weak_ptr<const World>> worlds)
	{
		try
		{
			worldsGarbage.reserve(worlds.size());
			for (const std::weak_ptr<const World>& world : worlds)
			{
				if (std::shared_ptr<const World> worldPtr = world.lock())
				{
					worldsGarbage.push_back(std::move(worldPtr));
				}
			}

			aliveObjectIndicesGarbage.clear();
			aliveObjectIndicesGarbage.reserve(objects.size() - objectFreeList.size());
			for (HandleID i = 0uz; i < objects.size(); ++i)
			{
				if (objects[i].object)
				{
					aliveObjectIndicesGarbage.push_back(i);
				}
			}

			if (aliveObjectFlagsGarbageCapacity < aliveObjectIndicesGarbage.capacity())
			{
				aliveObjectFlagsGarbage = std::unique_ptr<bool[], FlagDeleter>(static_cast<bool*>(
					operator new[](aliveObjectIndicesGarbage.capacity() * sizeof(bool), std::align_val_t{std::hardware_destructive_interference_size})), FlagDeleter{});
				aliveObjectFlagsGarbageCapacity = aliveObjectIndicesGarbage.capacity();
			}
			std::fill_n(aliveObjectFlagsGarbage.get(), aliveObjectIndicesGarbage.size(), false);

			const std::size_t jobCount = aliveObjectIndicesGarbage.size() / std::hardware_destructive_interference_size + 
				(aliveObjectIndicesGarbage.size() % std::hardware_destructive_interference_size != 0uz);

			tasksGarbage.reserve(jobCount);
			for (std::size_t i = tasksGarbage.size(); i < jobCount; ++i)
			{
				tasksGarbage.push_back(std::make_shared<GarbageCollectionTask>());
			}

			jobHandlesGarbage.clear();
			jobHandlesGarbage.reserve(jobCount);
			for (std::size_t i = 0uz; i < jobCount; ++i)
			{
				const std::shared_ptr<GarbageCollectionTask>& task = tasksGarbage[i];
				task->registry = this;
				task->offset = static_cast<HandleID>(i * jobCount);
				task->count = static_cast<HandleID>(std::min(std::hardware_destructive_interference_size, aliveObjectIndicesGarbage.size() - task->offset));
				jobHandlesGarbage.push_back(jobService->Schedule(tasksGarbage[i]));
			}
			jobService->Wait(jobHandlesGarbage);

			for (std::size_t i = aliveObjectIndicesGarbage.size(); i-- > 0uz; )
			{
				if (!aliveObjectFlagsGarbage[i])
				{
					RemoveObject(aliveObjectIndicesGarbage[i]);
				}
			}

			worldsGarbage.clear();
		}
		catch (...)
		{
			jobService->Wait(jobHandlesGarbage);
			worldsGarbage.clear();
			throw;
		}
	}

	void ObjectRegistry::FlagDeleter::operator ()(bool* const ptr) const noexcept
	{
		operator delete[](ptr, std::align_val_t{std::hardware_destructive_interference_size});
	}

	void ObjectRegistry::GarbageCollectionTask::Execute() noexcept
	{
		for (std::size_t i = 0uz; i < count; ++i)
		{
			const std::size_t flagIndex = offset + i;
			const HandleID handleId = registry->aliveObjectIndicesGarbage[flagIndex];
			registry->aliveObjectFlagsGarbage[flagIndex] = IsAlive(handleId);
		}
	}

	bool ObjectRegistry::GarbageCollectionTask::IsAlive(const HandleID handleId) const noexcept
	{
		const Object& object = registry->objects[handleId];
		const std::type_index objectType = object.type;
		const HandleVersion handleVersion = object.version;
		const auto handle = ObjectHandle<void>{.id = handleId, .version = handleVersion};

		if (const auto objectTypePosition = registry->objectOffsets.find(objectType); objectTypePosition != registry->objectOffsets.cend()) [[likely]]
		{
			for (const std::shared_ptr<const World>& world : registry->worldsGarbage)
			{
				for (const auto [componentType, componentOffsets] : objectTypePosition->second)
				{
					const auto [componentData, componentSize] = world->GetComponentData(componentType);
					for (const std::byte* component = componentData.data(); component < componentData.data() + componentData.size(); component += componentSize)
					{
						for (const std::size_t offset : componentOffsets)
						{
							if (*reinterpret_cast<const ObjectHandle<void>*>(component + offset) == handle)
							{
								return true;
							}
						}
					}
				}
			}
		}

		return false;
	}

	void ObjectRegistry::RemoveObject(const HandleID handleId)
	{
		Object& object = objects[handleId];
		objectFreeList.push_back(handleId);
		objectIndices.erase(std::pair(object.object.get(), object.type));
		object.object = nullptr;
		++object.version;
	}
}
