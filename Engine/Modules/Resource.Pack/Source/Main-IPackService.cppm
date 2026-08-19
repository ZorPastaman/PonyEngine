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
import :ResourceInfo;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack service.
	class IPackService
	{
		PONY_INTERFACE_BODY(IPackService)

		[[nodiscard("Pure function")]]
		virtual std::size_t PackCount() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual PackHandle Pack(std::size_t index) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(PackHandle packHandle) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::span<const ResourceInfo> Resources(PackHandle packHandle) const = 0;

		/// @brief Mounts a pack.
		/// @param packPath Path to a pack manifest. If it's relative it's resolved relative to the application root.
		/// @param accessType Access type.
		/// @return Pack mount request.
		/// @note The function is thread-safe.
		virtual std::shared_ptr<IPackMountRequest> MountPack(const std::filesystem::path& packPath, enum AccessType accessType = AccessType::Loadable | AccessType::File) = 0;
		virtual std::shared_ptr<IPackMountRequest> MountPack(std::span<const std::byte> packManifest, std::span<const std::byte> packData, 
			enum AccessType accessType = AccessType::Loadable | AccessType::Memory) = 0;
		virtual std::shared_ptr<IPackUnmountRequest> UnmountPack(PackHandle packHandle) = 0;
	};
}
