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

export module PonyEngine.Resource.Impl:LoadableResource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	/// @brief Loadable resource.
	class LoadableResource final : public ILoadableResource
	{
	public:
		/// @brief Creates a loadable resource.
		/// @param resourceType Resource type.
		/// @param dataMeta Resource data meta.
		/// @param loadMeta Resource load meta.
		/// @param dataAccessTypes Data access types.
		[[nodiscard("Pure constructor")]]
		LoadableResource(ResourceType resourceType, std::span<const std::byte> dataMeta, std::span<const std::byte> loadMeta, 
			std::span<const std::type_index> dataAccessTypes) noexcept;
		LoadableResource(const LoadableResource&) = delete;
		LoadableResource(LoadableResource&&) = delete;

		~LoadableResource() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual ResourceType Type() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::byte> DataMeta() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::byte> LoadMeta() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::type_index> DataAccessTypes() const noexcept override;

		virtual void SetDataAccessType(std::type_index dataAccessType) override;
		virtual void AddInterfaceTypes(std::span<const std::type_index> interfaceTypes) override;
		virtual void AddLoadData(std::shared_ptr<const void> loadData, std::type_index loadDataType) override;

		/// @brief Gets the data access type.
		/// @return Data access type.
		[[nodiscard("Pure function")]]
		std::optional<std::type_index> DataAccessType() const noexcept;
		/// @brief Gets the interface types.
		/// @return Interfaces types
		[[nodiscard("Pure function")]]
		std::vector<std::type_index>& InterfaceTypes() noexcept;
		/// @brief Gets the load data.
		/// @return Load data.
		[[nodiscard("Pure function")]]
		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>>& LoadData() noexcept;

		LoadableResource& operator =(const LoadableResource&) = delete;
		LoadableResource& operator =(LoadableResource&&) = delete;

	private:
		ResourceType resourceType; ///< Resource type.
		std::span<const std::byte> dataMeta; ///< Data meta.
		std::span<const std::byte> loadMeta; ///< Load meta.
		std::span<const std::type_index> dataAccessTypes; ///< Data access types.

		std::optional<std::type_index> dataAccessType; ///< Chosen data access type.
		std::vector<std::type_index> interfaceTypes; ///< Resource interface types.
		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData; ///< Load data.
	};
}

namespace PonyEngine::Resource
{
	LoadableResource::LoadableResource(const ResourceType resourceType, const std::span<const std::byte> dataMeta,
		const std::span<const std::byte> loadMeta, const std::span<const std::type_index> dataAccessTypes) noexcept :
		resourceType(resourceType),
		dataMeta(dataMeta),
		loadMeta(loadMeta),
		dataAccessTypes(dataAccessTypes)
	{
		assert(!this->dataAccessTypes.empty() && "Zero data access types.");
	}

	ResourceType LoadableResource::Type() const noexcept
	{
		return resourceType;
	}

	std::span<const std::byte> LoadableResource::DataMeta() const noexcept
	{
		return dataMeta;
	}

	std::span<const std::byte> LoadableResource::LoadMeta() const noexcept
	{
		return loadMeta;
	}

	std::span<const std::type_index> LoadableResource::DataAccessTypes() const noexcept
	{
		return dataAccessTypes;
	}

	std::optional<std::type_index> LoadableResource::DataAccessType() const noexcept
	{
		return dataAccessType;
	}

	std::vector<std::type_index>& LoadableResource::InterfaceTypes() noexcept
	{
		return interfaceTypes;
	}

	std::vector<std::pair<std::shared_ptr<const void>, std::type_index>>& LoadableResource::LoadData() noexcept
	{
		return loadData;
	}

	void LoadableResource::SetDataAccessType(const std::type_index dataAccessType)
	{
		assert(std::ranges::contains(dataAccessTypes, dataAccessType) && "Invalid data type.");
		this->dataAccessType = dataAccessType;
	}

	void LoadableResource::AddInterfaceTypes(std::span<const std::type_index> interfaceTypes)
	{
		for (std::size_t i = 1uz; i < interfaceTypes.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(interfaceTypes[i] != interfaceTypes[j] && "Output type duplicate.");
			}
		}
		for (const std::type_index type : interfaceTypes)
		{
			assert(!std::ranges::contains(this->interfaceTypes, type) && "Output type already added.");
		}

		this->interfaceTypes.append_range(interfaceTypes);
	}

	void LoadableResource::AddLoadData(std::shared_ptr<const void> loadData, const std::type_index loadDataType)
	{
		this->loadData.push_back(std::pair(std::move(loadData), loadDataType));
	}
}
