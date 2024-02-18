/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IWindow;

namespace PonyEngine::Window
{
	/// @brief Engine window interface.
	export class IWindow
	{
	protected:
		virtual ~IWindow() = default;
	};
}
