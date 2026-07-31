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

export module PonyEngine.World.Impl:ObjectTable;

import std;

import PonyEngine.Application;
import PonyEngine.Memory;
import PonyEngine.World;

import :ComponentTable;
import :ServiceContext;
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
	/// @brief Object table.
	class ObjectTable final
	{
	public:
		/// @brief Creates an object table.
		[[nodiscard("Pure constructor")]]
		ObjectTable() noexcept = default;
		ObjectTable(const ObjectTable&) = delete;
		ObjectTable(ObjectTable&&) = delete;

		~ObjectTable() noexcept = default;

		/// @brief Registers the object.
		/// @param objectType Object type.
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Weird call")]]
		TypelessObjectHandle RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object);
		/// @brief Unregisters the object.
		/// @param objectType Object type.
		/// @param handle Object handle.
		void UnregisterObject(std::type_index objectType, TypelessObjectHandle handle);
		/// @brief Replaces a registered object.
		/// @param handle Object handle.
		/// @param objectType Object type.
		/// @param object Replacement object.
		void ReplaceObject(TypelessObjectHandle handle, std::type_index objectType, const std::shared_ptr<void>& object);

		/// @brief Checks if the object is valid.
		/// @param objectType Object type.
		/// @param handle Object handle.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsObjectValid(std::type_index objectType, TypelessObjectHandle handle) const noexcept;
		/// @brief Gets an object.
		/// @param objectType Object type.
		/// @param handle Object handle.
		/// @return Object.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<void>& GetObject(std::type_index objectType, TypelessObjectHandle handle) const noexcept;

		/// @brief Collects garbage.
		/// @param context World service context.
		/// @param componentTables Component table.
		/// @param componentTablesIndices Component table index map.
		void CollectGarbage(const ServiceContext& context, std::span<const ComponentTable> componentTables, 
			const std::unordered_map<std::type_index, std::size_t>& componentTablesIndices);

		ObjectTable& operator =(const ObjectTable&) = delete;
		ObjectTable& operator =(ObjectTable&&) = delete;

	private:
		/// @brief Object wrapper.
		struct Object final
		{
			std::shared_ptr<void> object; ///< Object.
			std::type_index type; ///< Object type.
		};

		/// @brief Tries to find an object handle.
		/// @param objectType Object type.
		/// @param object Object.
		/// @return Object handle or @p std::nullopt if not found.
		[[nodiscard("Pure function")]]
		std::optional<TypelessObjectHandle> TryFindObject(std::type_index objectType, const std::shared_ptr<void>& object) const noexcept;
		/// @brief Creates an object registration.
		/// @param objectType Object type.
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Must be used")]]
		TypelessObjectHandle CreateObject(std::type_index objectType, const std::shared_ptr<void>& object);
		/// @brief Reuses an object registration.
		/// @param objectType Object type.
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Must be used")]]
		TypelessObjectHandle ResurrectObject(std::type_index objectType, const std::shared_ptr<void>& object);
		/// @brief Kills an object.
		/// @param handleId Object handle ID.
		void KillObject(HandleID handleId);

		std::vector<HandleID> objectsSparse; ///< Sparse.
		std::vector<HandleVersion> handleVersions; ///< Handle versions. Synced with the @p objectsSparse by index.
		std::vector<HandleID> objectsDense; ///< Dense.
		std::vector<Object> objects; ///< Objects. Synced with the @p objectsDense by index.
		std::vector<HandleID> objectFreeList; ///< Object free list.
		std::unordered_map<std::pair<void*, std::type_index>, HandleID> objectIndices; ///< Object index map.

		static_assert(sizeof(HandleID) <= sizeof(std::size_t), "HandleID is greater than std::size_t.");
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
		if (!IsObjectValid(objectType, handle)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle");
		}

		KillObject(handle.id);
	}

	void ObjectTable::ReplaceObject(const TypelessObjectHandle handle, const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		if (!IsObjectValid(objectType, handle)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle");
		}

		objects[objectsSparse[handle.id]].object = object;
	}

	bool ObjectTable::IsObjectValid(const std::type_index objectType, const TypelessObjectHandle handle) const noexcept
	{
		return handle.id < objectsSparse.size() && objectsSparse[handle.id] < objectsDense.size() && objectsDense[objectsSparse[handle.id]] == handle.id && 
			handleVersions[handle.id] == handle.version && objects[objectsSparse[handle.id]].type == objectType;
	}

	const std::shared_ptr<void>& ObjectTable::GetObject(const std::type_index objectType, const TypelessObjectHandle handle) const noexcept
	{
		assert(IsObjectValid(objectType, handle) && "Invalid handle.");
		return objects[objectsSparse[handle.id]].object;
	}

	void ObjectTable::CollectGarbage(const ServiceContext& context, const std::span<const ComponentTable> componentTables,
		const std::unordered_map<std::type_index, std::size_t>& componentTablesIndices)
	{
		if (objectsDense.empty()) [[unlikely]]
		{
			return;
		}

		const std::size_t denseSize = objectsDense.size();
		const std::size_t bufferSize = Memory::CalculateBufferSize<HandleID>(denseSize) + Memory::CalculateBufferSize<bool, HandleID>(denseSize);
		const auto buffer = Application::ScopedTempBuffer(context.Application(), bufferSize);
		auto arena = Memory::Arena(*buffer);
		const std::span<HandleID> objectsToRemove = arena.AllocateArray<HandleID>(denseSize);
		const std::span<bool> aliveObjectFlags = arena.AllocateArray<bool>(denseSize);
		std::ranges::fill(aliveObjectFlags, false);

		{
			const std::shared_lock<std::shared_mutex> typeRegistryLock = context.TypeRegistry().Lock();
			for (std::size_t foundCount = 0uz; const auto [componentType, componentTableIndex] : componentTablesIndices)
			{
				const std::span<const std::pair<std::size_t, std::type_index>> objectOffsets = context.TypeRegistry().ObjectOffsets(componentType);
				if (objectOffsets.empty())
				{
					continue;
				}

				const ComponentTable& componentTable = componentTables[componentTableIndex];
				for (EntityID entityIndex = 0uz; entityIndex < componentTable.Size(); ++entityIndex)
				{
					const auto component = static_cast<const std::byte*>(componentTable.Component(entityIndex));

					for (const auto [offset, objectType] : objectOffsets)
					{
						const TypelessObjectHandle handle = *reinterpret_cast<const TypelessObjectHandle*>(component + offset);
						if (!IsObjectValid(objectType, handle)) [[unlikely]]
						{
							continue;
						}

						const HandleID flagIndex = objectsSparse[handle.id];
						foundCount += !aliveObjectFlags[flagIndex];
						aliveObjectFlags[flagIndex] = true;

						if (foundCount >= denseSize) [[unlikely]]
						{
							return;
						}
					}
				}
			}
		}

		std::size_t removeCount = 0uz;
		for (std::size_t i = 0uz; i < denseSize; ++i)
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
