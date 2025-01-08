/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyEngine.Render.Direct3D12.Windows.Impl;

export import PonyEngine.Render.Direct3D12.Windows;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows.Detail;

export namespace PonyEngine::Render::Direct3D12::Windows
{
	/// @brief Creates a Direct3D 12 render system for Windows factory.
	///	@param application Application context.
	///	@param factoryParams Direct3D 12 render system for Windows factory parameters.
	///	@param systemParams Direct3D 12 render system for Windows parameters.
	/// @return Direct3D 12 render system for Windows factory
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT RenderSystemFactoryData CreateRenderSystemFactory(Core::IApplicationContext& application, const RenderSystemFactoryParams& factoryParams, const RenderSystemParams& systemParams);
}

namespace PonyEngine::Render::Direct3D12::Windows
{
	RenderSystemFactoryData CreateRenderSystemFactory(Core::IApplicationContext& application, const RenderSystemFactoryParams& factoryParams, const RenderSystemParams& systemParams)
	{
		return RenderSystemFactoryData{.systemFactory = std::make_unique<RenderSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
