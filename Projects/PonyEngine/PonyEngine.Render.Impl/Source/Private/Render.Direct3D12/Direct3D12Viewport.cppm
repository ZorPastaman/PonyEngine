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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Viewport;

import PonyMath.Core;
import PonyMath.Utility;

export namespace PonyEngine::Render
{
	class Direct3D12Viewport final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12Viewport(const PonyMath::Utility::Resolution<UINT>& resolution) noexcept;
		Direct3D12Viewport(const Direct3D12Viewport& other) noexcept = default;
		Direct3D12Viewport(Direct3D12Viewport&& other) noexcept = default;

		~Direct3D12Viewport() noexcept = default;

		[[nodiscard("Pure function")]]
		const D3D12_VIEWPORT& Viewport() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_RECT& Rect() const noexcept;

		Direct3D12Viewport& operator =(const Direct3D12Viewport& other) noexcept = default;
		Direct3D12Viewport& operator =(Direct3D12Viewport&& other) noexcept = default;

	private:
		D3D12_VIEWPORT viewPort;
		D3D12_RECT rect;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Viewport::Direct3D12Viewport(const PonyMath::Utility::Resolution<UINT>& resolution) noexcept :
		viewPort{.TopLeftX = 0.f, .TopLeftY = 0.f, .Width = static_cast<FLOAT>(resolution.Width()), .Height = static_cast<FLOAT>(resolution.Height()), .MinDepth = D3D12_MIN_DEPTH, .MaxDepth = D3D12_MAX_DEPTH},
		rect{.left = 0L, .top = 0L, .right = static_cast<LONG>(resolution.Width()), .bottom = static_cast<LONG>(resolution.Height())}
	{
	}

	const D3D12_VIEWPORT& Direct3D12Viewport::Viewport() const noexcept
	{
		return viewPort;
	}

	const D3D12_RECT& Direct3D12Viewport::Rect() const noexcept
	{
		return rect;
	}
}
