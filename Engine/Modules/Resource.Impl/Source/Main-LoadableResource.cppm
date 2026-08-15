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

		[[nodiscard("Pure function")]] 
		virtual std::optional<std::type_index> DataAccessType() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::type_index> OutputTypes() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> LoadData() const noexcept override;

		virtual void DataAccessType(std::type_index dataAccessType) override;
		virtual void AddOutputTypes(std::span<const std::type_index> outputTypes) override;
		virtual void AddLoadData(std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData) override;
		virtual void AddLoadData(std::span<const std::shared_ptr<const void>> loadData, std::span<const std::type_index> loadDataTypes) override;

		LoadableResource& operator =(const LoadableResource&) = delete;
		LoadableResource& operator =(LoadableResource&&) = delete;

	private:
		ResourceType resourceType; ///< Resource type.
		std::span<const std::byte> dataMeta; ///< Data meta.
		std::span<const std::byte> loadMeta; ///< Load meta.
		std::span<const std::type_index> dataAccessTypes; ///< Data access types.

		std::optional<std::type_index> dataAccessType; ///< Chosen data access type.
		std::vector<std::type_index> outputTypes; ///< Resource output types.
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

	std::span<const std::type_index> LoadableResource::OutputTypes() const noexcept
	{
		return outputTypes;
	}

	std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> LoadableResource::LoadData() const noexcept
	{
		return loadData;
	}

	void LoadableResource::DataAccessType(const std::type_index dataAccessType)
	{
		assert(std::ranges::contains(dataAccessTypes, dataAccessType) && "Invalid data type.");
		this->dataAccessType = dataAccessType;
	}

	void LoadableResource::AddOutputTypes(const std::span<const std::type_index> outputTypes)
	{
		for (std::size_t i = 1uz; i < outputTypes.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(outputTypes[i] != outputTypes[j] && "Output type duplicate.");
			}
		}
		for (const std::type_index type : outputTypes)
		{
			assert(!std::ranges::contains(this->outputTypes, type) && "Output type already added.");
		}

		this->outputTypes.append_range(outputTypes);
	}

	void LoadableResource::AddLoadData(const std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData)
	{
		this->loadData.append_range(loadData);
	}

	void LoadableResource::AddLoadData(const std::span<const std::shared_ptr<const void>> loadData, const std::span<const std::type_index> loadDataTypes)
	{
		assert(loadData.size() == loadDataTypes.size() && "Load data and types sizes mismatched.");

		for (std::size_t i = 0uz; i < loadData.size(); ++i)
		{
			this->loadData.emplace_back(loadData[i], loadDataTypes[i]);
		}
	}
}
