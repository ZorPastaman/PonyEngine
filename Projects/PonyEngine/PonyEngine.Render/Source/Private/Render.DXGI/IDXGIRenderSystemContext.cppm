/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/DXGI/Framework.h"
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.DXGI.Detail:IDXGIRenderSystemContext;

import PonyEngine.Render.Detail;

export namespace PonyEngine::Render
{
	class IDXGIRenderSystemContext : public IRenderSystemContext
	{
		INTERFACE_BODY(IDXGIRenderSystemContext)

		[[nodiscard("Pure function")]]
		virtual IUnknown* Device() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IUnknown* Device() const noexcept = 0;
	};
}
