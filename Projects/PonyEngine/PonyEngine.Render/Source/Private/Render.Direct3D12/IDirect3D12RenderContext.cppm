/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderContext;

import PonyEngine.Render.Detail;
import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	class IDirect3D12RenderContext : public IRenderContext
	{
		INTERFACE_BODY(IDirect3D12RenderContext)

		[[nodiscard("Pure function")]]
		virtual ID3D12Device10& Device() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Device10& Device() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTarget& RenderTarget() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTarget& RenderTarget() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderView& RenderView() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderView& RenderView() const noexcept = 0;
	};
}
