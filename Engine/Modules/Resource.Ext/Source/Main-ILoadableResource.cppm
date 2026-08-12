/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Resource.Ext:ILoadableResource;

import std;

import PonyEngine.Resource;

import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Loadable resource.
	class ILoadableResource
	{
		PONY_INTERFACE_BODY(ILoadableResource)

		/// @brief Gets the resource type.
		/// @return Resource type.
		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept = 0;
		/// @brief Gets the raw data meta.
		/// @return Raw data meta.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> DataMeta() const noexcept = 0;
		/// @brief Gets the raw load meta.
		/// @return Raw load meta.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> LoadMeta() const noexcept = 0;
		/// @brief Gets the data access types.
		/// @return Data access types. Guaranteed to be at least size of 1.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> DataAccessTypes() const noexcept = 0;

		/// @brief Gets the data access type.
		/// @return Data access type.
		[[nodiscard("Pure function")]]
		virtual std::optional<std::type_index> DataAccessType() const noexcept = 0;
		/// @brief Gets the output types.
		/// @return Output types.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> OutputTypes() const noexcept = 0;
		/// @brief Gets the load data.
		/// @return Load data.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> LoadData() const noexcept = 0;

		/// @brief Sets the data access type.
		/// @param dataAccessType Data access type. Must be one of the @p DataAccessTypes().
		virtual void DataAccessType(std::type_index dataAccessType) = 0;
		/// @brief Adds the resource output type.
		/// @param outputType Resource output type.
		void AddOutputType(std::type_index outputType);
		/// @brief Adds the resource output types.
		/// @param outputTypes Resource output types.
		virtual void AddOutputTypes(std::span<const std::type_index> outputTypes) = 0;
		/// @brief Adds the load data.
		/// @param loadData Load data.
		void AddLoadData(const std::pair<std::shared_ptr<const void>, std::type_index>& loadData);
		/// @brief Adds the load data.
		/// @param loadData Load data.
		virtual void AddLoadData(std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData) = 0;
		/// @brief Adds the load data.
		/// @param loadData Load data.
		/// @param loadDataType Load data type.
		void AddLoadData(const std::shared_ptr<const void>& loadData, std::type_index loadDataType);
		/// @brief Adds the load data.
		/// @param loadData Load data.
		/// @param loadDataTypes Load data types.
		virtual void AddLoadData(std::span<const std::shared_ptr<const void>> loadData, std::span<const std::type_index> loadDataTypes) = 0;
	};
}

namespace PonyEngine::Resource
{
	void ILoadableResource::AddOutputType(const std::type_index outputType)
	{
		AddOutputTypes(std::span(&outputType, 1uz));
	}

	void ILoadableResource::AddLoadData(const std::pair<std::shared_ptr<const void>, std::type_index>& loadData)
	{
		AddLoadData(std::span(&loadData, 1uz));
	}

	void ILoadableResource::AddLoadData(const std::shared_ptr<const void>& loadData, const std::type_index loadDataType)
	{
		AddLoadData(std::span(&loadData, 1uz), std::span(&loadDataType, 1uz));
	}
}
