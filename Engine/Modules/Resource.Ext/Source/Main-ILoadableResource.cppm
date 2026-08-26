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

		/// @brief Sets the data access type.
		/// @param dataAccessType Data access type. Must be one of the @p DataAccessTypes().
		virtual void SetDataAccessType(std::type_index dataAccessType) = 0;
		/// @brief Adds the resource interface type.
		/// @param interfaceType Resource interface type.
		void AddInterfaceType(std::type_index interfaceType);
		/// @brief Adds the resource interface types.
		/// @param interfaceTypes Resource interface types.
		virtual void AddInterfaceTypes(std::span<const std::type_index> interfaceTypes) = 0;
		/// @brief Adds the load data.
		/// @param loadData Load data.
		/// @param loadDataType Load data type.
		virtual void AddLoadData(std::shared_ptr<const void> loadData, std::type_index loadDataType) = 0;
	};
}

namespace PonyEngine::Resource
{
	void ILoadableResource::AddInterfaceType(const std::type_index interfaceType)
	{
		AddInterfaceTypes(std::span(&interfaceType, 1uz));
	}
}
