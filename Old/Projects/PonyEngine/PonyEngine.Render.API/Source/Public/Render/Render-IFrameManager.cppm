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

export module PonyEngine.Render:IFrameManager;

import :IFrame;

export namespace PonyEngine::Render
{
	/// @brief Frame manager.
	class IFrameManager
	{
		INTERFACE_BODY(IFrameManager)

		/// @brief Gets the main frame.
		/// @return Main frame.
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IFrame>& MainFrame() const noexcept = 0;
	};
}
