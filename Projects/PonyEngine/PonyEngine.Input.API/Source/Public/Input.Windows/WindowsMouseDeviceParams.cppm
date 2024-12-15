/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows:WindowsMouseDeviceParams;

export namespace PonyEngine::Input
{
	/// @brief Windows mouse device parameters.
	struct WindowsMouseDeviceParams final
	{
		float sensitivity = 1.f; ///< Mouse sensitivity.
	};
}
