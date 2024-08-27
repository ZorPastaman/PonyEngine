/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystemFactoryDestroyer;

import PonyEngine.Core.Factory;

import :WindowsDirect3D12RenderSystemFactory;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory destroyer.
	struct WindowsDirect3D12RenderSystemFactoryDestroyer final : Core::ISystemFactoryDestroyer
	{
		virtual void Destroy(Core::ISystemFactory* factory) noexcept override;
	};
}

namespace PonyEngine::Render
{
	void WindowsDirect3D12RenderSystemFactoryDestroyer::Destroy(Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<WindowsDirect3D12RenderSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<WindowsDirect3D12RenderSystemFactory*>(factory);
	}
}
