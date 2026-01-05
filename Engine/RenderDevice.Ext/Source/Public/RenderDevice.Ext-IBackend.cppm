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

export module PonyEngine.RenderDevice.Ext:IBackend;

import std;

import PonyEngine.Meta;
import PonyEngine.RenderDevice;

export namespace PonyEngine::Render
{
	class IBackend
	{
		PONY_INTERFACE_BODY(IBackend)

		[[nodiscard("Pure function")]]
		virtual std::string_view RenderApiName() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderApiVersion() const noexcept = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		[[nodiscard("Pure function")]]
		virtual TextureFormatFeature SupportedFeatures(TextureFormatId textureFormatId) const = 0;
	};
}
