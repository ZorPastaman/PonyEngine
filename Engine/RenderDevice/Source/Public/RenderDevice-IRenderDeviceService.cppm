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

export module PonyEngine.RenderDevice:IRenderDeviceService;

import std;

import PonyEngine.Meta;

import :TextureFormatFeature;
import :TextureFormatId;
import :TextureSupportRequest;
import :TextureSupportResponse;

export namespace PonyEngine::Render
{
	class IRenderDeviceService
	{
		PONY_INTERFACE_BODY(IRenderDeviceService)

		static constexpr std::size_t EmptyBackendIndex = 0uz;

		[[nodiscard("Pure function")]]
		virtual std::size_t BackendCount() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view RenderApiName(std::size_t backendIndex) const = 0;
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderApiVersion(std::size_t backendIndex) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t ActiveBackend() const noexcept = 0;
		virtual void SwitchBackend(std::size_t backendIndex) = 0;

		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatId TextureFormatId(std::string_view textureFormat) = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatId textureFormatId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual TextureFormatFeature TextureFormatFeatures(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const = 0;
	};
}
