/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Core/Linking.h"

export module PonyEngine.Input.Implementation;

import :InputSystemFactory;

export namespace PonyEngine::Input
{
	/// @brief Creates an input system factory.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT IInputSystemFactory* CreateInputSystemFactory();
	/// @brief Destroys a previously created input system factory.
	/// @param factory Input system factory to destroy.
	PONY_DLL_EXPORT void DestroyInputSystemFactory(IInputSystemFactory* factory) noexcept;
}

namespace PonyEngine::Input
{
	IInputSystemFactory* CreateInputSystemFactory()
	{
		return new InputSystemFactory();
	}

	void DestroyInputSystemFactory(IInputSystemFactory* factory) noexcept
	{
		assert((dynamic_cast<InputSystemFactory*>(factory) != nullptr));
		delete static_cast<InputSystemFactory*>(factory);
	}
}
