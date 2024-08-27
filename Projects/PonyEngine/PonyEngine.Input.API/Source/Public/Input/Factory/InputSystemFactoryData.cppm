/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Factory:InputSystemFactoryData;

import PonyEngine.Core.Factory;

export namespace PonyEngine::Input
{
	/// @brief Input system factory data.
	struct InputSystemFactoryData final
	{
		Core::SystemFactoryUniquePtr systemFactory; ///< Input system factory.
	};
}
