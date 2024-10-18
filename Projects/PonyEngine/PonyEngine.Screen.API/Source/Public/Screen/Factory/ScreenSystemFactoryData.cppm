/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Factory:ScreenSystemFactoryData;

import PonyEngine.Core.Factory;

export namespace PonyEngine::Screen
{
	struct ScreenSystemFactoryData final
	{
		Core::SystemFactoryUniquePtr systemFactory; ///< System factory.
	};
}
