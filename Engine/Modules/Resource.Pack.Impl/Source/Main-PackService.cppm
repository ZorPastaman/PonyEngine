/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Resource.Pack.Impl:PackService;

import std;

import PonyEngine.Application;
import PonyEngine.File;
import PonyEngine.Job;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Resource.Pack;

import :FileDataAccess;
import :FileLoadableDataAccess;
import :LoadableDataAccessRequestWorker;
import :MemoryDataAccess;
import :PackContainer;

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
		class FilePackMountRequest final : public IPackMountRequest
		{
		public:
			[[nodiscard("Pure constructor")]]
			FilePackMountRequest(PackService& packService, const std::filesystem::path& packPath, AccessType accessType);
		};

		[[nodiscard("Must be used")]]
		PackHandle CreatePackHandle();
		[[nodiscard("Must be used")]]
		PackHandle MakePackHandle();
		[[nodiscard("Must be used")]]
		PackHandle ResurrectPackHandle() noexcept;
		void KillPackHandle(PackHandle packHandle) noexcept;

		void AddPack(ResourceCollection collection, const std::shared_ptr<class Pack>& pack, std::span<const ResourceInfo> resourceInfos);
		void RemovePack(PackHandle packHandle);

		Application::IApplication* application;
		Log::ILogService* logService;
		IResourceHub* resourceHub;

		LoadableDataAccessRequestWorker loadableDataAccessRequestWorker;

		PackContainer packContainer;
		std::vector<PackVersion> packVersions;
		std::vector<PackID> deadPackIds;

		std::shared_mutex stateMutex;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackService::PackService(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		resourceHub{&this->application->GetInterface<IResourceHub>()},
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
		return std::make_shared<FilePackMountRequest>(*this, packPath, accessType);
	}

	void PackService::AddPack(const ResourceCollection collection, const std::shared_ptr<class Pack>& pack, const std::span<const ResourceInfo> resourceInfos)
	{
		const auto lock = std::unique_lock(stateMutex);

		const PackHandle packHandle = CreatePackHandle();
		packContainer.Add(packHandle, collection, pack, resourceInfos);
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
}
