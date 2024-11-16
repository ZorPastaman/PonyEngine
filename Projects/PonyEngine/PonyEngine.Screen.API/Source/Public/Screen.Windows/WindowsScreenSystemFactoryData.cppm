/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows:WindowsScreenSystemFactoryData;

import <memory>;

import PonyEngine.Screen;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system factory data.
	struct WindowsScreenSystemFactoryData final
	{
		std::unique_ptr<ScreenSystemFactory> systemFactory; ///< System factory.
	};
}
