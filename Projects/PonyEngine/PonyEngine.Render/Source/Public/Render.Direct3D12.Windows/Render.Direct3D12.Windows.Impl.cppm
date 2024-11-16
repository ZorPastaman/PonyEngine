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

export namespace PonyEngine::Render
{
	/// @brief Creates a Direct3D 12 render system for Windows factory.
	///	@param application Application context.
	///	@param factoryParams Direct3D 12 render system for Windows factory parameters.
	///	@param systemParams Direct3D 12 render system for Windows parameters.
	/// @return Direct3D 12 render system for Windows factory
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsDirect3D12RenderSystemFactoryData CreateWindowsDirect3D12RenderSystemFactory(Core::IApplicationContext& application, const WindowsDirect3D12RenderSystemFactoryParams& factoryParams, 
		const WindowsDirect3D12RenderSystemParams& systemParams);
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystemFactoryData CreateWindowsDirect3D12RenderSystemFactory(Core::IApplicationContext& application, const WindowsDirect3D12RenderSystemFactoryParams& factoryParams, 
		const WindowsDirect3D12RenderSystemParams& systemParams)
	{
		return WindowsDirect3D12RenderSystemFactoryData{.systemFactory = std::make_unique<WindowsDirect3D12RenderSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
