/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows:WindowsClassData;

import <memory>;

import :WindowsClass;

export namespace PonyEngine::Window
{
	/// @brief Windows class data.
	struct WindowsClassData final
	{
		std::unique_ptr<WindowsClass> windowsClass; ///< Windows class.
	};
}
