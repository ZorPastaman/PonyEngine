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

export module PonyEngine.Render.DXGI.Detail:IDXGISystemContext;

import PonyDebug.Log;

export namespace PonyEngine::Render
{
	class IDXGISystemContext
	{
		INTERFACE_BODY(IDXGISystemContext)

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDXGIFactory7& Factory() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDXGIFactory7& Factory() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IUnknown& Device() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IUnknown& Device() const noexcept = 0;
	};
}
