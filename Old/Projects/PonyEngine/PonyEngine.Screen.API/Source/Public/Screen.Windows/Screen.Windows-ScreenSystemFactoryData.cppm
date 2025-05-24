/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows:ScreenSystemFactoryData;

import <memory>;

import PonyEngine.Screen;

export namespace PonyEngine::Screen::Windows
{
	/// @brief Windows screen system factory data.
	struct ScreenSystemFactoryData final
	{
		std::shared_ptr<ScreenSystemFactory> systemFactory; ///< System factory.
	};
}
