/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:DeviceHandle;

export namespace PonyEngine::Input
{
	/// @brief Device handle.
	struct DeviceHandle final
	{
		const void* id = nullptr; ///< ID. It's used only by the owner. 
	};
}
