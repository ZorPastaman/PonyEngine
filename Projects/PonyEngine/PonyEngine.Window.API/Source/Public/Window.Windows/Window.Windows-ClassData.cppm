/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows:ClassData;

import <memory>;

import :Class;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows class data.
	struct ClassData final
	{
		std::unique_ptr<Class> windowsClass; ///< Windows class.
	};
}
