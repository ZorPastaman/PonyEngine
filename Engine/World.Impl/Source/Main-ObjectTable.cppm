/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Impl:ObjectTable;

import std;

import PonyEngine.World;

import :ComponentTable;
import :TypeRegistry;

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
	class ObjectTable final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ObjectTable() noexcept = default;
		ObjectTable(const ObjectTable&) = delete;
		ObjectTable(ObjectTable&&) = delete;

		~ObjectTable() noexcept = default;

		[[nodiscard("Weird call")]]
		TypelessObjectHandle RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object);
		void UnregisterObject(std::type_index objectType, TypelessObjectHandle handle);

		[[nodiscard("Pure function")]]
		bool IsObjectValid(std::type_index objectType, TypelessObjectHandle handle) const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<void>& GetObject(std::type_index objectType, TypelessObjectHandle handle) const;

		void CollectGarbage(const TypeRegistry& typeRegistry,
			std::span<const ComponentTable> componentTables, const std::unordered_map<std::type_index, std::size_t>& componentTablesIndices);

		ObjectTable& operator =(const ObjectTable&) = delete;
		ObjectTable& operator =(ObjectTable&&) = delete;

	private:
		struct Object final
		{
			std::shared_ptr<void> object;
			std::type_index type;
		};

		[[nodiscard("Pure function")]]
		std::optional<TypelessObjectHandle> TryFindObject(std::type_index objectType, const std::shared_ptr<void>& object) const noexcept;
		[[nodiscard("Must be used")]]
		TypelessObjectHandle CreateObject(std::type_index objectType, const std::shared_ptr<void>& object);
		[[nodiscard("Must be used")]]
		TypelessObjectHandle ResurrectObject(std::type_index objectType, const std::shared_ptr<void>& object);
		void KillObject(HandleID handleId);

		std::vector<HandleID> objectsSparse;
		std::vector<HandleVersion> handleVersions;
		std::vector<HandleID> objectsDense;
		std::vector<Object> objects;
		std::vector<HandleID> objectFreeList;
		std::unordered_map<std::pair<void*, std::type_index>, HandleID> objectIndices;

		std::vector<bool> aliveObjectFlags;
		std::vector<HandleID> objectsToRemove;

		static_assert(sizeof(HandleID) <= sizeof(std::size_t), "HandleID is greater than std::size_t.");
		static_assert(std::atomic_ref<bool>::is_always_lock_free, "bool is not lock free.");
	};
}

namespace PonyEngine::World
{
	TypelessObjectHandle ObjectTable::RegisterObject(const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		if (const std::optional<TypelessObjectHandle> fromExisting = TryFindObject(objectType, object))
		{
			return *fromExisting;
		}

		if (objectFreeList.empty())
		{
			return CreateObject(objectType, object);
		}

		return ResurrectObject(objectType, object);
	}

	void ObjectTable::UnregisterObject(const std::type_index objectType, const TypelessObjectHandle handle)
	{
#ifndef NDEBUG
		if (!IsObjectValid(objectType, handle)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle");
		}
#endif

		KillObject(handle.id);
	}

	bool ObjectTable::IsObjectValid(const std::type_index objectType, const TypelessObjectHandle handle) const noexcept
	{
		return handle.id < objectsSparse.size() && objectsSparse[handle.id] < objectsDense.size() && objectsDense[objectsSparse[handle.id]] == handle.id && 
			handleVersions[handle.id] == handle.version && objects[objectsSparse[handle.id]].type == objectType;
	}

	const std::shared_ptr<void>& ObjectTable::GetObject(const std::type_index objectType, const TypelessObjectHandle handle) const
	{
#ifndef NDEBUG
		if (!IsObjectValid(objectType, handle)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle");
		}
#endif

		return objects[objectsSparse[handle.id]].object;
	}

	void ObjectTable::CollectGarbage(const TypeRegistry& typeRegistry,
		const std::span<const ComponentTable> componentTables, const std::unordered_map<std::type_index, std::size_t>& componentTablesIndices)
	{
		aliveObjectFlags.resize(objectsDense.size());
		std::ranges::fill(aliveObjectFlags, false);
		objectsToRemove.resize(objectsDense.size());

		for (const auto [componentType, componentTableIndex] : componentTablesIndices)
		{
			const std::span<const std::pair<std::size_t, std::type_index>> objectOffsets = typeRegistry.ObjectOffsets(componentType);
			if (objectOffsets.empty())
			{
				continue;
			}

			const ComponentTable& componentTable = componentTables[componentTableIndex];
			for (EntityID i = 0uz; i < componentTable.Size(); ++i)
			{
				const auto component = static_cast<std::byte*>(componentTable.Component(i));

				for (const auto [offset, objectType] : objectOffsets)
				{
					const TypelessObjectHandle handle = *reinterpret_cast<const TypelessObjectHandle*>(component + offset);
					const bool currentFlag = aliveObjectFlags[objectsSparse[handle.id]];
					aliveObjectFlags[objectsSparse[handle.id]] = currentFlag | IsObjectValid(objectType, handle);
				}
			}
		}

		std::size_t removeCount = 0uz;
		for (std::size_t i = 0uz; i < objectsDense.size(); ++i)
		{
			objectsToRemove[removeCount] = objectsDense[i];
			removeCount += !aliveObjectFlags[i];
		}
		objectFreeList.reserve(objectFreeList.size() + removeCount);
		for (std::size_t i = 0uz; i < removeCount; ++i)
		{
			KillObject(objectsToRemove[i]);
		}
	}

	std::optional<TypelessObjectHandle> ObjectTable::TryFindObject(const std::type_index objectType, const std::shared_ptr<void>& object) const noexcept
	{
		const auto objectTypePair = std::pair(object.get(), objectType);
		if (const auto position = objectIndices.find(objectTypePair); position != objectIndices.cend())
		{
			const HandleID handleId = position->second;
			return TypelessObjectHandle{.id = handleId, .version = handleVersions[handleId]};
		}

		return std::nullopt;
	}

	TypelessObjectHandle ObjectTable::CreateObject(const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		if (objectsSparse.size() >= std::numeric_limits<HandleID>::max()) [[unlikely]]
		{
			throw std::logic_error("Object list is full");
		}

		const HandleID handleId = static_cast<HandleID>(objectsSparse.size());
		constexpr HandleVersion handleVersion = 1u;

		objectsSparse.push_back(static_cast<HandleID>(objectsDense.size()));
		try
		{
			handleVersions.push_back(handleVersion);
			try
			{
				objectsDense.push_back(handleId);
				try
				{
					objects.push_back(Object{.object = object, .type = objectType});
					try
					{
						const auto objectTypePair = std::pair(object.get(), objectType);
						objectIndices[objectTypePair] = handleId;
					}
					catch (...)
					{
						objects.pop_back();
						throw;
					}
				}
				catch (...)
				{
					objectsDense.pop_back();
					throw;
				}
			}
			catch (...)
			{
				handleVersions.pop_back();
				throw;
			}
		}
		catch (...)
		{
			objectsSparse.pop_back();
			throw;
		}

		return TypelessObjectHandle{.id = handleId, .version = handleVersion};
	}

	TypelessObjectHandle ObjectTable::ResurrectObject(const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		const HandleID handleId = objectFreeList.back();
		const auto objectTypePair = std::pair(object.get(), objectType);
		objectIndices[objectTypePair] = handleId;
		objectFreeList.pop_back();
		objectsSparse[handleId] = static_cast<HandleID>(objectsDense.size());
		const HandleVersion handleVersion = ++handleVersions[handleId];
		objectsDense.push_back(handleId);
		objects.push_back(Object{.object = object, .type = objectType});

		return TypelessObjectHandle{.id = handleId, .version = handleVersion};
	}

	void ObjectTable::KillObject(const HandleID handleId)
	{
		objectFreeList.push_back(handleId);

		Object& object = objects[handleId];
		const auto objectTypePair = std::pair(object.object.get(), object.type);
		objectIndices.erase(objectTypePair);

		const HandleID lastHandle = objectsDense.back();
		objectsDense[handleId] = lastHandle;
		std::swap(objects[handleId], objects[lastHandle]);
		objectsSparse[lastHandle] = handleId;

		objectsSparse[handleId] = std::numeric_limits<HandleID>::max();
		++handleVersions[handleId];
		objectsDense.pop_back();
		objects.pop_back();
	}
}
