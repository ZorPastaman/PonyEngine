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

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderSystem;

import PonyEngine.Render;

import :IDirect3D12RenderTarget;
import :IDirect3D12RenderView;
import :IDirect3D12RenderObjectManager;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render system.
	class IDirect3D12RenderSystem : public IRenderSystem
	{
		INTERFACE_BODY(IDirect3D12RenderSystem)

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTarget& RenderTarget() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTarget& RenderTarget() const noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderView& RenderView() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderView& RenderView() const noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObjectManager& RenderObjectManager() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderObjectManager& RenderObjectManager() const noexcept override = 0;
	};
}
