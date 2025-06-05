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

import :Frame;
import :FrameParams;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 frame manager.
	class IFrameManager
	{
		INTERFACE_BODY(IFrameManager)

		/// @brief Converts the @p frameParams to a Direct3D12 format.
		/// @note Throws if the params are incompatible with the current hardware.
		/// @param frameParams Frame parameters.
		/// @return Direct3D12 frame parameters.
		[[nodiscard("Pure function")]]
		virtual FrameParams ConvertFrameParams(const Render::FrameParams& frameParams) const = 0;

		/// @brief Creates a frame.
		/// @param frameParams Frame parameters.
		/// @return Frame.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Frame> CreateFrame(const FrameParams& frameParams) = 0;
	};
}
