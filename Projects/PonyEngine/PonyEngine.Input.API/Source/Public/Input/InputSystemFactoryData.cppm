/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputSystemFactoryData;

import PonyBase.Memory;

import :IInputSystemFactory;

export namespace PonyEngine::Input
{
	/// @brief Input system factory data.
	struct InputSystemFactoryData final
	{
		PonyBase::Memory::UniquePointer<IInputSystemFactory> systemFactory; ///< Input system factory.
	};
}
