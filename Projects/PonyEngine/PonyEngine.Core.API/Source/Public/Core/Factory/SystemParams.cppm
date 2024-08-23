/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemParams;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief System parameters.
	struct SystemParams final
	{
		IEngine* engine = nullptr; ///< Engine that owns the system.
	};
}
