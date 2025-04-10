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

export module PonyEngine.Render:IRenderObjectManager;

import <memory>;

import :IRenderObject;
import :RenderObjectParams;

export namespace PonyEngine::Render
{
	/// @brief Render object manager.
	class IRenderObjectManager
	{
		INTERFACE_BODY(IRenderObjectManager)

		/// @brief Creates a render object.
		/// @param params Render object parameters.
		/// @return Render object.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IRenderObject> CreateObject(const RenderObjectParams& params) = 0;
	};
}
