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
import :LoadableDataAccessRequestWorker;
import :MemoryDataAccess;
import :PackContainer;
import :FilePackMountRequest;

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

		[[nodiscard("Pure function")]] 
		virtual std::size_t PackCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual PackHandle Pack(std::size_t index) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsValid(PackHandle packHandle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const ResourceInfo> Resources(PackHandle packHandle) const override;

		virtual std::shared_ptr<IPackMountRequest> MountPack(const std::filesystem::path& packPath, AccessType accessType) override;
		virtual std::shared_ptr<IPackMountRequest> MountPack(std::span<const std::byte> packManifest, std::span<const std::byte> packData, AccessType accessType) override;
		virtual std::shared_ptr<IPackUnmountRequest> UnmountPack(PackHandle packHandle) override;

		PackService& operator =(const PackService&) = delete;
		PackService& operator =(PackService&&) = delete;

	private:
		static constexpr std::string_view PackManifestExtension = ".prpm";
		static constexpr std::string_view PackDataExtension = ".prpd";
		static constexpr std::string_view MagicWord = "PonyEngineRPM";

		[[nodiscard("Must be used")]]
		PackHandle CreatePackHandle();
		[[nodiscard("Must be used")]]
		PackHandle MakePackHandle();
		[[nodiscard("Must be used")]]
		PackHandle ResurrectPackHandle() noexcept;
		void KillPackHandle(PackHandle packHandle) noexcept;

		[[nodiscard("Must be used")]]
		PackHandle AddPack(ResourceCollection collection, const std::shared_ptr<class Pack>& pack, std::span<const ResourceInfo> resourceInfos);
		void RemovePack(PackHandle packHandle);

		void AddMountRequest(const std::shared_ptr<FilePackMountRequest>& request);
		std::shared_ptr<FilePackMountRequest> RemoveMountRequest(FilePackMountRequest* request);
		void ParseManifest(FilePackMountRequest& request) noexcept;
		void CreatePack(FilePackMountRequest& request) noexcept;

		Application::IApplication* application;
		Log::ILogService* logService;
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

	std::size_t PackService::PackCount() const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);
		return packContainer.Size();
	}

	PackHandle PackService::Pack(const std::size_t index) const
	{
		const auto lock = std::shared_lock(stateMutex);

		if (index >= packContainer.Size()) [[unlikely]]
		{
			throw std::out_of_range("Index out of range");
		}

		return packContainer.Handle(index);
	}

	bool PackService::IsValid(const PackHandle packHandle) const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);
		return Math::IsOdd(packHandle.version) && packHandle.id < packVersions.size() && packHandle.version == packVersions[packHandle.id];
	}

	std::span<const ResourceInfo> PackService::Resources(const PackHandle packHandle) const
	{
		const auto lock = std::shared_lock(stateMutex);

		const std::size_t index = packContainer.IndexOf(packHandle);
		if (index >= packContainer.Size()) [[unlikely]]
		{
			throw std::out_of_range("Index out of range");
		}

		return packContainer.ResourceInfos(index);
	}

	std::shared_ptr<IPackMountRequest> PackService::MountPack(const std::filesystem::path& packPath, const AccessType accessType)
	{
		if (packPath.extension() != PackManifestExtension) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pack path");
		}
		if (None(AccessType::Loadable | AccessType::File | AccessType::Memory, accessType)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid access type");
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

	PackHandle PackService::AddPack(const ResourceCollection collection, const std::shared_ptr<class Pack>& pack, const std::span<const ResourceInfo> resourceInfos)
	{
		const auto lock = std::unique_lock(stateMutex);

		const PackHandle packHandle = CreatePackHandle();
		packContainer.Add(packHandle, collection, pack, resourceInfos);

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

	void PackService::ParseManifest(FilePackMountRequest& request) noexcept
	{
		try
		{
			jobService->Schedule([this, req = &request]() noexcept
			{
				if (req->IsCancelRequested())
				{
					if (req->DecrementRequestCount() == 1uz)
					{
						const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetCanceled();
					}

					return;
				}

				try
				{
					const std::span<const std::byte> manifestBuffer = req->ManifestBuffer();
					const std::byte* manifest = manifestBuffer.data();
					const std::byte* const manifestBufferEnd = manifestBuffer.data() + manifestBuffer.size();

					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < MagicWord.size()) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					if (std::memcmp(manifest, MagicWord.data(), MagicWord.size())) [[unlikely]]
					{
						throw std::runtime_error("Manifest doesn't have valid magic word");
					}
					manifest += MagicWord.size();

					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < sizeof(std::size_t) * 4uz) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					constexpr std::size_t typeCountIndex = 0uz;
					constexpr std::size_t dataMetaCountIndex = 1uz;
					constexpr std::size_t loadMetaCountIndex = 2uz;
					constexpr std::size_t resourceCountIndex = 3uz;
					std::array<std::size_t, 4uz> mainCounts;
					std::memcpy(mainCounts.data(), manifest, sizeof(std::size_t) * 4uz);
					manifest += sizeof(std::size_t) * 4uz;

					const std::size_t tempBufferSize = Memory::CalculateBufferSize<ResourceType>(mainCounts[typeCountIndex]) +
						Memory::CalculateBufferSize<std::span<const std::byte>, ResourceType>(mainCounts[dataMetaCountIndex]) +
						Memory::CalculateBufferSize<std::span<const std::byte>, std::span<const std::byte>>(mainCounts[loadMetaCountIndex]);
					const std::shared_ptr<Application::IBuffer> tempBuffer = application->CreateBuffer(tempBufferSize);
					auto tempArena = Memory::Arena(tempBuffer->Span());

					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < mainCounts[typeCountIndex]) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					const auto typeSizes = std::span(reinterpret_cast<const std::uint8_t*>(manifest), mainCounts[typeCountIndex]);
					manifest += mainCounts[typeCountIndex];

					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < std::ranges::fold_left(typeSizes, 0uz, std::plus<std::size_t>())) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					const std::span<ResourceType> resourceTypes = tempArena.AllocateArray<ResourceType>(mainCounts[typeCountIndex]);
					for (std::size_t i = 0uz; i < resourceTypes.size(); ++i)
					{
						resourceTypes[i] = resourceHub->MakeResourceType(std::string_view(reinterpret_cast<const char*>(manifest), typeSizes[i]));
						manifest += typeSizes[i];
					}

					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < mainCounts[dataMetaCountIndex] * sizeof(std::size_t)) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					const std::byte* dataMetaSize = manifest;
					manifest += mainCounts[dataMetaCountIndex] * sizeof(std::size_t);
					const std::span<std::span<const std::byte>> dataMetas = tempArena.AllocateArray<std::span<const std::byte>>(mainCounts[dataMetaCountIndex]);
					for (std::size_t i = 0uz; i < dataMetas.size(); ++i)
					{
						std::size_t size;
						std::memcpy(&size, dataMetaSize, sizeof(std::size_t));
						dataMetaSize += sizeof(std::size_t);
						if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < size) [[unlikely]]
						{
							throw std::runtime_error("Unexpected manifest end");
						}
						dataMetas[i] = std::span(manifest, size);
						manifest += size;
					}

					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < mainCounts[loadMetaCountIndex] * sizeof(std::size_t)) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					const std::byte* loadMetaSize = manifest;
					manifest += mainCounts[loadMetaCountIndex] * sizeof(std::size_t);
					const std::span<std::span<const std::byte>> loadMetas = tempArena.AllocateArray<std::span<const std::byte>>(mainCounts[loadMetaCountIndex]);
					for (std::size_t i = 0uz; i < loadMetas.size(); ++i)
					{
						std::size_t size;
						std::memcpy(&size, loadMetaSize, sizeof(std::size_t));
						loadMetaSize += sizeof(std::size_t);
						if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < size) [[unlikely]]
						{
							throw std::runtime_error("Unexpected manifest end");
						}
						loadMetas[i] = std::span(manifest, size);
						manifest += size;
					}

					const std::size_t resourceBufferSize = Memory::CalculateBufferSize<std::pair<std::size_t, std::size_t>>(mainCounts[resourceCountIndex]) +
						Memory::CalculateBufferSize<CollectionResource, std::pair<std::size_t, std::size_t>>(mainCounts[resourceCountIndex]);
					const std::shared_ptr<Application::IBuffer> resourceBuffer = application->CreateBuffer(resourceBufferSize);
					auto resourceArena = Memory::Arena(resourceBuffer->Span());

					const std::span<std::pair<std::size_t, std::size_t>> ranges = resourceArena.AllocateArray<std::pair<std::size_t, std::size_t>>(mainCounts[resourceCountIndex]);
					if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < ranges.size_bytes()) [[unlikely]]
					{
						throw std::runtime_error("Unexpected manifest end");
					}
					std::memcpy(ranges.data(), manifest, ranges.size_bytes());
					manifest += ranges.size_bytes();
					for (const auto [offset, size] : ranges)
					{
						if (Math::SumClamp(offset, size) > req->DataFileSize()) [[unlikely]]
						{
							throw std::runtime_error("Invalid data range");
						}
					}

					const std::span<CollectionResource> resources = resourceArena.AllocateArray<CollectionResource>(mainCounts[resourceCountIndex]);
					for (std::size_t i = 0uz; i < resources.size(); ++i)
					{
						if (manifest >= manifestBufferEnd) [[unlikely]]
						{
							throw std::runtime_error("Unexpected manifest end");
						}
						const std::uint8_t idSize = *reinterpret_cast<const std::uint8_t*>(manifest++);
						if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < idSize) [[unlikely]]
						{
							throw std::runtime_error("Unexpected manifest end");
						}
						const auto id = std::string_view(reinterpret_cast<const char*>(manifest), idSize);

						if (manifest >= manifestBufferEnd || manifestBufferEnd - manifest < sizeof(std::size_t) * 4uz) [[unlikely]]
						{
							throw std::runtime_error("Unexpected manifest end");
						}
						constexpr std::size_t typeIndexIndex = 0uz;
						constexpr std::size_t dataMetaIndexIndex = 1uz;
						constexpr std::size_t loadMetaIndexIndex = 2uz;
						constexpr std::size_t dataIndexIndex = 3uz;
						std::array<std::size_t, 4uz> resourceIndices;
						std::memcpy(resourceIndices.data(), manifest, sizeof(std::size_t) * 4uz);
						manifest += sizeof(std::size_t) * 4uz;

						const std::size_t typeIndex = resourceIndices[typeIndexIndex];
						if (typeIndex >= resourceTypes.size()) [[unlikely]]
						{
							throw std::runtime_error("Invalid resource type index");
						}
						const std::size_t dataMetaIndex = resourceIndices[dataMetaIndexIndex];
						if (dataMetaIndex >= dataMetas.size()) [[unlikely]]
						{
							throw std::runtime_error("Invalid data meta index");
						}
						const std::size_t loadMetaIndex = resourceIndices[loadMetaIndexIndex];
						if (loadMetaIndex >= loadMetas.size()) [[unlikely]]
						{
							throw std::runtime_error("Invalid data meta index");
						}
						const std::size_t dataIndex = resourceIndices[dataIndexIndex];
						if (dataIndex >= ranges.size()) [[unlikely]]
						{
							throw std::runtime_error("Invalid data meta index");
						}
						resources[i] = CollectionResource
						{
							.id = resourceHub->MakeResourceID(id),
							.type = resourceTypes[typeIndex],
							.dataMeta = dataMetas[dataMetaIndex],
							.loadMeta = loadMetas[loadMetaIndex],
							.dataIndex = dataIndex
						};
					}

					req->Ranges(ranges);
					req->CollectionResources(resources);

					if (req->DecrementRequestCount() == 1uz)
					{
						if (req->IsCancelRequested())
						{
							const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
							mountRequest->SetCanceled();
						}
						else
						{
							CreatePack(*req);
						}
					}
				}
				catch (...)
				{
					req->ManifestException(std::current_exception());
					if (req->DecrementRequestCount() == 1uz)
					{
						const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetFailure(req->ManifestException());
					}
				}
			});
		}
		catch (...)
		{
			request.ManifestException(std::current_exception());
			if (request.DecrementRequestCount() == 1uz)
			{
				const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(&request);
				mountRequest->SetFailure(request.ManifestException());
			}
		}
	}

	void PackService::CreatePack(FilePackMountRequest& request) noexcept
	{
		try
		{
			jobService->Schedule([this, req = &request]() noexcept
			{
				if (req->IsCancelRequested())
				{
					if (req->DecrementRequestCount() == 1uz)
					{
						const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
						mountRequest->SetCanceled();
					}

					return;
				}

				try
				{
					std::shared_ptr<std::byte[]> loadedData = nullptr;
					if (Any(AccessType::Memory, req->AccessType()))
					{
						loadedData = std::make_shared<std::byte[]>(req->DataBuffer().size());
						std::memcpy(loadedData.get(), req->DataBuffer().data(), req->DataBuffer().size());
					}

					const auto pack = std::make_shared<class Pack>(loadableDataAccessRequestWorker,
						Any(AccessType::File, req->AccessType()) ? req->DataFile()->Path() : std::filesystem::path(),
						Any(AccessType::Loadable, req->AccessType()) && None(AccessType::Memory, req->AccessType()) ? req->DataFile() : nullptr,
						loadedData, req->Ranges());

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
					const std::span<const CollectionResource> resources = req->CollectionResources();
					const ResourceCollection collection = resourceHub->RegisterCollection(*pack, resources, accessTypes);

					try
					{
						std::vector<ResourceInfo> infos;
						infos.reserve(resources.size());
						for (const CollectionResource& resource : resources)
						{
							infos.push_back(ResourceInfo
							{
								.id = resource.id,
								.type = resource.type
							});
						}
						const PackHandle packHandle = AddPack(collection, pack, infos);

						const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
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
					const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(req);
					mountRequest->SetFailure(req->ManifestException());
				}
			});
		}
		catch (...)
		{
			request.ManifestException(std::current_exception());
			const std::shared_ptr<FilePackMountRequest> mountRequest = RemoveMountRequest(&request);
			mountRequest->SetFailure(request.ManifestException());
		}
	}
}
