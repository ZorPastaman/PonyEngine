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

export module PonyEngine.Resource.World.Impl:WorldDefinitionLoader;

import std;

import PonyEngine.Application;
import PonyEngine.Hash;
import PonyEngine.Job;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.Resource.Ext;
import PonyEngine.Utility;
import PonyEngine.World;

import :CopyComponentDeserializer;
import :LoadableWorldDefinitionLoadRequest;
import :WorldDefinitionLoadRequest;

export namespace PonyEngine::Resource::World
{
	/// @brief World definition loader.
	class WorldDefinitionLoader final : public IResourceLoader, public IWorldDefinitionLoader
	{
	public:
		/// @brief Creates a world definition loader.
		/// @param application 
		[[nodiscard("Pure constructor")]]
		explicit WorldDefinitionLoader(Application::IApplication& application);
		WorldDefinitionLoader(const WorldDefinitionLoader&) = delete;
		WorldDefinitionLoader(WorldDefinitionLoader&&) = delete;

		~WorldDefinitionLoader() noexcept;

		virtual void PrepareResource(ILoadableResource& context) override;
		[[nodiscard("Weird call")]] 
		virtual std::shared_ptr<IResourceLoadRequest> Load(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) override;

		WorldDefinitionLoader& operator =(const WorldDefinitionLoader&) = delete;
		WorldDefinitionLoader& operator =(WorldDefinitionLoader&&) = delete;

	protected:
		virtual void RegisterComponentDeserializer(std::type_index componentType, std::size_t componentSize, std::string_view type) override;
		virtual void UnregisterComponentDeserializer(std::type_index componentType, std::string_view type) override;
		virtual void RegisterComponentDeserializer(std::type_index componentType, std::size_t componentSize, std::string_view type, 
			IInlineComponentDeserializer& deserializer) override;
		virtual void UnregisterComponentDeserializer(std::type_index componentType, std::string_view type, IInlineComponentDeserializer& deserializer) override;
		virtual void RegisterComponentDeserializer(std::type_index componentType, std::size_t componentSize, std::string_view type, 
			IComponentDeserializer& deserializer) override;
		virtual void UnregisterComponentDeserializer(std::type_index componentType, std::string_view type, IComponentDeserializer& deserializer) override;
		virtual void RegisterObjectDeserializer(std::type_index objectType, std::string_view type, IInlineObjectDeserializer& deserializer) override;
		virtual void UnregisterObjectDeserializer(std::type_index objectType, std::string_view type, IInlineObjectDeserializer& deserializer) override;
		virtual void RegisterObjectDeserializer(std::type_index objectType, std::string_view type, IObjectDeserializer& deserializer) override;
		virtual void UnregisterObjectDeserializer(std::type_index objectType, std::string_view type, IObjectDeserializer& deserializer) override;

	private:
		/// @brief Registers the component deserializer.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param type Type in the serialized data.
		/// @return Deserializer slot.
		[[nodiscard("Must be used")]]
		std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>& AddComponentDeserializer(std::type_index componentType, std::size_t componentSize,
			std::string_view type);
		/// @brief Unregisters the component deserializer.
		/// @param componentType Component type.
		/// @param type Type in the serialized data.
		/// @param deserializer Component deserializer.
		void RemoveComponentDeserializer(std::type_index componentType, std::string_view type, 
			const std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>& deserializer) noexcept;
		/// @brief Registers the object deserializer.
		/// @param objectType Object type.
		/// @param type Type in the serialized data.
		/// @return Deserializer slot.
		[[nodiscard("Must be used")]]
		std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>& AddObjectDeserializer(std::type_index objectType, std::string_view type);
		/// @brief Unregisters the object deserializer.
		/// @param objectType Object type.
		/// @param type Type in the serialized data.
		/// @param deserializer Object deserializer.
		void RemoveObjectDeserializer(std::type_index objectType, std::string_view type, 
			const std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>& deserializer) noexcept;

		/// @brief Makes a default load request.
		/// @param context Load context.
		/// @param callback Callback.
		/// @return Load request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceLoadRequest> MakeDefaultLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);
		/// @brief Makes a direct load request.
		/// @param context Load context.
		/// @param callback Callback.
		/// @return Load request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceLoadRequest> MakeDirectLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);

		/// @brief Creates a world definition resource.
		/// @return World definition resource.
		[[nodiscard("Pure function")]]
		std::shared_ptr<PonyEngine::World::WorldDefinition> CreateWorldDefinitionResource();

		/// @brief Adds the load request.
		/// @param request Request to add.
		void AddRequest(const std::shared_ptr<WorldDefinitionLoadRequest>& request);
		/// @brief Removes the load request.
		/// @param request Request to remove.
		/// @return Removed load request.
		std::shared_ptr<WorldDefinitionLoadRequest> RemoveRequest(WorldDefinitionLoadRequest* request) noexcept;

		/// @brief Increment the request count.
		void IncrementRequestCount() noexcept;
		/// @brief Decrement the request count.
		void DecrementRequestCount() noexcept;
		/// @brief Wait till the request count reaches 0.
		void WaitForRequestCountToFinish() const noexcept;

		/// @brief Gets a component info.
		/// @param type Component type in serialized data.
		/// @return Component type and component size.
		[[nodiscard("Pure function")]]
		std::pair<std::type_index, std::size_t> GetComponentInfo(std::string_view type) const;
		/// @brief Gets a component deserializer.
		/// @param type Component type.
		/// @return Component deserializer.
		[[nodiscard("Pure function")]]
		const std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>& GetComponentDeserializer(std::type_index type) const;
		/// @brief Gets an object type.
		/// @param type Object type in serialized data.
		/// @return Object type.
		[[nodiscard("Pure function")]]
		std::type_index GetObjectType(std::string_view type) const;
		/// @brief Gets an object deserializer.
		/// @param type Object type.
		/// @return Object deserializer.
		[[nodiscard("Pure function")]]
		const std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>& GetObjectDeserializer(std::type_index type) const;

		/// @brief Cancels the request.
		/// @param request Request.
		void CancelRequest(WorldDefinitionLoadRequest& request) noexcept;
		/// @brief Finishes the request.
		/// @param request Request.
		void FinishRequest(WorldDefinitionLoadRequest& request) noexcept;

		/// @brief Schedules a job to parse the world definition data.
		/// @param request Request.
		void Parse(WorldDefinitionLoadRequest& request) noexcept;
		/// @brief Validates that the data is of required size.
		/// @param input Current input.
		/// @param inputEnd Input end.
		/// @param requiredSize Required size.
		static void ValidateDataSize(const std::byte* input, const std::byte* inputEnd, std::size_t requiredSize);
		/// @brief Moves the data pointer.
		/// @param input Current input.
		/// @param count How many bytes to skip.
		/// @return Previous input pointer.
		static const std::byte* MoveData(const std::byte*& input, std::size_t count) noexcept;
		/// @brief Reads the data and moves the pointer after it.
		/// @tparam T Data type.
		/// @param input Current input.
		/// @return Read data.
		template<typename T>
		static T ReadData(const std::byte*& input) noexcept;
		/// @brief Reads the data array and moves the pointer after it.
		/// @tparam T Data type.
		/// @param input Current input.
		/// @param data Read data.
		template<typename T>
		static void ReadData(const std::byte*& input, std::span<T> data) noexcept;
		/// @brief Reads the data array and moves the pointer after it.
		/// @tparam T Data type.
		/// @param input Current input.
		/// @param count Read count.
		/// @return Read data.
		template<typename T>
		static std::span<const T> ReadDataSpan(const std::byte*& input, std::size_t count) noexcept requires (sizeof(T) == 1);
		/// @brief Reads the data as a string and moves the pointer after it.
		/// @param input Current input.
		/// @param count Read count.
		/// @return Read data.
		[[nodiscard("Pure function")]]
		static std::string_view ReadDataString(const std::byte*& input, std::size_t count) noexcept;
		/// @brief Sums the data in the span.
		/// @tparam T Data type.
		/// @param data Data.
		/// @return Sum.
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		static std::size_t Sum(std::span<const T> data) noexcept;
		/// @brief Sums the std::size_t array.
		/// @param data Data.
		/// @param count std::size_t count.
		/// @return Sum.
		[[nodiscard("Pure function")]]
		static std::size_t Sum(const std::byte* data, std::size_t count) noexcept;

		inline static const std::type_index DefaultAccessType = typeid(ILoadableDataAccess); ///< Default data access type.
		inline static const std::type_index DirectAccessType = typeid(IMemoryDataAccess); ///< Direct data access type.

		Application::IApplication* application; ///< Application.
		Job::IJobService* jobService; ///< Job service.
		Log::ILogService* logService; ///< Log service.

		std::unordered_map<std::uint64_t, std::type_index> componentTypeMap; ///< Component serialized data type hash to component type map.
		std::unordered_map<std::uint64_t, std::string> componentTypeNameMap; ///< Component serialized data type hash to component serialized data type map.
		std::unordered_map<std::type_index, std::size_t> componentSizeMap; ///< Component type to component size map.
		std::unordered_map<std::type_index, std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>> componentDeserializers; ///< Component type to component deserializer map.
		std::unordered_map<std::uint64_t, std::type_index> objectTypeMap; ///< Object serialized data type hash to object type map.
		std::unordered_map<std::uint64_t, std::string> objectTypeNameMap; ///< Object serialized data type hash to object serialized data type map.
		std::unordered_map<std::type_index, std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>> objectDeserializers; ///< Object type to object deserializer map.
		std::shared_mutex deserializerMutex; ///< Deserializer mutex.

		CopyComponentDeserializer copyComponentDeserializer;

		std::unordered_map<WorldDefinitionLoadRequest*, std::shared_ptr<WorldDefinitionLoadRequest>> loadRequests; ///< Load requests.
		std::mutex loadRequestsMutex; ///< Load requests mutex.

		std::atomic_size_t requestCount; ///< Request count.

#ifndef NDEBUG
		std::atomic_size_t worldDefinitionResourceCount; ///< World definition resource count.
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free");
	};
}

namespace PonyEngine::Resource::World
{
	WorldDefinitionLoader::WorldDefinitionLoader(Application::IApplication& application) :
		application{&application},
		jobService{&this->application->GetInterface<Job::IJobService>()},
		logService{this->application->FindInterface<Log::ILogService>()}
	{
	}

	WorldDefinitionLoader::~WorldDefinitionLoader() noexcept
	{
		WaitForRequestCountToFinish();

#ifndef NDEBUG
		assert(worldDefinitionResourceCount.load(std::memory_order::relaxed) == 0uz && "Some world definition resources are still alive.");
#endif

		assert(componentTypeMap.size() == 0uz && "Some component deserializers weren't unregistered.");
		assert(objectTypeMap.size() == 0uz && "Some object deserializers weren't unregistered.");
	}

	void WorldDefinitionLoader::PrepareResource(ILoadableResource& context)
	{
		const std::span<const std::type_index> accessTypes = context.DataAccessTypes();
		if (std::ranges::contains(accessTypes, DirectAccessType))
		{
			context.SetDataAccessType(DirectAccessType);
		}
		else if (std::ranges::contains(accessTypes, DefaultAccessType))
		{
			context.SetDataAccessType(DefaultAccessType);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("No supported access type");
		}

		context.AddInterfaceTypes<PonyEngine::World::WorldDefinition>();
	}

	std::shared_ptr<IResourceLoadRequest> WorldDefinitionLoader::Load(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		const std::type_index accessType = context.ResourceDataAccessType();
		if (accessType == DefaultAccessType)
		{
			return MakeDefaultLoadRequest(context, std::move(callback));
		}
		if (accessType == DirectAccessType)
		{
			return MakeDirectLoadRequest(context, std::move(callback));
		}

		throw std::invalid_argument("Invalid access type");
	}

	void WorldDefinitionLoader::RegisterComponentDeserializer(const std::type_index componentType, const std::size_t componentSize, const std::string_view type)
	{
		RegisterComponentDeserializer(componentType, componentSize, type, copyComponentDeserializer);
	}

	void WorldDefinitionLoader::UnregisterComponentDeserializer(const std::type_index componentType, const std::string_view type)
	{
		UnregisterComponentDeserializer(componentType, type, copyComponentDeserializer);
	}

	void WorldDefinitionLoader::RegisterComponentDeserializer(const std::type_index componentType, const std::size_t componentSize, const std::string_view type, 
		IInlineComponentDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			AddComponentDeserializer(componentType, componentSize, type) = &deserializer;
		}

		PONY_LOG(logService, Log::LogType::Info, "Component deserializer registered. Component type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			componentType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::UnregisterComponentDeserializer(const std::type_index componentType, const std::string_view type, IInlineComponentDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			RemoveComponentDeserializer(componentType, type, std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>(&deserializer));
		}

		PONY_LOG(logService, Log::LogType::Info, "Component deserializer unregistered. Component type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			componentType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::RegisterComponentDeserializer(const std::type_index componentType, const std::size_t componentSize,
		const std::string_view type, IComponentDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			AddComponentDeserializer(componentType, componentSize, type) = &deserializer;
		}
		
		PONY_LOG(logService, Log::LogType::Info, "Component deserializer registered. Component type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			componentType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::UnregisterComponentDeserializer(const std::type_index componentType, const std::string_view type,
		IComponentDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			RemoveComponentDeserializer(componentType, type, std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>(&deserializer));
		}
		
		PONY_LOG(logService, Log::LogType::Info, "Component deserializer unregistered. Component type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			componentType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::RegisterObjectDeserializer(const std::type_index objectType, const std::string_view type, IInlineObjectDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			AddObjectDeserializer(objectType, type) = &deserializer;
		}
		
		PONY_LOG(logService, Log::LogType::Info, "Object deserializer registered. Object type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			objectType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::UnregisterObjectDeserializer(const std::type_index objectType, const std::string_view type, IInlineObjectDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			RemoveObjectDeserializer(objectType, type, std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>(&deserializer));
		}
		
		PONY_LOG(logService, Log::LogType::Info, "Object deserializer unregistered. Object type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			objectType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::RegisterObjectDeserializer(const std::type_index objectType, const std::string_view type, IObjectDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			AddObjectDeserializer(objectType, type) = &deserializer;
		}
		
		PONY_LOG(logService, Log::LogType::Info, "Object deserializer registered. Object type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			objectType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	void WorldDefinitionLoader::UnregisterObjectDeserializer(const std::type_index objectType, const std::string_view type, IObjectDeserializer& deserializer)
	{
		{
			const auto lock = std::unique_lock(deserializerMutex);
			RemoveObjectDeserializer(objectType, type, std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>(&deserializer));
		}
		
		PONY_LOG(logService, Log::LogType::Info, "Object deserializer unregistered. Object type: '{}'; Serialized type: '{}'; Deserializer: '0x{:X}'.",
			objectType.name(), type, reinterpret_cast<std::uintptr_t>(&deserializer));
	}

	std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>& WorldDefinitionLoader::AddComponentDeserializer(
		const std::type_index componentType, const std::size_t componentSize, const std::string_view type)
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);

		assert(!componentTypeMap.contains(typeHash) && "Component type with the same hash is already registered.");
		assert(!componentDeserializers.contains(componentType) && "Component type is already registered.");

		componentTypeMap.emplace(typeHash, componentType);
		try
		{
			componentTypeNameMap[typeHash] = type;
			try
			{
				componentSizeMap[componentType] = componentSize;
				try
				{
					return componentDeserializers[componentType] = std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>();
				}
				catch (...)
				{
					componentSizeMap.erase(componentType);
					throw;
				}
			}
			catch (...)
			{
				componentTypeNameMap.erase(typeHash);
				throw;
			}
		}
		catch (...)
		{
			componentTypeMap.erase(typeHash);
			throw;
		}
	}

	void WorldDefinitionLoader::RemoveComponentDeserializer(const std::type_index componentType, const std::string_view type,
		const std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>& deserializer) noexcept
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);

		assert(componentTypeMap.contains(typeHash) && "Component type with the same hash was not registered.");
		assert(componentDeserializers.contains(componentType) && "Component type was not registered.");
		assert(componentTypeMap.find(typeHash)->second == componentType && "Invalid type map.");
		assert(componentDeserializers.find(componentType)->second == deserializer && "Invalid deserializer.");

		componentDeserializers.erase(componentType);
		componentSizeMap.erase(componentType);
		componentTypeNameMap.erase(typeHash);
		componentTypeMap.erase(typeHash);
	}

	std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>& WorldDefinitionLoader::AddObjectDeserializer(const std::type_index objectType, const std::string_view type)
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);

		assert(!objectTypeMap.contains(typeHash) && "Object type with the same hash is already registered.");
		assert(!objectDeserializers.contains(objectType) && "Object type is already registered.");

		objectTypeMap.emplace(typeHash, objectType);
		try
		{
			objectTypeNameMap[typeHash] = type;
			try
			{
				return objectDeserializers[objectType] = std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>();
			}
			catch (...)
			{
				objectTypeNameMap.erase(typeHash);
				throw;
			}
		}
		catch (...)
		{
			objectTypeMap.erase(typeHash);
			throw;
		}
	}

	void WorldDefinitionLoader::RemoveObjectDeserializer(const std::type_index objectType, const std::string_view type,
		const std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>& deserializer) noexcept
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);

		assert(objectTypeMap.contains(typeHash) && "Object type with the same hash was not registered.");
		assert(objectDeserializers.contains(objectType) && "Object type was not registered.");
		assert(objectTypeMap.find(typeHash)->second == objectType && "Invalid type map.");
		assert(objectDeserializers.find(objectType)->second == deserializer && "Invalid deserializer.");

		objectDeserializers.erase(objectType);
		objectTypeNameMap.erase(typeHash);
		objectTypeMap.erase(typeHash);
	}

	std::shared_ptr<IResourceLoadRequest> WorldDefinitionLoader::MakeDefaultLoadRequest(const ILoadContext& context,
		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		auto dataAccess = static_cast<ILoadableDataAccess*>(context.ResourceDataAccess().get());
		const std::size_t size = dataAccess->Size();
		auto data = std::make_shared<std::byte[]>(size);
		const auto buffer = std::span(data.get(), size);
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition = CreateWorldDefinitionResource();
		auto request = std::make_shared<LoadableWorldDefinitionLoadRequest>(std::move(data), size, std::move(worldDefinition), std::move(callback));

		AddRequest(request);
		IncrementRequestCount();

		try
		{
			request->Request(dataAccess->Load(LoadParams{.buffer = buffer}, [this, req = request.get()](const ILoadableDataAccessRequest& accessRequest) noexcept
			{
				switch (accessRequest.Status())
				{
				case Async::RequestStatus::Success: [[likely]]
					if (req->IsCancelRequested()) [[unlikely]]
					{
						CancelRequest(*req);
					}
					else [[likely]]
					{
						Parse(*req);
					}
					break;
				case Async::RequestStatus::Failure:
					{
						std::shared_ptr<WorldDefinitionLoadRequest> loadRequest = RemoveRequest(req);
						loadRequest->AddException(accessRequest.Exception());
						loadRequest->SetFailure();
						loadRequest.reset();
						DecrementRequestCount();
					}
					break;
				case Async::RequestStatus::Canceled:
					{
						std::shared_ptr<WorldDefinitionLoadRequest> loadRequest = RemoveRequest(req);
						loadRequest->SetCanceled();
						loadRequest.reset();
						DecrementRequestCount();
					}
					break;
				default: [[unlikely]]
					assert(false && "Unexpected status");
					break;
				}
			}));
		}
		catch (...)
		{
			RemoveRequest(request.get());
			DecrementRequestCount();
			throw;
		}

		return request;
	}

	std::shared_ptr<IResourceLoadRequest> WorldDefinitionLoader::MakeDirectLoadRequest(const ILoadContext& context,
		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition = CreateWorldDefinitionResource();
		auto dataAccess = static_cast<IMemoryDataAccess*>(context.ResourceDataAccess().get());
		auto request = std::make_shared<WorldDefinitionLoadRequest>(std::move(worldDefinition), dataAccess->Buffer(), std::move(callback));

		AddRequest(request);
		IncrementRequestCount();

		Parse(*request);

		return request;
	}

	std::shared_ptr<PonyEngine::World::WorldDefinition> WorldDefinitionLoader::CreateWorldDefinitionResource()
	{
#ifndef NDEBUG
		const auto resource = new PonyEngine::World::WorldDefinition();
		worldDefinitionResourceCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<PonyEngine::World::WorldDefinition>(resource, [this](const PonyEngine::World::WorldDefinition* const worldDefinition) noexcept
			{
				delete worldDefinition;
				worldDefinitionResourceCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete resource;
			worldDefinitionResourceCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<PonyEngine::World::WorldDefinition>();
#endif
	}

	void WorldDefinitionLoader::AddRequest(const std::shared_ptr<WorldDefinitionLoadRequest>& request)
	{
		const auto lock = std::lock_guard(loadRequestsMutex);
		assert(!loadRequests.contains(request.get()) && "Double request addition.");

		loadRequests[request.get()] = request;
	}

	std::shared_ptr<WorldDefinitionLoadRequest> WorldDefinitionLoader::RemoveRequest(WorldDefinitionLoadRequest* const request) noexcept
	{
		const auto lock = std::lock_guard(loadRequestsMutex);
		const auto position = loadRequests.find(request);
		assert(position != loadRequests.cend() && "Request wasn't added.");

		std::shared_ptr<WorldDefinitionLoadRequest> req = std::move(position->second);
		loadRequests.erase(position);

		return req;
	}

	void WorldDefinitionLoader::IncrementRequestCount() noexcept
	{
		requestCount.fetch_add(1uz, std::memory_order::release);
	}

	void WorldDefinitionLoader::DecrementRequestCount() noexcept
	{
		requestCount.fetch_sub(1uz, std::memory_order::release);
		requestCount.notify_one();
	}

	void WorldDefinitionLoader::WaitForRequestCountToFinish() const noexcept
	{
		for (std::size_t count = requestCount.load(std::memory_order::acquire);
			count > 0uz;
			count = requestCount.load(std::memory_order::acquire))
		{
			requestCount.wait(count, std::memory_order::acquire);
		}
	}

	std::pair<std::type_index, std::size_t> WorldDefinitionLoader::GetComponentInfo(const std::string_view type) const
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);
		if (const auto position = componentTypeMap.find(typeHash); position != componentTypeMap.cend()) [[likely]]
		{
			if (componentTypeNameMap.find(typeHash)->second != type) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}

			return std::pair(position->second, componentSizeMap.find(position->second)->second);
		}

		throw std::invalid_argument("Component type not found");
	}

	const std::variant<IInlineComponentDeserializer*, IComponentDeserializer*>& WorldDefinitionLoader::GetComponentDeserializer(const std::type_index type) const
	{
		return componentDeserializers.find(type)->second;
	}

	std::type_index WorldDefinitionLoader::GetObjectType(const std::string_view type) const
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);
		if (const auto position = objectTypeMap.find(typeHash); position != objectTypeMap.cend()) [[likely]]
		{
			if (componentTypeNameMap.find(typeHash)->second != type) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}

			return position->second;
		}

		throw std::invalid_argument("Object type not found");
	}

	const std::variant<IInlineObjectDeserializer*, IObjectDeserializer*>& WorldDefinitionLoader::GetObjectDeserializer(const std::type_index type) const
	{
		return objectDeserializers.find(type)->second;
	}

	void WorldDefinitionLoader::CancelRequest(WorldDefinitionLoadRequest& request) noexcept
	{
		std::shared_ptr<WorldDefinitionLoadRequest> req = RemoveRequest(&request);
		req->SetCanceled();
		req.reset();
		DecrementRequestCount();
	}

	void WorldDefinitionLoader::FinishRequest(WorldDefinitionLoadRequest& request) noexcept
	{
		std::shared_ptr<WorldDefinitionLoadRequest> req = RemoveRequest(&request);

		if (req->HasException())
		{
			req->SetFailure();
		}
		else if (req->HasCancel())
		{
			req->SetCanceled();
		}
		else
		{
			req->SetSuccess();
		}

		req.reset();
		DecrementRequestCount();
	}

	void WorldDefinitionLoader::Parse(WorldDefinitionLoadRequest& request) noexcept
	{
		try
		{
			jobService->Schedule([this, req = &request]() noexcept
			{
				if (req->IsCancelRequested())
				{
					CancelRequest(*req);
					return;
				}

				try
				{
					const std::byte* input = req->Input().data();
					const std::byte* const inputEnd = input + req->Input().size();
					PonyEngine::World::WorldDefinition& worldDefinition = req->WorldDefinition();

					ValidateDataSize(input, inputEnd, sizeof(std::size_t) * 3uz);
					const std::size_t entityCount = ReadData<std::size_t>(input);
					const std::size_t componentTableCount = ReadData<std::size_t>(input);
					const std::size_t objectCount = ReadData<std::size_t>(input);
					worldDefinition.entityCount = entityCount;
					worldDefinition.components.reserve(componentTableCount);
					worldDefinition.objects.reserve(objectCount);

					req->SetMaxJobCount(componentTableCount + objectCount);

					ValidateDataSize(input, inputEnd, componentTableCount + sizeof(std::size_t) * componentTableCount + objectCount + 
						sizeof(std::size_t) * componentTableCount + sizeof(std::size_t) * objectCount);
					const std::span<const std::uint8_t> componentTableTypeLengths = ReadDataSpan<std::uint8_t>(input, componentTableCount);
					const std::byte* componentEntityCounts = MoveData(input, sizeof(std::size_t) * componentTableCount);
					const std::span<const std::uint8_t> objectTypeLengths = ReadDataSpan<std::uint8_t>(input, objectCount);
					const std::byte* componentDataSizes = MoveData(input, sizeof(std::size_t) * componentTableCount);
					const std::byte* objectDataSizes = MoveData(input, sizeof(std::size_t) * objectCount);
					const std::size_t componentTypeLengthSum = Sum(componentTableTypeLengths);
					const std::size_t componentEntityCount = Sum(componentEntityCounts, componentTableCount);
					const std::size_t objectTypeLengthSum = Sum(objectTypeLengths);
					const std::size_t componentDataSum = Sum(componentDataSizes, componentTableCount);
					const std::size_t objectDataSum = Sum(objectDataSizes, objectCount);

					ValidateDataSize(input, inputEnd, componentTypeLengthSum + sizeof(std::size_t) * componentEntityCount + objectTypeLengthSum + 
						componentDataSum + objectDataSum);
					const std::byte* componentTypes = MoveData(input, componentTypeLengthSum);
					const std::byte* componentEntities = MoveData(input, sizeof(std::size_t) * componentEntityCount);
					const std::byte* objectTypes = MoveData(input, objectTypeLengthSum);
					const std::byte* componentData = MoveData(input, componentDataSum);
					const std::byte* objectData = MoveData(input, objectDataSum);

					{
						const auto lock = std::shared_lock(deserializerMutex);

						for (std::size_t i = 0uz; i < componentTableCount; ++i)
						{
							const std::string_view type = ReadDataString(componentTypes, componentTableTypeLengths[i]);
							const auto [componentType, componentSize] = GetComponentInfo(type);
							if (worldDefinition.components.contains(componentType)) [[unlikely]]
							{
								throw std::runtime_error("Same component type found twice");
							}

							const std::size_t tableEntityCount = ReadData<std::size_t>(componentEntityCounts);
							const std::size_t tableDataSize = componentSize * tableEntityCount;
							PonyEngine::World::ComponentTableDefinition& tableDefinition = worldDefinition.components[componentType] = PonyEngine::World::ComponentTableDefinition
							{
								.entityBindings = std::vector<std::size_t>(tableEntityCount),
								.data = std::vector<std::byte>(tableDataSize)
							};
							ReadData<std::size_t>(componentEntities, tableDefinition.entityBindings);

							const std::size_t tableInputSize = ReadData<std::size_t>(componentDataSizes);
							const std::span<const std::byte> tableInput = ReadDataSpan<const std::byte>(componentData, tableInputSize);

							std::visit(Utility::Overload
							{
								[&](IInlineComponentDeserializer* const deserializer)
								{
									deserializer->Deserialize(tableInput, tableDefinition.data);
								},
								[&](IComponentDeserializer* const deserializer)
								{
									req->IncrementJobCount();
									try
									{
										req->AddDeserializationRequest(deserializer->Deserialize(tableInput, tableDefinition.data, [this, r = req](const IWorldDeserializationRequest& dataRequest) noexcept
										{
											switch (dataRequest.Status())
											{
											case Async::RequestStatus::Success:
												break;
											case Async::RequestStatus::Failure:
												r->AddExceptions(dataRequest.Exceptions());
												break;
											case Async::RequestStatus::Canceled:
												r->IncrementCancelCount();
												break;
											default: [[unlikely]]
												assert(false && "Unexpected status");
												break;
											}

											if (r->DecrementJobCount())
											{
												FinishRequest(*r);
											}
										}));
									}
									catch (...)
									{
										req->DecrementJobCount();
										throw;
									}
								}
							}, GetComponentDeserializer(componentType));
						}

						for (std::size_t i = 0uz; i < objectCount; ++i)
						{
							const std::string_view type = ReadDataString(objectTypes, objectTypeLengths[i]);
							const std::type_index objectType = GetObjectType(type);
							worldDefinition.objects.push_back(std::pair(objectType, std::shared_ptr<void>()));

							const std::size_t objectInputSize = ReadData<std::size_t>(objectDataSizes);
							const std::span<const std::byte> objectInput = ReadDataSpan<const std::byte>(objectData, objectInputSize);

							std::shared_ptr<void>& target = worldDefinition.objects.back().second;
							std::visit(Utility::Overload
							{
								[&](IInlineObjectDeserializer* const deserializer)
								{
									deserializer->Deserialize(objectInput, target);
								},
								[&](IObjectDeserializer* deserializer)
								{
									req->IncrementJobCount();
									try
									{
										req->AddDeserializationRequest(deserializer->Deserialize(objectInput, target, [this, r = req](const IWorldDeserializationRequest& dataRequest) noexcept
										{
											switch (dataRequest.Status())
											{
											case Async::RequestStatus::Success:
												break;
											case Async::RequestStatus::Failure:
												r->AddExceptions(dataRequest.Exceptions());
												break;
											case Async::RequestStatus::Canceled:
												r->IncrementCancelCount();
												break;
											default: [[unlikely]]
												assert(false && "Unexpected status");
												break;
											}

											if (r->DecrementJobCount())
											{
												FinishRequest(*r);
											}
										}));
									}
									catch (...)
									{
										req->DecrementJobCount();
										throw;
									}
								}
							}, GetObjectDeserializer(objectType));
						}
					}

					if (req->DecrementJobCount())
					{
						FinishRequest(*req);
					}
				}
				catch (...)
				{
					req->AddException(std::current_exception());
					if (req->DecrementJobCount())
					{
						FinishRequest(*req);
					}
				}
			}, Job::JobParams{.priority = Job::JobPriority::Low});
		}
		catch (...)
		{
			request.AddException(std::current_exception());
			FinishRequest(request);
		}
	}

	void WorldDefinitionLoader::ValidateDataSize(const std::byte* const input, const std::byte* const inputEnd, const std::size_t requiredSize)
	{
		if (static_cast<std::size_t>(inputEnd - input) < requiredSize) [[unlikely]]
		{
			throw std::runtime_error("Unexpected input end");
		}
	}

	const std::byte* WorldDefinitionLoader::MoveData(const std::byte*& input, const std::size_t count) noexcept
	{
		const std::byte* data = input;
		input += count;

		return data;
	}

	template<typename T>
	T WorldDefinitionLoader::ReadData(const std::byte*& input) noexcept
	{
		if constexpr (sizeof(T) == 1)
		{
			return static_cast<T>(*input++);
		}
		else
		{
			T data;
			std::memcpy(&data, input, sizeof(T));
			input += sizeof(T);

			return data;
		}
	}

	template<typename T>
	void WorldDefinitionLoader::ReadData(const std::byte*& input, std::span<T> data) noexcept
	{
		const std::size_t copySize = data.size_bytes();
		std::memcpy(data.data(), input, copySize);
		input += copySize;
	}

	template<typename T>
	std::span<const T> WorldDefinitionLoader::ReadDataSpan(const std::byte*& input, std::size_t count) noexcept requires (sizeof(T) == 1)
	{
		const auto span = std::span<const T>(reinterpret_cast<const T*>(input), count);
		input += count;

		return span;
	}

	std::string_view WorldDefinitionLoader::ReadDataString(const std::byte*& input, const std::size_t count) noexcept
	{
		const auto string = std::string_view(reinterpret_cast<const char*>(input), count);
		input += count;

		return string;
	}

	template<std::unsigned_integral T>
	std::size_t WorldDefinitionLoader::Sum(const std::span<const T> data) noexcept
	{
		std::size_t sum = 0uz;
		for (const T element : data)
		{
			sum += static_cast<std::size_t>(element);
		}

		return sum;
	}

	std::size_t WorldDefinitionLoader::Sum(const std::byte* data, const std::size_t count) noexcept
	{
		std::size_t sum = 0u;
		for (std::size_t i = 0uz; i < count; ++i, data += sizeof(std::size_t))
		{
			std::size_t value;
			std::memcpy(&value, data, sizeof(std::size_t));
			sum += value;
		}

		return sum;
	}
}
