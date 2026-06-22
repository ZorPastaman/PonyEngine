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

export module PonyEngine.Resource.File.Impl:FileResourceProvider;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.File;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :FileFileResourceData;
import :FileLoadableResourceData;
import :LoadRequestManager;

export namespace PonyEngine::Resource::File
{
	class FileResourceProvider final : public IResourceProvider
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit FileResourceProvider(IResourceContext& resourceContext);
		FileResourceProvider(const FileResourceProvider&) = delete;
		FileResourceProvider(FileResourceProvider&&) = delete;

		~FileResourceProvider() noexcept = default;

		virtual void Begin(IResourceRegistry& registry) override;
		virtual void End(IResourceRegistry& registry) override;
		virtual void Tick(IResourceRegistry& registry) override;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<ILoadableResourceData> GetLoadableResource(std::size_t index) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IFileResourceData> GetFileResource(std::size_t index) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IMemoryResourceData> GetMemoryResource(std::size_t index) const override;

		FileResourceProvider& operator =(const FileResourceProvider&) = delete;
		FileResourceProvider& operator =(FileResourceProvider&&) = delete;

	private:
		void Begin(IResourceRegistry& registry, std::size_t& count);
		void End(IResourceRegistry& registry, std::size_t count) const;

		IResourceContext* resourceContext;
		PonyEngine::File::IFileService* fileService;

		LoadRequestManager loadRequestManager;

		std::vector<std::filesystem::path> filePaths;
		std::vector<ResourceHandle> resourceHandles;
	};
}

namespace PonyEngine::Resource::File
{
	FileResourceProvider::FileResourceProvider(IResourceContext& resourceContext) :
		resourceContext{&resourceContext},
		fileService{&this->resourceContext->Application().GetService<PonyEngine::File::IFileService>()}
	{
	}

	void FileResourceProvider::Begin(IResourceRegistry& registry)
	{
		std::size_t count = 0uz;
		
		try
		{
			Begin(registry, count);
		}
		catch (...)
		{
			End(registry, count);
			throw;
		}
	}

	void FileResourceProvider::End(IResourceRegistry& registry)
	{
		End(registry, resourceHandles.size());
	}

	void FileResourceProvider::Tick(IResourceRegistry& registry)
	{
	}

	std::shared_ptr<ILoadableResourceData> FileResourceProvider::GetLoadableResource(const std::size_t index) const
	{
		std::shared_ptr<PonyEngine::File::IFile> file = fileService->OpenFile(PonyEngine::File::FileParams
		{
			.path = filePaths[index],
			.access = PonyEngine::File::FileAccess::Read,
		});

		return std::make_shared<FileLoadableResourceData>(loadRequestManager, std::move(file));
	}

	std::shared_ptr<IFileResourceData> FileResourceProvider::GetFileResource(const std::size_t index) const
	{
		return std::make_shared<FileFileResourceData>(filePaths[index]);
	}

	std::shared_ptr<IMemoryResourceData> FileResourceProvider::GetMemoryResource(const std::size_t index) const
	{
		throw std::logic_error("Not implemented");
	}

	void FileResourceProvider::Begin(IResourceRegistry& registry, std::size_t& count)
	{
		// TODO: Parse manifest and register resources
	}

	void FileResourceProvider::End(IResourceRegistry& registry, const std::size_t count) const
	{
		for (std::size_t i = count; i-- > 0uz; )
		{
			registry.UnregisterResource(resourceHandles[i]);
		}
	}
}
