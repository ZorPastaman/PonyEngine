/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ViewSupport;

import :CBVRequirement;

export namespace PonyEngine::RenderDevice
{
	/// @brief View support.
	struct ViewSupport final
	{
		CBVRequirement cbvRequirement; ///< Constant buffer view requirement.
	};
}
