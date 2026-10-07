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

export module PonyEngine.Resource.World.Impl:WorldDefinitionLoader;

import std;

import PonyEngine.Application;
import PonyEngine.Job;
import PonyEngine.Memory;
import PonyEngine.Resource.Ext;
import PonyEngine.World;

import :DefaultWorldDefinitionLoadRequest;
import :WorldDefinitionLoadRequest;

export namespace PonyEngine::Resource::World
{
	class WorldDefinitionLoader final : public IResourceLoader
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit WorldDefinitionLoader(Application::IApplication& application);
		WorldDefinitionLoader(const WorldDefinitionLoader&) = delete;
		WorldDefinitionLoader(WorldDefinitionLoader&&) = delete;

		~WorldDefinitionLoader() noexcept = default;

		virtual void PrepareResource(ILoadableResource& context) override;
		[[nodiscard("Weird call")]] 
		virtual std::shared_ptr<IResourceLoadRequest> Load(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) override;

		WorldDefinitionLoader& operator =(const WorldDefinitionLoader&) = delete;
		WorldDefinitionLoader& operator =(WorldDefinitionLoader&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceLoadRequest> MakeDefaultLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);
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

		[[nodiscard("Pure function")]]
		std::type_index GetComponentType(std::string_view type) const;
		[[nodiscard("Pure function")]]
		std::size_t GetComponentSize(std::type_index type) const;
		[[nodiscard("Pure function")]]
		std::type_index GetObjectType(std::string_view type) const;

		void Parse(WorldDefinitionLoadRequest& request);
		static void ValidateDataSize(const std::byte* input, const std::byte* inputEnd, std::size_t requiredSize);
		static const std::byte* MoveData(const std::byte*& input, std::size_t count) noexcept;
		template<typename T>
		static T ReadData(const std::byte*& input) noexcept;
		template<typename T>
		static void ReadData(const std::byte*& input, std::span<T> data) noexcept;
		template<typename T>
		static std::span<const T> ReadDataSpan(const std::byte*& input, std::size_t count) noexcept requires (sizeof(T) == 1);
		[[nodiscard("Pure function")]]
		static std::string_view ReadDataString(const std::byte*& input, std::size_t count) noexcept;
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		static std::size_t Sum(std::span<const T> data) noexcept;
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		static T Sum(const std::byte* data, std::size_t count) noexcept;

		inline static const std::type_index DefaultAccessType = typeid(ILoadableDataAccess); ///< Default data access type.
		inline static const std::type_index DirectAccessType = typeid(IMemoryDataAccess); ///< Direct data access type.

		Application::IApplication* application;
		Job::IJobService* jobService;

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
		jobService{&this->application->GetInterface<Job::IJobService>()}
	{
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

	std::shared_ptr<IResourceLoadRequest> WorldDefinitionLoader::MakeDefaultLoadRequest(const ILoadContext& context,
		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		auto dataAccess = static_cast<ILoadableDataAccess*>(context.ResourceDataAccess().get());
		const std::size_t size = dataAccess->Size();
		auto data = std::make_shared<std::byte[]>(size);
		const auto buffer = std::span(data.get(), size);
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition = CreateWorldDefinitionResource();
		auto request = std::make_shared<DefaultWorldDefinitionLoadRequest>(std::move(data), size, std::move(worldDefinition), std::move(callback));

		AddRequest(request);
		IncrementRequestCount();

		try
		{
			request->Request(dataAccess->Load(LoadParams{.buffer = buffer}, [this, req = request.get()](const ILoadableDataAccessRequest& accessRequest) noexcept
			{
				switch (accessRequest.Status())
				{
				case Async::RequestStatus::Success: [[likely]]
					Parse(*req);
					break;
				case Async::RequestStatus::Failure:
					{
						std::shared_ptr<WorldDefinitionLoadRequest> loadRequest = RemoveRequest(req);
						loadRequest->SetException(accessRequest.Exception());
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

		try
		{
			Parse(*request);
		}
		catch (...)
		{
			RemoveRequest(request.get());
			DecrementRequestCount();
			throw;
		}

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

	void WorldDefinitionLoader::Parse(WorldDefinitionLoadRequest& request)
	{
		jobService->Schedule([this, req = &request]() noexcept
		{
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

				ValidateDataSize(input, inputEnd, componentTableCount + sizeof(std::size_t) * componentTableCount + objectCount + 
					sizeof(std::size_t) * componentTableCount + sizeof(std::size_t) * objectCount);
				const std::span<const std::uint8_t> componentTableTypeLengths = ReadDataSpan<std::uint8_t>(input, componentTableCount);
				const std::byte* componentEntityCounts = MoveData(input, sizeof(std::size_t) * componentTableCount);
				const std::span<const std::uint8_t> objectTypeLengths = ReadDataSpan<std::uint8_t>(input, objectCount);
				const std::byte* componentDataSizes = MoveData(input, sizeof(std::size_t) * componentTableCount);
				const std::byte* objectDataSizes = MoveData(input, sizeof(std::size_t) * objectCount);
				const std::size_t componentTypeLengthSum = Sum(componentTableTypeLengths);
				const std::size_t componentEntityCount = Sum<std::size_t>(componentEntityCounts, componentTableCount);
				const std::size_t objectTypeLengthSum = Sum(objectTypeLengths);
				const std::size_t componentDataSum = Sum<std::size_t>(componentDataSizes, componentTableCount);
				const std::size_t objectDataSum = Sum<std::size_t>(objectDataSizes, objectCount);

				ValidateDataSize(input, inputEnd, componentTypeLengthSum + sizeof(std::size_t) * componentEntityCount + objectTypeLengthSum + 
					componentDataSum + objectDataSum);
				const std::byte* componentTypes = MoveData(input, componentTypeLengthSum);
				const std::byte* componentEntities = MoveData(input, sizeof(std::size_t) * componentEntityCount);
				const std::byte* objectTypes = MoveData(input, objectTypeLengthSum);
				const std::byte* componentData = MoveData(input, componentDataSum);
				const std::byte* objectData = MoveData(input, objectDataSum);

				for (std::size_t i = 0uz; i < componentTableCount; ++i)
				{
					const std::string_view type = ReadDataString(componentTypes, componentTableTypeLengths[i]);
					const std::type_index componentType = GetComponentType(type);
					if (worldDefinition.components.contains(componentType)) [[unlikely]]
					{
						throw std::runtime_error("Same component type found twice");
					}

					const std::size_t tableEntityCount = ReadData<std::size_t>(componentEntityCounts);
					const std::size_t tableDataSize = GetComponentSize(componentType) * tableEntityCount;
					PonyEngine::World::ComponentTableDefinition& tableDefinition = worldDefinition.components[componentType] = PonyEngine::World::ComponentTableDefinition
					{
						.entityBindings = std::vector<std::size_t>(tableEntityCount),
						.data = std::vector<std::byte>(tableDataSize)
					};
					ReadData<std::size_t>(componentEntities, tableDefinition.entityBindings);

					// TODO: Make a component load request
				}

				for (std::size_t i = 0uz; i < objectCount; ++i)
				{
					const std::string_view type = ReadDataString(objectTypes, objectTypeLengths[i]);
					const std::type_index objectType = GetObjectType(type);
					worldDefinition.objects.push_back(std::pair(objectType, std::shared_ptr<void>()));

					// TODO: Make an object load request
				}
			}
			catch (...)
			{
				// TODO: SetException
			}
		}, Job::JobParams{.priority = Job::JobPriority::Low});
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

	template<std::unsigned_integral T>
	T WorldDefinitionLoader::Sum(const std::byte* data, const std::size_t count) noexcept
	{
		T sum = 0u;
		for (std::size_t i = 0uz; i < count; ++i, data += sizeof(T))
		{
			T value;
			std::memcpy(&value, data, sizeof(T));
			sum += value;
		}

		return sum;
	}

	std::string_view WorldDefinitionLoader::ReadDataString(const std::byte*& input, const std::size_t count) noexcept
	{
		const auto string = std::string_view(reinterpret_cast<const char*>(input), count);
		input += count;

		return string;
	}
}
