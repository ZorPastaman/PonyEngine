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
import :FrameParams;

export namespace PonyEngine::Render::Direct3D12
{
	class IFrameManager
	{
		INTERFACE_BODY(IFrameManager)

		[[nodiscard("Pure function")]]
		virtual FrameParams ConvertFrameParams(const Render::FrameParams& frameParams) const = 0;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Frame> CreateFrame(const FrameParams& frameParams) = 0;
	};
}
