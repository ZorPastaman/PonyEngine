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

export module PonyEngine.Input.Implementation;

import PonyEngine.Input.Factories;

import :InputSystemFactory;

namespace PonyEngine::Input
{
	/// @brief Creates an input system factory.
	/// @return Input system factory.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) IInputSystemFactory* CreateInputSystemFactory();
	/// @brief Destroys a previously created input system factory.
	/// @param factory Input system factory to destroy.
	export __declspec(dllexport) void DestroyInputSystemFactory(IInputSystemFactory* factory) noexcept;

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
