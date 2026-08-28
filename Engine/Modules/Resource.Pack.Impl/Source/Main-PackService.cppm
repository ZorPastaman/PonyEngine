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
import PonyEngine.File;
import PonyEngine.Job;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Resource.Pack;

import :FileDataAccess;
import :FileLoadableDataAccess;
import :FilePackMountRequest;
import :LoadableDataAccessRequestWorker;
import :MemoryDataAccess;
import :PackContainer;
import :PackMountRequest;

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

		virtual std::shared_ptr<IPackMountRequest> MountPack(std::filesystem::path packPath, AccessType accessType, 
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) override;
		virtual std::shared_ptr<IPackMountRequest> MountPack(std::span<const std::byte> packManifest, std::span<const std::byte> packData, AccessType accessType,
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) override;
		virtual std::shared_ptr<IPackUnmountRequest> UnmountPack(PackHandle packHandle) override;

		PackService& operator =(const PackService&) = delete;
		PackService& operator =(PackService&&) = delete;

	private:
		static constexpr std::string_view PackManifestExtension = ".prpm";
		static constexpr std::string_view PackDataExtension = ".prpd";
		static constexpr std::string_view MagicWord = "PonyEngineRPM";

		struct ManifestResource final
		{
			std::size_t typeIndex;
			std::size_t dataMetaIndex;
			std::size_t loadMetaIndex;
			std::size_t rangeIndex;
		};

		[[nodiscard("Must be used")]]
		PackHandle CreatePackHandle();
		[[nodiscard("Must be used")]]
		PackHandle MakePackHandle();
		[[nodiscard("Must be used")]]
		PackHandle ResurrectPackHandle() noexcept;
		void KillPackHandle(PackHandle packHandle) noexcept;

		[[nodiscard("Must be used")]]
		PackHandle AddPack(ResourceCollection collection, const std::shared_ptr<Pack>& pack);
		void RemovePack(PackHandle packHandle);

		void AddMountRequest(const std::shared_ptr<PackMountRequest>& request);
		std::shared_ptr<PackMountRequest> RemoveMountRequest(PackMountRequest* request);
		[[nodiscard("Pure function")]]
		bool CheckCancel(PackMountRequest* request);

		void ParseManifest(PackMountRequest& request) noexcept;
		static void ValidateManifestSize(const std::byte* manifest, const std::byte* manifestEnd, std::size_t requiredSize);
		template<typename T>
		static void CheckManifestData(const std::byte*& manifest, std::span<const T> data, std::string_view error);
		static const std::byte* MoveManifestData(const std::byte*& manifest, std::size_t count) noexcept;
		template<typename T>
		static T ReadManifestData(const std::byte*& manifest) noexcept;
		template<typename T>
		static std::span<const T> ReadManifestSpan(const std::byte*& manifest, std::size_t count) noexcept requires (sizeof(T) == 1);
		[[nodiscard("Pure function")]]
		static std::string_view ReadManifestString(const std::byte*& manifest, std::size_t count) noexcept;
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		static std::size_t SumManifestData(const std::byte* data, std::size_t count) noexcept;

		void CreatePack(PackMountRequest& request) noexcept;

		Application::IApplication* application;
		const Log::ILogService* logService;
		IResourceHub* resourceHub;
		File::IFileService* fileService;
		Job::IJobService* jobService;

		LoadableDataAccessRequestWorker loadableDataAccessRequestWorker;

		PackContainer packContainer;
		std::vector<PackVersion> packVersions;
		std::vector<PackID> deadPackIds;

		mutable std::shared_mutex stateMutex;

		std::unordered_map<FilePackMountRequest*, std::shared_ptr<FilePackMountRequest>> mountRequests;
		std::mutex mountRequestMutex;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackService::PackService(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		resourceHub{&this->application->GetInterface<IResourceHub>()},
		fileService{&this->application->GetInterface<File::IFileService>()},
		jobService{&this->application->GetInterface<Job::IJobService>()},
		loadableDataAccessRequestWorker(this->application->GetInterface<Job::IJobService>())
	{
	}

	PackService::~PackService() noexcept
	{
		for (std::size_t i = packContainer.Size(); i-- > 0uz; )
		{
			try
			{
				resourceHub->UnregisterCollection(packContainer.Pack(i), packContainer.Collection(i));
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering collection. Pack: '0x{:X}'; Collection: '0x{:X}'.",
					packContainer.Handle(i).id, packContainer.Collection(i).id);
			}
		}

		packContainer.Clear();
	}

	std::shared_ptr<IPackMountRequest> PackService::MountPack(std::filesystem::path packPath, const AccessType accessType)
	{
		if (packPath.extension() != PackManifestExtension) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pack path");
		}
		if (None(AccessType::Loadable | AccessType::File | AccessType::Memory, accessType)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid access type");
		}

		if (packPath.is_relative())
		{
			packPath = application->RootDirectory() / packPath;
		}

		const std::shared_ptr<File::IFile> manifest = fileService->OpenFile(packPath, File::FileParams::Read());
		const std::shared_ptr<File::IFile> data = fileService->OpenFile(packPath.stem() / PackDataExtension, File::FileParams::Read());
		const bool loadedData = Any(AccessType::Memory, accessType);
		const std::shared_ptr<Application::IBuffer> manifestBuffer = application->CreateBuffer(std::filesystem::file_size(manifest->Path()));
		const std::size_t dataFileSize = std::filesystem::file_size(data->Path());
		const std::shared_ptr<Application::IBuffer> dataBuffer = loadedData ? application->CreateBuffer(dataFileSize) : nullptr;
		const auto request = std::make_shared<FilePackMountRequest>(accessType, manifest, data, dataFileSize, manifestBuffer, dataBuffer);
		AddMountRequest(request);

		try
		{
			request->SetManifestRequest(manifest->Read(File::ReadParams{.buffer = manifestBuffer->Span()}, [this, req = request.get()](const File::IReadRequest& readRequest) noexcept
			{
				switch (readRequest.Status())
				{
				case File::FileRequestStatus::Success:
					if (req->IsCancelRequested())
					{
						if (req->DecrementRequestCount() == 1uz)
						{
							const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
							mountRequest->SetCanceled();
						}
					}
					else
					{
						ParseManifest(*req);
					}
					break;
				case File::FileRequestStatus::Failure:
					req->ManifestException(readRequest.Exception());
					if (req->DecrementRequestCount() == 1uz)
					{
						const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetFailure(req->ManifestException());
					}
					break;
				case File::FileRequestStatus::Canceled:
					if (req->DecrementRequestCount() == 1uz)
					{
						const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetCanceled();
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
			throw;
		}

		if (loadedData)
		{
			// TODO: Data load request.
		}

		return request;
	}

	std::shared_ptr<IPackMountRequest> PackService::MountPack(const std::span<const std::byte> packManifest, const std::span<const std::byte> packData, const AccessType accessType,
		std::move_only_function<void(const IPackMountRequest&) noexcept> callback)
	{
		if (None(AccessType::Loadable | AccessType::Memory, accessType) || Any(AccessType::File, accessType)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid access type");
		}

		auto dataBuffer = std::make_shared<std::byte[]>(packData.size());

		auto request = std::make_shared<PackMountRequest>(accessType, packManifest, std::move(dataBuffer), packData.size(), std::move(callback));
		AddMountRequest(request);

		try
		{
			jobService->Schedule([this, req = request.get(), src = packData.data()]() noexcept
			{
				if (CheckCancel(req))
				{
					const std::span<std::byte> data = req->Data();
					std::memcpy(data.data(), src, data.size());

					if (CheckCancel(req))
					{
						if (req->DecrementRequestCount())
						{
							CreatePack(*req);
						}
					}
				}
			});
		}
		catch (...)
		{
			RemoveMountRequest(request.get());
			throw;
		}

		ParseManifest(*request);

		return request;
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

	PackHandle PackService::AddPack(const ResourceCollection collection, const std::shared_ptr<Pack>& pack)
	{
		const auto lock = std::unique_lock(stateMutex);

		const PackHandle packHandle = CreatePackHandle();
		packContainer.Add(packHandle, collection, pack);

		return packHandle;
	}

	void PackService::RemovePack(const PackHandle packHandle)
	{
		const auto lock = std::unique_lock(stateMutex);

		const std::size_t index = packContainer.IndexOf(packHandle);
		if (index >= packContainer.Size()) [[unlikely]]
		{
			throw std::out_of_range("Index out of range");
		}

		packContainer.Remove(index);
	}

	bool PackService::CheckCancel(PackMountRequest* const request)
	{
		if (request->IsCancelRequested())
		{
			if (request->DecrementRequestCount())
			{
				const std::shared_ptr<PackMountRequest> req = RemoveMountRequest(request);
				req->SetCanceled();
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
				if (CheckCancel(req))
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
					const std::size_t resourceCount = ReadManifestData<std::size_t>(manifest);

					const std::size_t typeSizeSize = typeCount * sizeof(std::uint8_t);
					const std::size_t dataMetaSizeSize = dataMetaCount * sizeof(std::size_t);
					const std::size_t loadMetaSizeSize = loadMetaCount * sizeof(std::size_t);
					const std::size_t rangeSize = rangeCount * sizeof(std::pair<std::size_t, std::size_t>);
					const std::size_t idSizeSize = resourceCount * sizeof(std::uint8_t);
					const std::size_t infoCountSize = typeSizeSize + dataMetaSizeSize + loadMetaSizeSize + rangeSize + idSizeSize;
					ValidateManifestSize(manifest, manifestEnd, infoCountSize);
					const std::byte* const typeSizes = MoveManifestData(manifest, typeSizeSize);
					const std::byte* const dataMetaSizes = MoveManifestData(manifest, dataMetaSizeSize);
					const std::byte* const loadMetaSizes = MoveManifestData(manifest, loadMetaSizeSize);
					const std::byte* const ranges = MoveManifestData(manifest, rangeSize);
					const std::byte* const idSizes = MoveManifestData(manifest, idSizeSize);

					const std::size_t totalTypeSize = SumManifestData<std::uint8_t>(typeSizes, typeCount);
					const std::size_t totalDataMetaSize = SumManifestData<std::size_t>(dataMetaSizes, dataMetaCount);
					const std::size_t totalLoadMetaSize = SumManifestData<std::size_t>(loadMetaSizes, loadMetaCount);
					const std::size_t totalIdSize = SumManifestData<std::uint8_t>(idSizes, resourceCount);
					const std::size_t resourceSize = resourceCount * sizeof(ManifestResource);
					const std::size_t totalInfoSize = totalTypeSize + totalDataMetaSize + totalLoadMetaSize + totalIdSize + resourceSize);
					ValidateManifestSize(manifest, manifestEnd, totalInfoSize);
					const std::byte* const types = MoveManifestData(manifest, totalTypeSize);
					const std::byte* const dataMetas = MoveManifestData(manifest, totalDataMetaSize);
					const std::byte* const loadMetas = MoveManifestData(manifest, totalLoadMetaSize);
					const std::byte* const ids = MoveManifestData(manifest, totalIdSize);
					const std::byte* const resources = MoveManifestData(manifest, resourceSize);
					PONY_LOG_IF(manifest != manifestEnd, logService, Log::LogType::Warning, "Resource pack manifest read operation hasn't reached the end. Maybe, manifest is invalid.")

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

					const std::byte* idSize = idSizes;
					const std::byte* id = ids;
					const std::byte* resource = resources;
					std::vector<CollectionResource>& collectionResources = req->CollectionResources();
					collectionResources.resize(resourceCount);
					for (CollectionResource& collectionResource : collectionResources)
					{
						const ManifestResource manifestResource = ReadManifestData<ManifestResource>(resource);
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

						const std::uint8_t resourceIdSize = ReadManifestData<std::uint8_t>(idSize);
						const std::string_view resourceId = ReadManifestString(id, resourceIdSize);

						collectionResource = CollectionResource
						{
							.id = resourceHub->MakeResourceID(resourceId),
							.type = resourceTypes[manifestResource.typeIndex],
							.dataMeta = resourceDataMetas[manifestResource.dataMetaIndex],
							.loadMeta = resourceLoadMetas[manifestResource.loadMetaIndex],
							.dataIndex = manifestResource.rangeIndex
						};
					}
				}
				catch (...)
				{
					req->ManifestException(std::current_exception());
					if (req->DecrementRequestCount())
					{
						const std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetFailure(req->ManifestException());
					}
				}

				if (CheckCancel(req))
				{
					if (req->DecrementRequestCount())
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
				const std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(&request);
				mountRequest->SetFailure(request.ManifestException());
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
			return static_cast<T>(manifest++);
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
				if (CheckCancel(req))
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

					const auto pack = std::make_shared<class Pack>(loadableDataAccessRequestWorker, std::move(dataFilePath), std::move(dataFile),
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
						const PackHandle packHandle = AddPack(collection, pack);
						const std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetSuccess(packHandle);
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
					const std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(req);
					mountRequest->SetFailure(req->ManifestException());
				}
			});
		}
		catch (...)
		{
			request.ManifestException(std::current_exception());
			const std::shared_ptr<PackMountRequest> mountRequest = RemoveMountRequest(&request);
			mountRequest->SetFailure(request.ManifestException());
		}
	}
}
