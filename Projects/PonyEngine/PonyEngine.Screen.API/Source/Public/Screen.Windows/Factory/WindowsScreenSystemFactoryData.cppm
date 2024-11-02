/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Factory:WindowsScreenSystemFactoryData;

import PonyBase.Memory;

import PonyEngine.Core.Factory;

import :IWindowsScreenSystemFactory;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system factory data.
	struct WindowsScreenSystemFactoryData final
	{
		PonyBase::Memory::UniquePointer<IWindowsScreenSystemFactory> systemFactory; ///< System factory.
	};
}
