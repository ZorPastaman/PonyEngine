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

export module PonyEngine.Resource.Pack:IPackService;

import std;

import PonyEngine.Resource.Ext;

import :AccessType;
import :IPackMountRequest;
import :IPackUnmountRequest;
import :PackHandle;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack service.
	class IPackService
	{
		PONY_INTERFACE_BODY(IPackService)

		/// @brief Mounts a pack.
		/// @param packPath Path to a pack manifest. If it's relative it's resolved relative to the application root.
		/// @param accessType Access type.
		/// @param callback Callback.
		/// @return Pack mount request.
		/// @note The request and the callback must be kept alive till the end of the operation.
		/// @note The function is thread-safe.
		virtual std::shared_ptr<IPackMountRequest> MountPack(std::filesystem::path packPath, enum AccessType accessType = AccessType::Loadable | AccessType::File,
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback = nullptr) = 0;
		virtual std::shared_ptr<IPackMountRequest> MountPack(std::span<const std::byte> packManifest, std::span<const std::byte> packData, 
			enum AccessType accessType = AccessType::Loadable | AccessType::Memory, std::move_only_function<void(const IPackMountRequest&) noexcept> callback = nullptr) = 0;
		virtual std::shared_ptr<IPackUnmountRequest> UnmountPack(PackHandle packHandle) = 0;
	};
}
