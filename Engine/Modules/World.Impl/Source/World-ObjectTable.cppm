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
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.World;

import :ComponentTable;
import :TypeRegistry;

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
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Weird call")]]
		TypelessObjectHandle RegisterObject(Object object);

		/// @brief Checks if the object is valid.
		/// @param objectType Object type.
		/// @param isConst Is the object const?
		/// @param handle Object handle.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsObjectValid(std::type_index objectType, bool isConst, TypelessObjectHandle handle) const noexcept;
		/// @brief Gets an object.
		/// @param objectType Object type.
		/// @param isConst Is the object const?
		/// @param handle Object handle.
		/// @return Object.
		[[nodiscard("Pure function")]]
		const Object& GetObject(std::type_index objectType, bool isConst, TypelessObjectHandle handle) const noexcept;

		/// @brief Collects garbage.
		/// @param application Application.
		/// @param typeRegistry Type registry.
		/// @param componentTables Component table.
		/// @param componentTablesIndices Component table index map.
		void CollectGarbage(Application::IApplication& application, const TypeRegistry& typeRegistry, std::span<const ComponentTable> componentTables,
			const std::unordered_map<std::type_index, std::size_t>& componentTablesIndices);

		ObjectTable& operator =(const ObjectTable&) = delete;
		ObjectTable& operator =(ObjectTable&&) = delete;

	private:
		/// @brief Creates an object registration.
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Must be used")]]
		TypelessObjectHandle CreateObject(Object object);
		/// @brief Reuses an object registration.
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Must be used")]]
		TypelessObjectHandle ResurrectObject(Object object);
		/// @brief Kills an object.
		/// @param handleId Object handle ID.
		void KillObject(ObjectHandleID handleId);

		std::vector<ObjectHandleID> objectsSparse; ///< Sparse.
		std::vector<ObjectHandleVersion> handleVersions; ///< Handle versions. Synced with the @p objectsSparse by index.
		std::vector<ObjectHandleID> objectsDense; ///< Dense.
		std::vector<Object> objects; ///< Objects. Synced with the @p objectsDense by index.
		std::vector<ObjectHandleID> objectFreeList; ///< Object free list.

		static_assert(sizeof(ObjectHandleID) <= sizeof(std::size_t), "ObjectHandleID is greater than std::size_t.");
	};
}

namespace PonyEngine::World
{
	TypelessObjectHandle ObjectTable::RegisterObject(Object object)
	{
		return objectFreeList.empty() ? CreateObject(std::move(object)) : ResurrectObject(std::move(object));
	}

	bool ObjectTable::IsObjectValid(const std::type_index objectType, const bool isConst, const TypelessObjectHandle handle) const noexcept
	{
		if (Math::IsOdd(handle.version) && handle.id < objectsSparse.size() && handleVersions[handle.id] == handle.version && objectsSparse[handle.id] < objectsDense.size() &&
			objectsDense[objectsSparse[handle.id]] == handle.id)
		{
			const Object& object = objects[objectsSparse[handle.id]];
			return object.IsCastable(objectType, isConst);
		}

		return false;
	}

	const Object& ObjectTable::GetObject(const std::type_index objectType, const bool isConst, const TypelessObjectHandle handle) const noexcept
	{
		assert(IsObjectValid(objectType, isConst, handle) && "Invalid handle.");
		return objects[objectsSparse[handle.id]];
	}

	void ObjectTable::CollectGarbage(Application::IApplication& application, const TypeRegistry& typeRegistry, const std::span<const ComponentTable> componentTables,
		const std::unordered_map<std::type_index, std::size_t>& componentTablesIndices)
	{
		if (objectsDense.empty()) [[unlikely]]
		{
			return;
		}

		const std::size_t denseSize = objectsDense.size();
		const std::size_t bufferSize = Memory::CalculateBufferSize<ObjectHandleID>(denseSize) + Memory::CalculateBufferSize<bool, ObjectHandleID>(denseSize);
		const std::shared_ptr<Application::IBuffer> buffer = application.CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());
		const std::span<ObjectHandleID> objectsToRemove = arena.AllocateArray<ObjectHandleID>(denseSize);
		const std::span<bool> aliveObjectFlags = arena.AllocateArray<bool>(denseSize);
		std::ranges::fill(aliveObjectFlags, false);

		{
			const std::shared_lock<std::shared_mutex> typeRegistryLock = typeRegistry.SharedLock();
			for (std::size_t foundCount = 0uz; const auto [componentType, componentTableIndex] : componentTablesIndices)
			{
				const std::span<const ObjectHandleInfo> handleInfos = typeRegistry.GetObjectHandleInfos(componentType);
				if (handleInfos.empty())
				{
					continue;
				}

				const ComponentTable& componentTable = componentTables[componentTableIndex];
				const std::byte* component = componentTable.FirstComponent();
				for (EntityID entityIndex = 0u; entityIndex < componentTable.Size(); ++entityIndex, component += componentTable.ComponentSize())
				{
					for (const ObjectHandleInfo& handleInfo : handleInfos)
					{
						const TypelessObjectHandle handle = *reinterpret_cast<const TypelessObjectHandle*>(component + handleInfo.offset);
						if (!IsObjectValid(handleInfo.type, handleInfo.isConst, handle))
						{
							continue;
						}

						const ObjectHandleID flagIndex = objectsSparse[handle.id];
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

	TypelessObjectHandle ObjectTable::CreateObject(Object object)
	{
		if (objectsSparse.size() >= std::numeric_limits<ObjectHandleID>::max()) [[unlikely]]
		{
			throw std::logic_error("Object list is full");
		}

		const ObjectHandleID handleId = static_cast<ObjectHandleID>(objectsSparse.size());
		constexpr ObjectHandleVersion handleVersion = 1u;

		objectsSparse.push_back(static_cast<ObjectHandleID>(objectsDense.size()));
		try
		{
			handleVersions.push_back(handleVersion);
			try
			{
				objectsDense.push_back(handleId);
				try
				{
					objects.push_back(std::move(object));
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

	TypelessObjectHandle ObjectTable::ResurrectObject(Object object)
	{
		const ObjectHandleID handleId = objectFreeList.back();
		objectFreeList.pop_back();
		objectsSparse[handleId] = static_cast<ObjectHandleID>(objectsDense.size());
		const ObjectHandleVersion handleVersion = ++handleVersions[handleId];
		objectsDense.push_back(handleId);
		objects.push_back(std::move(object));

		return TypelessObjectHandle{.id = handleId, .version = handleVersion};
	}

	void ObjectTable::KillObject(const ObjectHandleID handleId)
	{
		objectFreeList.push_back(handleId);

		const ObjectHandleID lastHandle = objectsDense.back();
		objectsDense[handleId] = lastHandle;
		std::swap(objects[handleId], objects[lastHandle]);
		objectsSparse[lastHandle] = handleId;

		objectsSparse[handleId] = std::numeric_limits<ObjectHandleID>::max();
		++handleVersions[handleId];
		objectsDense.pop_back();
		objects.pop_back();
	}
}
