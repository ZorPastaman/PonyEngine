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

export module PonyEngine.Resource.Pack.Impl:PackService;

import std;

import PonyEngine.Application;
import PonyEngine.Async;
import PonyEngine.File;
import PonyEngine.Job;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Resource.Pack;

import :DataAccessFactory;
import :FilePackMountRequest;
import :LoadableDataAccessRequestWorker;
import :PackContainer;
import :PackMountRequest;
import :PackUnmountRequest;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack resource provider.
	class PackService final : public IPackService
	{
	public:
		/// @brief Creates a pack service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit PackService(Application::IApplication& application);
		PackService(const PackService&) = delete;
		PackService(PackService&&) = delete;

		~PackService() noexcept;

		virtual std::shared_ptr<IPackMountRequest> MountPack(std::filesystem::path packManifestPath, std::filesystem::path packDataPath, AccessType accessType,
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) override;
		virtual std::shared_ptr<IPackMountRequest> MountPack(std::span<const std::byte> packManifest, std::span<const std::byte> packData, AccessType accessType,
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) override;
		virtual std::shared_ptr<IPackUnmountRequest> UnmountPack(PackHandle packHandle, std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback) override;

		PackService& operator =(const PackService&) = delete;
		PackService& operator =(PackService&&) = delete;

	private:
		/// @brief Manifest resource.
		struct ManifestResource final
		{
			std::size_t typeIndex; ///< Resource type index.
			std::size_t dataMetaIndex; ///< Resource data meta index.
			std::size_t loadMetaIndex; ////< Resouce load meta index.
			std::size_t rangeIndex; ///< Resource data range index.
		};

		/// @brief Checks if the @p packHandle is valid.
		/// @param packHandle Pack handle to check.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValid(PackHandle packHandle) const noexcept;
		/// @brief Creates a pack handle.
		/// @return Pack handle.
		[[nodiscard("Must be used")]]
		PackHandle CreatePackHandle();
		/// @brief Makes a new pack handle.
		/// @return Pack handle.
		[[nodiscard("Must be used")]]
		PackHandle MakePackHandle();
		/// @brief Resurrects a pack handle.
		/// @return Pack handle.
		[[nodiscard("Must be used")]]
		PackHandle ResurrectPackHandle() noexcept;
		/// @brief Kills the pack handle.
		/// @param packHandle Pack handle to kill.
		void KillPackHandle(PackHandle packHandle) noexcept;

		/// @brief Creates a pack mount request.
		/// @param accessType Access type.
		/// @param manifest Pack manifest.
		/// @param manifestSize Pack manifest size.
		/// @param dataBuffer Pack data. If it's nullptr, the request count will be 1, otherwise it'll be 2.
		/// @param dataSize Pack data size.
		/// @param callback Callback.
		/// @return Pack mount request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<PackMountRequest> CreatePackMountRequest(AccessType accessType, const std::byte* manifest, std::size_t manifestSize, 
			std::shared_ptr<std::byte[]> dataBuffer, std::size_t dataSize, std::move_only_function<void(const IPackMountRequest&) noexcept> callback);
		/// @brief Creates a file pack mount request.
		/// @param manifestFile Manifest file.
		/// @param dataFile Data file.
		/// @param accessType Access type.
		/// @param manifestBuffer Manifest buffer.
		/// @param manifestSize Manifest size in bytes.
		/// @param dataBuffer Data buffer.
		/// @param dataSize Data size in bytes.
		/// @param callback Request callback.
		/// @return File pack mount request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<FilePackMountRequest> CreateFilePackMountRequest(std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, 
			AccessType accessType, std::unique_ptr<std::byte[]> manifestBuffer, std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer, std::size_t dataSize,
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback);
		/// @brief Creates a pack unmount request.
		/// @param packHandle Pack handle.
		/// @param callback Callback.
		/// @return Pack unmount request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<PackUnmountRequest> CreatePackUnmountRequest(PackHandle packHandle, std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback);

		/// @brief Adds the mount request.
		/// @param request Mount request to add.
		void AddMountRequest(const std::shared_ptr<PackMountRequest>& request);
		/// @brief Removes the mount request.
		/// @param request Mount request to remove.
		/// @return Removed mounted request.
		std::shared_ptr<PackMountRequest> RemoveMountRequest(PackMountRequest* request) noexcept;

		/// @brief Checks if the request is canceled and process canceling if needed.
		/// @param request Request to check.
		/// @return @a True if the request isn't canceled and the caller may proceed its operations; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool CheckCancel(PackMountRequest* request);

		/// @brief Adds a manifest parse task.
		/// @param request Mount request that has a manifest to parse.
		void ParseManifest(PackMountRequest& request) noexcept;
		/// @brief Validates that the manifest has enough data.
		/// @param manifest Current manifest pointer.
		/// @param manifestEnd Manifest end pointer.
		/// @param requiredSize Required size.
		static void ValidateManifestSize(const std::byte* manifest, const std::byte* manifestEnd, std::size_t requiredSize);
		/// @brief Checks the manifest data. Moves the pointer if the check passes.
		/// @tparam T Data type.
		/// @param manifest Manifest pointer.
		/// @param data Data to check.
		/// @param error Error message in case of a failure.
		template<typename T>
		static void CheckManifestData(const std::byte*& manifest, std::span<const T> data, std::string_view error);
		/// @brief Moves the manifest pointer.
		/// @param manifest Current manifest pointer.
		/// @param count How many bytes to skip.
		/// @return Previous pointer.
		static const std::byte* MoveManifestData(const std::byte*& manifest, std::size_t count) noexcept;
		/// @brief Reads the manifest data and moves the pointer.
		/// @tparam T Manifest data type.
		/// @param manifest Manifest.
		/// @return Manifest data.
		template<typename T>
		static T ReadManifestData(const std::byte*& manifest) noexcept;
		/// @brief Reads the manifest data as a span and moves the pointer.
		/// @tparam T Manifest data type.
		/// @param manifest Manifest.
		/// @param count Manifest data count.
		/// @return Manifest data span.
		template<typename T>
		static std::span<const T> ReadManifestSpan(const std::byte*& manifest, std::size_t count) noexcept requires (sizeof(T) == 1);
		/// @brief Reads the manifest data as a string and moves the pointer.
		/// @param manifest Manifest.
		/// @param count Manifest data count.
		/// @return Manifest data string.
		[[nodiscard("Pure function")]]
		static std::string_view ReadManifestString(const std::byte*& manifest, std::size_t count) noexcept;
		/// @brief Sums the data.
		/// @tparam T Data type.
		/// @param data Data.
		/// @param count Data count.
		/// @return Sum.
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		static std::size_t SumManifestData(const std::byte* data, std::size_t count) noexcept;

		/// @brief Adds a pack creation task.
		/// @param request Mount task.
		void CreatePack(PackMountRequest& request) noexcept;

		/// @brief Adds the unmount request.
		/// @param request Unmount request to add.
		void AddUnmountRequest(const std::shared_ptr<PackUnmountRequest>& request);
		/// @brief Removes the unmount request.
		/// @param request Unmount request to remove.
		/// @return Removed request.
		std::shared_ptr<PackUnmountRequest> RemoveUnmountRequest(PackUnmountRequest* request) noexcept;

		/// @brief Increment the ongoing request count.
		void IncrementOngoingRequestCount() const noexcept;
		/// @brief Decrement the ongoing request count.
		void DecrementOngoingRequestCount() const noexcept;
		/// @brief Wait till the ongoing request count reaches 0.
		void WaitForOngoingRequestCountToFinish() const noexcept;

		static constexpr std::string_view MagicWord = "PonyEngineResourcePackManifest"; ///< Pack manifest magic word.

		Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.
		IResourceHub* resourceHub; ///< Resource hub.
		File::IFileService* fileService; ///< File service.
		Job::IJobService* jobService; ///< Job service.

		LoadableDataAccessRequestWorker loadableDataAccessRequestWorker; ///< Loadable data access request worker.
		DataAccessFactory dataAccessFactory; ///< Data access factory.

		PackContainer packContainer; ///< Pack container.
		std::vector<PackVersion> packVersions; ///< Pack versions.
		std::vector<PackID> deadPackIds; ///< Dead pack IDs.

		mutable std::shared_mutex stateMutex; ///< Service state mutex.

		std::unordered_map<PackMountRequest*, std::shared_ptr<PackMountRequest>> mountRequests; ///< Mount requests.
		std::mutex mountRequestMutex; ///< Mount request mutex.

		std::unordered_map<PackUnmountRequest*, std::shared_ptr<PackUnmountRequest>> unmountRequests; ///< Unmount requests.
		std::mutex unmountRequestMutex; ///< Unmount request mutex.

		mutable std::atomic_size_t ongoingRequestCount; ///< Ongoing request count.

#ifndef NDEBUG
		std::atomic_size_t requestCount; ///< Request count.
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};
}

namespace PonyEngine::Resource::Pack
{
	PackService::PackService(Application::IApplication& application) :
#ifndef NDEBUG
		requestCount(0uz),
#endif
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		resourceHub{&this->application->GetInterface<IResourceHub>()},
		fileService{&this->application->GetInterface<File::IFileService>()},
		jobService{&this->application->GetInterface<Job::IJobService>()},
		loadableDataAccessRequestWorker(this->application->GetInterface<Job::IJobService>()),
		dataAccessFactory(loadableDataAccessRequestWorker),
		ongoingRequestCount(0uz)
	{
	}

	PackService::~PackService() noexcept
	{
		WaitForOngoingRequestCountToFinish();

#ifndef NDEBUG
		assert(requestCount.load(std::memory_order::relaxed) == 0uz && "Some mount/unmount requests are still alive.");
#endif

		for (std::size_t i = packContainer.Size(); i-- > 0uz; )
		{
			try
			{
				resourceHub->UnregisterCollection(packContainer.Pack(i), packContainer.Collection(i));
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering collection. Pack: '0x{:X}'; Collection: '0x{:X}'.",
					packContainer.Handle(i), packContainer.Collection(i).id);
			}
		}
	}

	std::shared_ptr<IPackMountRequest> PackService::MountPack(std::filesystem::path packManifestPath, std::filesystem::path packDataPath, const AccessType accessType,
		std::move_only_function<void(const IPackMountRequest&) noexcept> callback)
	{
		if (None(AccessType::Loadable | AccessType::File | AccessType::Memory, accessType)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid access type");
		}

		if (packManifestPath.is_relative())
		{
			packManifestPath = application->RootDirectory() / packManifestPath;
		}
		if (packDataPath.is_relative())
		{
			packDataPath = application->RootDirectory() / packDataPath;
		}

		std::shared_ptr<File::IFile> manifest = fileService->OpenFile(std::move(packManifestPath), File::FileParams::Read());
		std::shared_ptr<File::IFile> data = fileService->OpenFile(std::move(packDataPath), File::FileParams::Read());
		const bool loadedData = Any(AccessType::Memory, accessType);
		const std::size_t manifestSize = std::filesystem::file_size(manifest->Path());
		auto manifestBuffer = std::make_unique<std::byte[]>(manifestSize);
		const std::size_t dataSize = std::filesystem::file_size(data->Path());
		std::shared_ptr<std::byte[]> dataBuffer = loadedData ? std::make_shared<std::byte[]>(dataSize) : nullptr;
		auto request = CreateFilePackMountRequest(std::move(manifest), std::move(data), accessType,
			std::move(manifestBuffer), manifestSize, std::move(dataBuffer), dataSize, std::move(callback));
		AddMountRequest(request);
		IncrementOngoingRequestCount();

		try
		{
			request->ManifestReadRequest(request->ManifestFile()->Read(File::ReadParams{.buffer = request->ManifestTarget()}, [this, req = request.get()](const File::IReadRequest& readRequest) noexcept
			{
				switch (readRequest.Status())
				{
				case Async::RequestStatus::Success: [[likely]]
					if (CheckCancel(req)) [[likely]]
					{
						ParseManifest(*req);
					}
					break;
				case Async::RequestStatus::Failure:
					req->ManifestException(readRequest.Exception());
					if (req->DecrementRequestCount()) [[likely]]
					{
						std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetFailure(req->ManifestException());
						mountRequest.reset();
						DecrementOngoingRequestCount();
					}
					break;
				case Async::RequestStatus::Canceled:
					if (req->DecrementRequestCount()) [[likely]]
					{
						std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
						if (mountRequest->HasDataException()) [[unlikely]]
						{
							mountRequest->SetFailure(req->DataException());
						}
						else [[likely]]
						{
							mountRequest->SetCanceled();
						}
						mountRequest.reset();
						DecrementOngoingRequestCount();
					}
					break;
				default: [[unlikely]]
					assert(false && "Unexpected read request status.");
					break;
				}
			}));
		}
		catch (...)
		{
			RemoveMountRequest(request.get());
			DecrementOngoingRequestCount();
			throw;
		}

		if (loadedData)
		{
			try
			{
				request->DataReadRequest(request->DataFile()->Read(File::ReadParams{.buffer = request->Data()}, [this, req = request.get()](const File::IReadRequest& readRequest) noexcept
				{
					switch (readRequest.Status())
					{
					case Async::RequestStatus::Success: [[likely]]
						if (CheckCancel(req)) [[likely]]
						{
							if (req->DecrementRequestCount()) [[likely]]
							{
								CreatePack(*req);
							}
						}
						break;
					case Async::RequestStatus::Failure:
						req->DataException(readRequest.Exception());
						if (req->DecrementRequestCount()) [[likely]]
						{
							std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
							mountRequest->SetFailure(req->HasManifestException() ? req->ManifestException() : req->DataException());
							mountRequest.reset();
							DecrementOngoingRequestCount();
						}
						break;
					case Async::RequestStatus::Canceled:
						if (req->DecrementRequestCount())
						{
							std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
							if (mountRequest->HasManifestException()) [[unlikely]]
							{
								mountRequest->SetFailure(mountRequest->ManifestException());
							}
							else [[likely]]
							{
								mountRequest->SetCanceled();
							}
							mountRequest.reset();
							DecrementOngoingRequestCount();
						}
						break;
					default: [[unlikely]]
						assert(false && "Unexpected read request status.");
						break;
					}
				}));
			}
			catch (...)
			{
				request->DataException(std::current_exception());
				if (request->DecrementRequestCount())
				{
					std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(request.get());
					mountRequest->SetFailure(request->HasManifestException() ? request->ManifestException() : request->DataException());
					mountRequest.reset();
					DecrementOngoingRequestCount();
				}
			}
		}

		return request;
	}

	std::shared_ptr<IPackMountRequest> PackService::MountPack(const std::span<const std::byte> packManifest, const std::span<const std::byte> packData, const AccessType accessType,
		std::move_only_function<void(const IPackMountRequest&) noexcept> callback)
	{
		if (!packManifest.data()) [[unlikely]]
		{
			throw std::invalid_argument("Manifest is nullptr");
		}
		if (!packData.data()) [[unlikely]]
		{
			throw std::invalid_argument("Data is nullptr");
		}
		if (None(AccessType::Loadable | AccessType::Memory, accessType) || Any(AccessType::File, accessType)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid access type");
		}

		auto dataBuffer = std::make_shared<std::byte[]>(packData.size());

		auto request = CreatePackMountRequest(accessType, packManifest.data(), packManifest.size(), std::move(dataBuffer), packData.size(), std::move(callback));
		AddMountRequest(request);
		IncrementOngoingRequestCount();

		try
		{
			jobService->Schedule([this, req = request.get(), src = packData.data()]() noexcept
			{
				if (!CheckCancel(req)) [[unlikely]]
				{
					return;
				}

				const std::span<std::byte> data = req->Data();
				std::memcpy(data.data(), src, data.size());

				if (CheckCancel(req)) [[likely]]
				{
					if (req->DecrementRequestCount()) [[likely]]
					{
						CreatePack(*req);
					}
				}
			});
		}
		catch (...)
		{
			RemoveMountRequest(request.get());
			DecrementOngoingRequestCount();
			throw;
		}

		ParseManifest(*request);

		return request;
	}

	std::shared_ptr<IPackUnmountRequest> PackService::UnmountPack(const PackHandle packHandle, std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback)
	{
		auto request = CreatePackUnmountRequest(packHandle, std::move(callback));
		AddUnmountRequest(request);

		try
		{
			jobService->Schedule([this, req = request.get()]() noexcept
			{
				if (req->IsCancelRequested()) [[unlikely]]
				{
					const std::shared_ptr<PackUnmountRequest> unmountRequest = RemoveUnmountRequest(req);
					unmountRequest->SetCanceled();
					return;
				}

				try
				{
					const auto lock = std::unique_lock(stateMutex);
					if (!IsValid(req->Pack())) [[unlikely]]
					{
						throw std::invalid_argument("Pack handle is invalid");
					}

					const PackHandle packHandle = req->Pack();
					const std::size_t index = packContainer.IndexOf(packHandle.id);
					assert(index < packContainer.Size() && "Invalid pack handle.");
					resourceHub->UnregisterCollection(packContainer.Pack(index), packContainer.Collection(index));
					packContainer.Remove(index);
					KillPackHandle(packHandle);
				}
				catch (...)
				{
					const std::shared_ptr<PackUnmountRequest> unmountRequest = RemoveUnmountRequest(req);
					unmountRequest->SetFailure(std::current_exception());
				}

				const std::shared_ptr<PackUnmountRequest> unmountRequest = RemoveUnmountRequest(req);
				unmountRequest->SetSuccess();
			});
		}
		catch (...)
		{
			RemoveUnmountRequest(request.get());
			throw;
		}

		return request;
	}

	bool PackService::IsValid(const PackHandle packHandle) const noexcept
	{
		return Math::IsOdd(packHandle.version) && packHandle.id < packVersions.size() && packVersions[packHandle.id] == packHandle.version;
	}

	PackHandle PackService::CreatePackHandle()
	{
		return deadPackIds.empty() ? MakePackHandle() : ResurrectPackHandle();
	}

	PackHandle PackService::MakePackHandle()
	{
		if (packVersions.size() >= std::numeric_limits<PackID>::max()) [[unlikely]]
		{
			throw std::overflow_error("No more pack ID available");
		}

		const PackID packID = static_cast<PackID>(packVersions.size());

		constexpr PackID packVersion = 1u;
		packVersions.push_back(packVersion);

		return PackHandle{.id = packID, .version = packVersion};
	}

	PackHandle PackService::ResurrectPackHandle() noexcept
	{
		const PackID packId = deadPackIds.back();
		deadPackIds.pop_back();

		const PackVersion packVersion = ++packVersions[packId];

		return PackHandle{.id = packId, .version = packVersion};
	}

	void PackService::KillPackHandle(const PackHandle packHandle) noexcept
	{
		try
		{
			++packVersions[packHandle.id];
			deadPackIds.push_back(packHandle.id);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On killing pack handle. ID: '0x{:X}'.", packHandle.id);
			// Just forget about this pack handle.
		}
	}

	std::shared_ptr<PackMountRequest> PackService::CreatePackMountRequest(const AccessType accessType,
		const std::byte* const manifest, const std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer,
		const std::size_t dataSize, std::move_only_function<void(const IPackMountRequest&) noexcept> callback)
	{
#ifndef NDEBUG
		const auto request = new PackMountRequest(accessType, manifest, manifestSize, std::move(dataBuffer), dataSize, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<PackMountRequest>(request, [this](const PackMountRequest* const req) noexcept
			{
				delete req;
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete request;
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<PackMountRequest>(accessType, manifest, manifestSize, std::move(dataBuffer), dataSize, std::move(callback));
#endif
	}

	std::shared_ptr<FilePackMountRequest> PackService::CreateFilePackMountRequest(std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, 
		const AccessType accessType, std::unique_ptr<std::byte[]> manifestBuffer, const std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer,
		const std::size_t dataSize, std::move_only_function<void(const IPackMountRequest&) noexcept> callback)
	{
#ifndef NDEBUG
		const auto request = new FilePackMountRequest(std::move(manifestFile), std::move(dataFile), accessType,
			std::move(manifestBuffer), manifestSize, std::move(dataBuffer), dataSize, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<FilePackMountRequest>(request, [this](const FilePackMountRequest* const req) noexcept
			{
				delete req;
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete request;
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<FilePackMountRequest>(std::move(manifestFile), std::move(dataFile), accessType,
			std::move(manifestBuffer), manifestSize, std::move(dataBuffer), dataSize, std::move(callback));
#endif
	}

	std::shared_ptr<PackUnmountRequest> PackService::CreatePackUnmountRequest(const PackHandle packHandle,
		std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback)
	{
#ifndef NDEBUG
		const auto request = new PackUnmountRequest(packHandle, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<PackUnmountRequest>(request, [this](const PackUnmountRequest* const req) noexcept
			{
				delete req;
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete request;
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<PackUnmountRequest>(packHandle, std::move(callback));
#endif
	}

	void PackService::AddMountRequest(const std::shared_ptr<PackMountRequest>& request)
	{
		const auto lock = std::lock_guard(mountRequestMutex);
		assert(!mountRequests.contains(request.get()) && "Double request addition.");

		mountRequests[request.get()] = request;
	}

	std::shared_ptr<PackMountRequest> PackService::RemoveMountRequest(PackMountRequest* const request) noexcept
	{
		const auto lock = std::lock_guard(mountRequestMutex);
		const auto position = mountRequests.find(request);
		assert(position != mountRequests.cend() && "Request wasn't added.");

		std::shared_ptr<PackMountRequest> req = std::move(position->second);
		mountRequests.erase(position);

		return req;
	}

	bool PackService::CheckCancel(PackMountRequest* const request)
	{
		if (request->IsCancelRequested()) [[unlikely]]
		{
			if (request->DecrementRequestCount()) [[likely]]
			{
				std::shared_ptr<PackMountRequest> req = RemoveMountRequest(request);
				req->SetCanceled();
				req.reset();
				DecrementOngoingRequestCount();
			}

			return false;
		}

		return true;
	}

	void PackService::ParseManifest(PackMountRequest& request) noexcept
	{
		try
		{
			jobService->Schedule([this, req = &request]() noexcept
			{
				if (!CheckCancel(req)) [[unlikely]]
				{
					return;
				}

				try
				{
					const std::span<const std::byte> manifestBuffer = req->Manifest();
					const std::byte* manifest = manifestBuffer.data();
					const std::byte* const manifestEnd = manifestBuffer.data() + manifestBuffer.size();

					ValidateManifestSize(manifest, manifestEnd, MagicWord.size() + 5uz * sizeof(std::size_t));
					CheckManifestData<char>(manifest, MagicWord, "Manifest doesn't have valid magic word");
					const std::size_t typeCount = ReadManifestData<std::size_t>(manifest);
					const std::size_t dataMetaCount = ReadManifestData<std::size_t>(manifest);
					const std::size_t loadMetaCount = ReadManifestData<std::size_t>(manifest);
					const std::size_t rangeCount = ReadManifestData<std::size_t>(manifest);

					const std::size_t typeSizeSize = typeCount * sizeof(std::uint8_t);
					const std::size_t dataMetaSizeSize = dataMetaCount * sizeof(std::size_t);
					const std::size_t loadMetaSizeSize = loadMetaCount * sizeof(std::size_t);
					const std::size_t rangeSize = rangeCount * sizeof(std::pair<std::size_t, std::size_t>);
					const std::size_t infoCountSize = typeSizeSize + dataMetaSizeSize + loadMetaSizeSize + rangeSize;
					ValidateManifestSize(manifest, manifestEnd, infoCountSize);
					const std::byte* const typeSizes = MoveManifestData(manifest, typeSizeSize);
					const std::byte* const dataMetaSizes = MoveManifestData(manifest, dataMetaSizeSize);
					const std::byte* const loadMetaSizes = MoveManifestData(manifest, loadMetaSizeSize);
					const std::byte* const ranges = MoveManifestData(manifest, rangeSize);

					const std::size_t totalTypeSize = SumManifestData<std::uint8_t>(typeSizes, typeCount);
					const std::size_t totalDataMetaSize = SumManifestData<std::size_t>(dataMetaSizes, dataMetaCount);
					const std::size_t totalLoadMetaSize = SumManifestData<std::size_t>(loadMetaSizes, loadMetaCount);
					const std::size_t totalInfoSize = totalTypeSize + totalDataMetaSize + totalLoadMetaSize;
					ValidateManifestSize(manifest, manifestEnd, totalInfoSize);
					const std::byte* const types = MoveManifestData(manifest, totalTypeSize);
					const std::byte* const dataMetas = MoveManifestData(manifest, totalDataMetaSize);
					const std::byte* const loadMetas = MoveManifestData(manifest, totalLoadMetaSize);

					const std::size_t tempBufferSize = Memory::CalculateBufferSize<ResourceType>(typeCount) +
						Memory::CalculateBufferSize<std::span<const std::byte>, ResourceType>(dataMetaCount) +
						Memory::CalculateBufferSize<std::span<const std::byte>, std::span<const std::byte>>(loadMetaCount);
					const std::shared_ptr<Application::IBuffer> tempBuffer = application->CreateBuffer(tempBufferSize);
					auto tempArena = Memory::Arena(tempBuffer->Span());

					const std::span<ResourceType> resourceTypes = tempArena.AllocateArray<ResourceType>(typeCount);
					const std::byte* typeSize = typeSizes;
					const std::byte* type = types;
					for (ResourceType& resourceType : resourceTypes)
					{
						const std::uint8_t size = ReadManifestData<std::uint8_t>(typeSize);
						const std::string_view typeString = ReadManifestString(type, size);
						resourceType = resourceHub->MakeResourceType(typeString);
					}

					const std::span<std::span<const std::byte>> resourceDataMetas = tempArena.AllocateArray<std::span<const std::byte>>(dataMetaCount);
					const std::byte* dataMetaSize = dataMetaSizes;
					const std::byte* dataMeta = dataMetas;
					for (std::span<const std::byte>& resourceDataMeta : resourceDataMetas)
					{
						const std::size_t size = ReadManifestData<std::size_t>(dataMetaSize);
						resourceDataMeta = ReadManifestSpan<std::byte>(dataMeta, size);
					}

					const std::span<std::span<const std::byte>> resourceLoadMetas = tempArena.AllocateArray<std::span<const std::byte>>(loadMetaCount);
					const std::byte* loadMetaSize = loadMetaSizes;
					const std::byte* loadMeta = loadMetas;
					for (std::span<const std::byte>& resourceLoadMeta : resourceLoadMetas)
					{
						const auto size = ReadManifestData<std::size_t>(loadMetaSize);
						resourceLoadMeta = ReadManifestSpan<std::byte>(loadMeta, size);
					}

					std::vector<std::pair<std::size_t, std::size_t>>& reqRanges = req->Ranges();
					reqRanges.resize(rangeCount);
					std::memcpy(reqRanges.data(), ranges, rangeSize);
					for (const auto [offset, size] : reqRanges)
					{
						if (Math::SumClamp(offset, size) >= req->DataSize()) [[unlikely]]
						{
							throw std::runtime_error("Invalid manifest data range");
						}
					}

					std::vector<CollectionResource>& collectionResources = req->CollectionResources();
					while (manifest < manifestEnd)
					{
						ValidateManifestSize(manifest, manifestEnd, sizeof(ManifestResource) + sizeof(std::uint8_t));
						const ManifestResource manifestResource = ReadManifestData<ManifestResource>(manifest);
						const std::uint8_t idSize = ReadManifestData<std::uint8_t>(manifest);
						ValidateManifestSize(manifest, manifestEnd, idSize);
						const std::string_view id = ReadManifestString(manifest, idSize);

						if (manifestResource.typeIndex >= typeCount) [[unlikely]]
						{
							throw std::runtime_error("Invalid manifest resource type index");
						}
						if (manifestResource.dataMetaIndex >= dataMetaCount) [[unlikely]]
						{
							throw std::runtime_error("Invalid manifest resource data meta index");
						}
						if (manifestResource.loadMetaIndex >= loadMetaCount) [[unlikely]]
						{
							throw std::runtime_error("Invalid manifest resource load meta index");
						}
						if (manifestResource.rangeIndex >= rangeCount) [[unlikely]]
						{
							throw std::runtime_error("Invalid manifest resource range index");
						}

						collectionResources.push_back(CollectionResource
						{
							.id = resourceHub->MakeResourceID(id),
							.type = resourceTypes[manifestResource.typeIndex],
							.dataMeta = resourceDataMetas[manifestResource.dataMetaIndex],
							.loadMeta = resourceLoadMetas[manifestResource.loadMetaIndex],
							.dataIndex = manifestResource.rangeIndex
						});
					}
					collectionResources.shrink_to_fit();
				}
				catch (...)
				{
					req->ManifestException(std::current_exception());
					if (req->DecrementRequestCount())
					{
						std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetFailure(req->ManifestException());
						mountRequest.reset();
						DecrementOngoingRequestCount();
					}
				}

				if (CheckCancel(req)) [[likely]]
				{
					if (req->DecrementRequestCount()) [[likely]]
					{
						CreatePack(*req);
					}
				}
			});
		}
		catch (...)
		{
			request.ManifestException(std::current_exception());
			if (request.DecrementRequestCount())
			{
				std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(&request);
				mountRequest->SetFailure(request.ManifestException());
				mountRequest.reset();
				DecrementOngoingRequestCount();
			}
		}
	}

	void PackService::ValidateManifestSize(const std::byte* const manifest, const std::byte* const manifestEnd, const std::size_t requiredSize)
	{
		if (static_cast<std::size_t>(manifestEnd - manifest) < requiredSize) [[unlikely]]
		{
			throw std::runtime_error("Unexpected manifest end");
		}
	}

	const std::byte* PackService::MoveManifestData(const std::byte*& manifest, const std::size_t count) noexcept
	{
		const std::byte* const prev = manifest;
		manifest += count;

		return prev;
	}

	template<typename T>
	void PackService::CheckManifestData(const std::byte*& manifest, const std::span<const T> data, const std::string_view error)
	{
		const std::size_t sizeBytes = data.size_bytes();

		if (std::memcmp(manifest, data.data(), sizeBytes)) [[unlikely]]
		{
			throw std::runtime_error(error.data());
		}

		manifest += sizeBytes;
	}

	template<typename T>
	T PackService::ReadManifestData(const std::byte*& manifest) noexcept
	{
		if constexpr (sizeof(T) == 1)
		{
			return static_cast<T>(*manifest++);
		}
		else
		{
			T data;
			std::memcpy(&data, manifest, sizeof(T));
			manifest += sizeof(T);

			return data;
		}
	}

	template<typename T>
	std::span<const T> PackService::ReadManifestSpan(const std::byte*& manifest, const std::size_t count) noexcept requires (sizeof(T) == 1)
	{
		const auto span = std::span<const T>(reinterpret_cast<const T*>(manifest), count);
		manifest += count;

		return span;
	}

	template<std::unsigned_integral T>
	std::size_t PackService::SumManifestData(const std::byte* data, const std::size_t count) noexcept
	{
		std::size_t sum = 0uz;
		for (std::size_t i = 0uz; i < count; ++i, data += sizeof(T))
		{
			if constexpr (sizeof(T) == 1)
			{
				sum += static_cast<T>(*data);
			}
			else
			{
				T value;
				std::memcpy(&value, data, sizeof(T));
				sum += value;
			}
		}

		return sum;
	}

	std::string_view PackService::ReadManifestString(const std::byte*& manifest, const std::size_t count) noexcept
	{
		const auto string = std::string_view(reinterpret_cast<const char*>(manifest), count);
		manifest += count;

		return string;
	}

	void PackService::CreatePack(PackMountRequest& request) noexcept
	{
		try
		{
			jobService->Schedule([this, req = &request]() noexcept
			{
				if (!CheckCancel(req)) [[unlikely]]
				{
					return;
				}

				try
				{
					const bool isFileSource = req->IsFileSource();
					const auto fileReq = isFileSource ? static_cast<FilePackMountRequest*>(req) : nullptr;

					std::filesystem::path dataFilePath = Any(AccessType::File, req->AccessType())
						? fileReq->DataFile()->Path()
						: std::filesystem::path();
					std::shared_ptr<File::IFile> dataFile = isFileSource && Any(AccessType::Loadable, req->AccessType()) && None(AccessType::Memory, req->AccessType())
						? fileReq->DataFile()
						: nullptr;
					std::shared_ptr<std::byte[]> loadedData = Any(AccessType::Memory, req->AccessType()) 
						? req->DataBuffer() 
						: nullptr;

					auto pack = std::make_shared<class Pack>(dataAccessFactory, std::move(dataFilePath), std::move(dataFile),
						std::move(loadedData), std::move(req->Ranges()));

					std::vector<std::type_index> accessTypes;
					accessTypes.reserve(3uz);
					if (Any(AccessType::Loadable, req->AccessType()))
					{
						accessTypes.push_back(typeid(ILoadableDataAccess));
					}
					if (Any(AccessType::File, req->AccessType()))
					{
						accessTypes.push_back(typeid(IFileDataAccess));
					}
					if (Any(AccessType::Memory, req->AccessType()))
					{
						accessTypes.push_back(typeid(IMemoryDataAccess));
					}

					const ResourceCollection collection = resourceHub->RegisterCollection(*pack, req->CollectionResources(), accessTypes);

					try
					{
						const auto lock = std::unique_lock(stateMutex);
						const PackHandle packHandle = CreatePackHandle();
						
						try
						{
							packContainer.Add(packHandle.id, collection, std::move(pack));
						}
						catch (...)
						{
							KillPackHandle(packHandle);
							throw;
						}

						std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetSuccess(packHandle);
						mountRequest.reset();
						DecrementOngoingRequestCount();
					}
					catch (...)
					{
						resourceHub->UnregisterCollection(*pack, collection);
						throw;
					}
				}
				catch (...)
				{
					req->ManifestException(std::current_exception());
					std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
					mountRequest->SetFailure(req->ManifestException());
					mountRequest.reset();
					DecrementOngoingRequestCount();
				}
			});
		}
		catch (...)
		{
			request.ManifestException(std::current_exception());
			std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(&request);
			mountRequest->SetFailure(request.ManifestException());
			mountRequest.reset();
			DecrementOngoingRequestCount();
		}
	}

	void PackService::AddUnmountRequest(const std::shared_ptr<PackUnmountRequest>& request)
	{
		const auto lock = std::lock_guard(unmountRequestMutex);
		assert(!unmountRequests.contains(request.get()) && "Double request addition.");

		unmountRequests[request.get()] = request;
	}

	std::shared_ptr<PackUnmountRequest> PackService::RemoveUnmountRequest(PackUnmountRequest* const request) noexcept
	{
		const auto lock = std::lock_guard(unmountRequestMutex);
		const auto position = unmountRequests.find(request);
		assert(position != unmountRequests.cend() && "Request wasn't added.");

		std::shared_ptr<PackUnmountRequest> req = std::move(position->second);
		unmountRequests.erase(position);

		return req;
	}

	void PackService::IncrementOngoingRequestCount() const noexcept
	{
		ongoingRequestCount.fetch_add(1uz, std::memory_order::release);
	}

	void PackService::DecrementOngoingRequestCount() const noexcept
	{
		ongoingRequestCount.fetch_sub(1uz, std::memory_order::release);
		ongoingRequestCount.notify_one();
	}

	void PackService::WaitForOngoingRequestCountToFinish() const noexcept
	{
		for (std::size_t requestCount = ongoingRequestCount.load(std::memory_order::acquire);
			requestCount > 0uz;
			requestCount = ongoingRequestCount.load(std::memory_order::acquire))
		{
			ongoingRequestCount.wait(requestCount, std::memory_order::acquire);
		}
	}
}
