/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows.Factory:WindowsDirect3D12RenderSystemFactoryData;

import PonyEngine.Core.Factory;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory data.
	struct WindowsDirect3D12RenderSystemFactoryData final
	{
		Core::SystemFactoryUniquePtr systemFactory; ///< Render system factory.
	};
}
