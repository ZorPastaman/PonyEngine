/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render:IRenderSystem;

import :IRenderObjectManager;
import :IRenderTarget;
import :IRenderView;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem
	{
		INTERFACE_BODY(IRenderSystem)

		[[nodiscard("Pure function")]]
		virtual IRenderTarget& RenderTarget() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IRenderTarget& RenderTarget() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderView& RenderView() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IRenderView& RenderView() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManager& RenderObjectManager() const noexcept = 0;
	};
}
