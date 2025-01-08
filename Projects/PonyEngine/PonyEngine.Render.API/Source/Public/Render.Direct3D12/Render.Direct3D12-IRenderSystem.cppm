/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12:IRenderSystem;

import PonyEngine.Render;

import :IRenderTarget;
import :IRenderView;
import :IRenderObjectManager;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render system.
	class IRenderSystem : public Render::IRenderSystem
	{
		INTERFACE_BODY(IRenderSystem)

		[[nodiscard("Pure function")]]
		virtual IRenderTarget& RenderTarget() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const IRenderTarget& RenderTarget() const noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderView& RenderView() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const IRenderView& RenderView() const noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManager& RenderObjectManager() const noexcept override = 0;
	};
}
