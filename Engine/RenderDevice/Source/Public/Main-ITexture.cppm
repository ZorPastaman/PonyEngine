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

export module PonyEngine.RenderDevice:ITexture;

import std;

import PonyEngine.Math;

import :SampleCount;
import :TextureDimension;
import :TextureFormatId;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	class ITexture
	{
		PONY_INTERFACE_BODY(ITexture)

		[[nodiscard("Pure function")]]
		virtual TextureDimension Dimension() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual TextureFormatId Format() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::span<const TextureFormatId> CastableFormats() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual Math::Vector3<std::uint32_t> Size() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t MipCount() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ArraySize() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual SampleCount SampleCount() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual TextureUsage Usage() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool SRGBCompatible() const noexcept = 0;

		virtual void SetName(std::string_view name) = 0;
	};
}
