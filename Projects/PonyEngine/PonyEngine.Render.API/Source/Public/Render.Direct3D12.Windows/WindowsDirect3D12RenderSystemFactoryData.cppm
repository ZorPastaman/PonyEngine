/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows:WindowsDirect3D12RenderSystemFactoryData;

import PonyBase.Memory;

import :IWindowsDirect3D12RenderSystemFactory;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory data.
	struct WindowsDirect3D12RenderSystemFactoryData final
	{
		PonyBase::Memory::UniquePointer<IWindowsDirect3D12RenderSystemFactory> systemFactory; ///< Render system factory.
	};
}
