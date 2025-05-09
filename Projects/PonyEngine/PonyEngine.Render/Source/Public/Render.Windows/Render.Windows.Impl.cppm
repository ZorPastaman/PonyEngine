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

export module PonyEngine.Render.Windows.Impl;

export import PonyEngine.Render.Windows;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Render.Windows.Detail;

export namespace PonyEngine::Render::Windows
{
	/// @brief Creates a render system for Windows factory.
	///	@param application Application context.
	///	@param factoryParams Render system for Windows factory parameters.
	///	@param systemParams Render system for Windows parameters.
	/// @return Render system for Windows factory
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT RenderSystemFactoryData CreateRenderSystemFactory(Core::IApplicationContext& application, const RenderSystemFactoryParams& factoryParams, const RenderSystemParams& systemParams);
}

namespace PonyEngine::Render::Windows
{
	RenderSystemFactoryData CreateRenderSystemFactory(Core::IApplicationContext& application, const RenderSystemFactoryParams& factoryParams, const RenderSystemParams& systemParams)
	{
		return RenderSystemFactoryData{.systemFactory = std::make_shared<RenderSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
