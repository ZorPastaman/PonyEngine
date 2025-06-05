/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows:WindowSystemFactoryData;

import <memory>;

import PonyEngine.Window;

export namespace PonyEngine::Window::Windows
{
	/// @brief Window system for Windows factory data.
	struct WindowSystemFactoryData final
	{
		std::shared_ptr<WindowSystemFactory> systemFactory; ///< System factory.
	};
}
