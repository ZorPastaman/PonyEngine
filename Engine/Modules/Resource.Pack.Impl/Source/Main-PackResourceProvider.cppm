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

export module PonyEngine.Resource.Pack.Impl:PackResourceProvider;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.File;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :PackFileResourceData;
import :PackLoadableResourceData;
import :LoadRequestManager;

export namespace PonyEngine::Resource::Pack
{
	class PackResourceProvider final : public IResourceProvider
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit PackResourceProvider(IResourceContext& resourceContext);
		PackResourceProvider(const PackResourceProvider&) = delete;
		PackResourceProvider(PackResourceProvider&&) = delete;

		~PackResourceProvider() noexcept = default;

		virtual void Begin(IResourceRegistry& registry) override;
		virtual void End(IResourceRegistry& registry) override;
		virtual void Tick(IResourceRegistry& registry) override;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<ILoadableResourceData> GetLoadableResource(std::size_t index) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IFileResourceData> GetFileResource(std::size_t index) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IMemoryResourceData> GetMemoryResource(std::size_t index) const override;

		PackResourceProvider& operator =(const PackResourceProvider&) = delete;
		PackResourceProvider& operator =(PackResourceProvider&&) = delete;

	private:
		void Begin(IResourceRegistry& registry, std::size_t& count);
		void End(IResourceRegistry& registry, std::size_t count) const;

		void ParseManifest(std::span<const char> data, IResourceRegistry& registry, std::size_t& count);
		[[nodiscard("Pure function")]]
		static std::size_t ParseSize(const char* data) noexcept;
		void AddResource(IResourceRegistry& registry, std::string_view resourceId, std::string_view resourceType, 
			std::size_t packIndex, std::size_t offset, std::size_t size);

		[[nodiscard("Pure function")]]
		std::filesystem::path MakeAbsolutePath(const std::filesystem::path& relativePath) const;

		struct ResourceEntry final
		{
			std::size_t packIndex;
			std::size_t offset;
			std::size_t size;
		};

		static constexpr std::string_view ManifestExtension = ".pprm";
		static constexpr std::string_view MagicHeader = "PonyEnginePRM";

		IResourceContext* resourceContext;
		File::IFileService* fileService;

		LoadRequestManager loadRequestManager;

		std::vector<std::shared_ptr<File::IFile>> packs;
		std::vector<ResourceEntry> resourceEntries;
		std::vector<ResourceHandle> resourceHandles;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackResourceProvider::PackResourceProvider(IResourceContext& resourceContext) :
		resourceContext{&resourceContext},
		fileService{&this->resourceContext->Application().GetService<File::IFileService>()}
	{
	}

	void PackResourceProvider::Begin(IResourceRegistry& registry)
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

	void PackResourceProvider::End(IResourceRegistry& registry)
	{
		End(registry, resourceHandles.size());
	}

	void PackResourceProvider::Tick(IResourceRegistry& registry)
	{
	}

	std::shared_ptr<ILoadableResourceData> PackResourceProvider::GetLoadableResource(const std::size_t index) const
	{
		const ResourceEntry& entry = resourceEntries[index];
		return std::make_shared<PackLoadableResourceData>(loadRequestManager, packs[entry.packIndex].get(), entry.offset, entry.size);
	}

	std::shared_ptr<IFileResourceData> PackResourceProvider::GetFileResource(const std::size_t index) const
	{
		const ResourceEntry& entry = resourceEntries[index];
		return std::make_shared<PackFileResourceData>(packs[entry.packIndex].get(), entry.offset, entry.size);
	}

	std::shared_ptr<IMemoryResourceData> PackResourceProvider::GetMemoryResource(const std::size_t index) const
	{
		throw std::logic_error("Not available");
	}

	void PackResourceProvider::Begin(IResourceRegistry& registry, std::size_t& count)
	{
		const std::filesystem::path manifestDirectory = 
			(resourceContext->Application().RootDirectory() / PONY_STRINGIFY_VALUE(PONY_ENGINE_RESOURCE_PACK_MANIFEST_DIR)).lexically_normal();
		if (!std::filesystem::is_directory(manifestDirectory)) [[unlikely]]
		{
			PONY_LOG(resourceContext->Logger(), Log::LogType::Warning, "Pack resource manifest directory not found. Directory: '{}'.", manifestDirectory.string());
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

			PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Reading pack resource manifest... Path: '{}'.", path.string());
			auto fileStream = std::ifstream(path, std::ios::ate | std::ios::binary);
			if (!fileStream) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to open manifest file: path = '{}'", path.string()));
			}
			fileData.resize(static_cast<std::size_t>(fileStream.tellg()));
			fileStream.seekg(0, std::ios::beg);
			fileStream.read(fileData.data(), fileData.size());
			ParseManifest(fileData, registry, count);
			PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Reading pack resource manifest done. Path: '{}'.", path.string());
		}
	}

	void PackResourceProvider::End(IResourceRegistry& registry, const std::size_t count) const
	{
		for (std::size_t i = count; i-- > 0uz; )
		{
			registry.UnregisterResource(resourceHandles[i]);
		}
	}

	void PackResourceProvider::ParseManifest(const std::span<const char> data, IResourceRegistry& registry, std::size_t& count)
	{
		if (data.size() < MagicHeader.size() || std::memcmp(data.data(), MagicHeader.data(), MagicHeader.size()) != 0) [[unlikely]]
		{
			PONY_LOG(resourceContext->Logger(), Log::LogType::Warning, "Manifest doesn't have correct magic header.");
			return;
		}

		const char* current = data.data() + MagicHeader.size();
		const char* const end = data.data() + data.size();
		if (end == current) [[unlikely]]
		{
			PONY_LOG(resourceContext->Logger(), Log::LogType::Warning, "Manifest is empty.");
			return;
		}

		const std::uint8_t packPathSize = static_cast<std::uint8_t>(*current++);
		if (end - current < packPathSize) [[unlikely]]
		{
			throw std::runtime_error("Unexpected manifest file end");
		}
		const std::size_t packIndex = packs.size();
		const auto packPath = std::string_view(current, packPathSize);
		const std::filesystem::path absolutePath = MakeAbsolutePath(std::filesystem::path(packPath).lexically_normal());
		std::shared_ptr<File::IFile> pack = fileService->OpenFile(absolutePath, File::FileParams::Read());
		const std::size_t packSize = static_cast<std::size_t>(std::filesystem::file_size(absolutePath));
		packs.push_back(std::move(pack));
		current += packPathSize;

		PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Registering resources from pack... PackPath: '{}'.", packPath);
		while (current < end)
		{
			if (end - current < sizeof(std::size_t) * 2 + 2) [[unlikely]]
			{
				throw std::runtime_error("Unexpected manifest file end");
			}

			const std::size_t resourceOffset = ParseSize(current);
			current += sizeof(std::size_t);
			const std::size_t resourceSize = ParseSize(current);
			current += sizeof(std::size_t);
			if (resourceOffset + resourceSize > packSize) [[unlikely]]
			{
				throw std::out_of_range("Invalid resource offset and/or size");
			}

			const std::uint8_t resourceIdSize = static_cast<std::uint8_t>(*current++);
			const std::uint8_t resourceTypeSize = static_cast<std::uint8_t>(*current++);
			if (end - current < static_cast<std::uint_fast16_t>(resourceIdSize) + resourceTypeSize) [[unlikely]]
			{
				throw std::runtime_error("Unexpected manifest file end");
			}

			const auto resourceId = std::string_view(current, resourceIdSize);
			current += resourceIdSize;
			const auto resourceType = std::string_view(current, resourceTypeSize);
			current += resourceTypeSize;

			AddResource(registry, resourceId, resourceType, packIndex, resourceOffset, resourceSize);

			++count;
		}
		PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Registering resources from pack done. PackPath: '{}'.", packPath);
	}

	std::size_t PackResourceProvider::ParseSize(const char* const data) noexcept
	{
		std::size_t value;
		std::memcpy(&value, data, sizeof(std::size_t));
		return value;
	}

	void PackResourceProvider::AddResource(IResourceRegistry& registry, const std::string_view resourceId, const std::string_view resourceType, 
		const std::size_t packIndex, const std::size_t offset, const std::size_t size)
	{
		PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Registering resource... ID: '{}'; Type: '{}'; Offset: '{}'; Size: '{}'.", 
			resourceId, resourceType, offset, size);

		const ResourceID id = resourceContext->MakeResourceID(resourceId);
		const ResourceType type = resourceContext->MakeResourceType(resourceType);
		const std::size_t index = resourceEntries.size();

		resourceEntries.push_back(ResourceEntry
		{
			.packIndex = packIndex,
			.offset = offset,
			.size = size
		});
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
			resourceEntries.pop_back();
			throw;
		}

		PONY_LOG(resourceContext->Logger(), Log::LogType::Info, "Registering resource done.");
	}

	std::filesystem::path PackResourceProvider::MakeAbsolutePath(const std::filesystem::path& relativePath) const
	{
		return resourceContext->Application().RootDirectory() / relativePath;
	}
}
