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

export module PonyEngine.Render.Direct3D12.Detail:IFrameManager;

import <memory>;

import PonyMath.Utility;

import :Frame;

export namespace PonyEngine::Render::Direct3D12
{
	class IFrameManager
	{
		INTERFACE_BODY(IFrameManager)

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT RtvFormat() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT DsvFormat() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<UINT>& Resolution() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept = 0;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<class Frame> CreateFrame() = 0;
	};
}
