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
#include "PonyEngine/Macro/Text.h"

export module PonyEngine.Resource.File.Impl:FileResourceProvider;

import std;

import PonyEngine.Application;
import PonyEngine.File;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :FileResourceData;
import :LoadableResourceData;
import :LoadRequestManager;

export namespace PonyEngine::Resource::File
{
	/// @brief File resource provider.
	class FileResourceProvider final : public IResourceProvider
	{
	public:
		/// @brief Creates a file resource provider.
		/// @param resourceContext Resource context.
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
		/// @brief Begins the provider.
		/// @param registry Resource registry.
		/// @param count How many resources are registered.
		void Begin(IResourceRegistry& registry, std::size_t& count);
		/// @brief Ends the provider.
		/// @param registry Resource registry.
		/// @param count How many resources to unregister.
		void End(IResourceRegistry& registry, std::size_t count) const;

		/// @brief Parses the manifest.
		/// @param data Manifest.
		/// @param registry Resource registry.
		/// @param count How many resources are registered.
		void ParseManifest(std::span<const char> data, IResourceRegistry& registry, std::size_t& count);
		/// @brief Adds a resource.
		/// @param registry Resource registry.
		/// @param resourceId Resource ID.
		/// @param resourceType Resource type.
		/// @param resourcePath Resource path.
		void AddResource(IResourceRegistry& registry, std::string_view resourceId, std::string_view resourceType, std::string_view resourcePath);

		/// @brief Makes an absolute resource path.
		/// @param relativePath Relative to a game root path.
		/// @return Absolute resource path.
		[[nodiscard("Pure function")]]
		std::filesystem::path MakeAbsolutePath(const std::filesystem::path& relativePath) const;

		static constexpr std::string_view ManifestExtension = ".pfrm"; ///< Resource manifest file extension.
		static constexpr std::string_view MagicHeader = "PonyEngineFRM"; ///< Resource manifest magic header.

		IResourceContext* resourceContext; ///< Resource context.
		PonyEngine::File::IFileService* fileService; ///< File service.

		LoadRequestManager loadRequestManager; ///< Load request manager.

		std::vector<std::filesystem::path> filePaths; ///< File paths.
		std::vector<ResourceHandle> resourceHandles; ///< Resource handles. Synced with the @p filePaths by index.
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
		std::shared_ptr<PonyEngine::File::IFile> file = fileService->OpenFile(filePaths[index], PonyEngine::File::FileParams::Read());
		return std::make_shared<LoadableResourceData>(loadRequestManager, std::move(file));
	}

	std::shared_ptr<IFileResourceData> FileResourceProvider::GetFileResource(const std::size_t index) const
	{
		return std::make_shared<FileResourceData>(&filePaths[index]);
	}

	std::shared_ptr<IMemoryResourceData> FileResourceProvider::GetMemoryResource(const std::size_t index) const
	{
		throw std::logic_error("Not available");
	}

	void FileResourceProvider::Begin(IResourceRegistry& registry, std::size_t& count)
	{
		const std::filesystem::path manifestDirectory = 
			(resourceContext->Application().RootDirectory() / PONY_STRINGIFY_VALUE(PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR)).lexically_normal();
		if (!std::filesystem::is_directory(manifestDirectory)) [[unlikely]]
		{
			PONY_LOG(resourceContext->Logger(), Log::LogType::Warning, "File resource manifest directory not found. Directory: '{}'.", manifestDirectory.string());
			return;
		}

		const auto manifestExtension = std::filesystem::path(ManifestExtension);
		for (std::vector<char> fileData; const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator(manifestDirectory))
		{
			const std::filesystem::path& path = file.path();
			if (path.extension() != manifestExtension) [[unlikely]]
			{
				continue;
			}

			PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Reading file resource manifest... Path: '{}'.", path.string());
			auto fileStream = std::ifstream(path, std::ios::ate | std::ios::binary);
			if (!fileStream) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to open manifest file: path = '{}'", path.string()));
			}
			fileData.resize(static_cast<std::size_t>(fileStream.tellg()));
			fileStream.seekg(0, std::ios::beg);
			fileStream.read(fileData.data(), fileData.size());
			ParseManifest(fileData, registry, count);
			PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Reading file resource manifest done. Path: '{}'.", path.string());
		}
	}

	void FileResourceProvider::End(IResourceRegistry& registry, const std::size_t count) const
	{
		for (std::size_t i = count; i-- > 0uz; )
		{
			registry.UnregisterResource(resourceHandles[i]);
		}
	}

	void FileResourceProvider::ParseManifest(const std::span<const char> data, IResourceRegistry& registry, std::size_t& count)
	{
		if (data.size() < MagicHeader.size() || std::memcmp(data.data(), MagicHeader.data(), MagicHeader.size()) != 0) [[unlikely]]
		{
			PONY_LOG(resourceContext->Logger(), Log::LogType::Warning, "Manifest doesn't have correct magic header.");
			return;
		}

		const char* current = data.data() + MagicHeader.size();
		const char* const end = data.data() + data.size();
		while (current < end)
		{
			if (end - current < 3uz) [[unlikely]]
			{
				throw std::runtime_error("Unexpected manifest file end");
			}

			const std::uint8_t resourceIdSize = static_cast<std::uint8_t>(*current++);
			const std::uint8_t resourceTypeSize = static_cast<std::uint8_t>(*current++);
			const std::uint8_t resourcePathSize = static_cast<std::uint8_t>(*current++);
			const std::uint_fast16_t resourceDataSize = static_cast<std::uint_fast16_t>(resourceIdSize) + resourceTypeSize + resourcePathSize;
			if (end - current < resourceDataSize) [[unlikely]]
			{
				throw std::runtime_error("Unexpected manifest file end");
			}

			const auto resourceId = std::string_view(current, resourceIdSize);
			current += resourceIdSize;
			const auto resourceType = std::string_view(current, resourceTypeSize);
			current += resourceTypeSize;
			const auto resourcePath = std::string_view(current, resourcePathSize);
			current += resourcePathSize;

			AddResource(registry, resourceId, resourceType, resourcePath);

			++count;
		}
	}

	void FileResourceProvider::AddResource(IResourceRegistry& registry, const std::string_view resourceId, const std::string_view resourceType, const std::string_view resourcePath)
	{
		PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Registering resource... ID: '{}'; Type: '{}'; Path: '{}'.", resourceId, resourceType, resourcePath);

		const ResourceID id = resourceContext->MakeResourceID(resourceId);
		const ResourceType type = resourceContext->MakeResourceType(resourceType);
		const std::size_t index = filePaths.size();

		filePaths.push_back(MakeAbsolutePath(std::filesystem::path(resourcePath).lexically_normal()));

		try
		{
			const ResourceHandle handle = registry.RegisterResource(ResourceParams
			{
				.id = id,
				.type = type,
				.availability = ResourceAvailability::Loadable | ResourceAvailability::File,
				.index = index
			});
			try
			{
				resourceHandles.push_back(handle);
			}
			catch (...)
			{
				registry.UnregisterResource(handle);
				throw;
			}
		}
		catch (...)
		{
			filePaths.pop_back();
			throw;
		}

		PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Registering resource done.");
	}

	std::filesystem::path FileResourceProvider::MakeAbsolutePath(const std::filesystem::path& relativePath) const
	{
		return resourceContext->Application().RootDirectory() / relativePath;
	}
}
