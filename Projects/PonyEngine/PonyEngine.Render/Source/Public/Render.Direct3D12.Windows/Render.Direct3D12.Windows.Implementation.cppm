/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Render.Direct3D12.Windows.Implementation;

export import PonyEngine.Render.Direct3D12.Windows.Factory;

import :WindowsDirect3D12RenderSystemFactory;
import :WindowsDirect3D12RenderSystemFactoryDestroyer;

export namespace PonyEngine::Render
{
	/// @brief Creates a Direct3D 12 render system for Windows factory.
	///	@param params Direct3D 12 render system for Windows factory parameters.
	/// @return Direct3D 12 render system for Windows factory
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsDirect3D12RenderSystemFactoryData CreateWindowsDirect3D12RenderSystemFactory(const WindowsDirect3D12RenderSystemFactoryParams& params);
}

namespace PonyEngine::Render
{
	auto DefaultWindowsDirect3D12RenderSystemFactoryDestroyer = WindowsDirect3D12RenderSystemFactoryDestroyer(); ///< Default Direct3D 12 render system for Windows factory destroyer.

	WindowsDirect3D12RenderSystemFactoryData CreateWindowsDirect3D12RenderSystemFactory(const WindowsDirect3D12RenderSystemFactoryParams&)
	{
		const auto factory = new WindowsDirect3D12RenderSystemFactory();
		const auto factoryDeleter = Core::SystemFactoryDeleter(DefaultWindowsDirect3D12RenderSystemFactoryDestroyer);

		return WindowsDirect3D12RenderSystemFactoryData
		{
			.systemFactory = Core::SystemFactoryUniquePtr(factory, factoryDeleter)
		};
	}
}