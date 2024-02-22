/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Implementation:InputSystemFactory;

import <cassert>;

import PonyEngine.Input;

import :InputSystem;

namespace PonyEngine::Input
{
	export [[nodiscard("Pure function")]] __declspec(dllexport) IInputSystem* CreateInputSystem();

	export __declspec(dllexport) void DestroyInputSystem(IInputSystem* inputSystem);

	IInputSystem* CreateInputSystem()
	{
		return new InputSystem();
	}

	void DestroyInputSystem(IInputSystem* inputSystem)
	{
		assert((inputSystem != nullptr));
		delete static_cast<InputSystem*>(inputSystem);
	}
}
