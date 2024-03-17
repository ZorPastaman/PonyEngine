/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Implementation;

import PonyEngine.Input.Factories;

import :InputSystemFactory;

namespace PonyEngine::Input
{
	export __declspec(dllexport) IInputSystemFactory* CreateInputSystemFactory();
	export __declspec(dllexport) void DestroyInputSystemFactory(IInputSystemFactory* factory);

	IInputSystemFactory* CreateInputSystemFactory()
	{
		return new InputSystemFactory();
	}

	void DestroyInputSystemFactory(IInputSystemFactory* factory)
	{
		delete static_cast<InputSystemFactory*>(factory);
	}
}
