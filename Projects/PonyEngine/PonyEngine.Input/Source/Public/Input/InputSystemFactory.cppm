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
import <functional>;

import PonyEngine.Core;
import PonyEngine.Input;

import :InputSystem;

namespace PonyEngine::Input
{
	export [[nodiscard("Pure function")]] 
	__declspec(dllexport) IInputSystem* CreateInputSystem(Core::IEngine& engine);

	export __declspec(dllexport) void DestroyInputSystem(IInputSystem* inputSystem) noexcept;

	export [[nodiscard("Pure function")]] 
	__declspec(dllexport) Core::SystemFactoryInfo CreateSystemFactoryInfo();

	IInputSystem* CreateInputSystem(Core::IEngine& engine)
	{
		return new InputSystem();
	}

	void DestroyInputSystem(IInputSystem* const inputSystem) noexcept
	{
		assert((dynamic_cast<InputSystem*>(inputSystem) != nullptr));
		delete static_cast<InputSystem*>(inputSystem);
	}

	Core::SystemFactoryInfo CreateSystemFactoryInfo()
	{
		const std::function<Core::ISystem*(Core::IEngine&)> createInputSystem = &CreateInputSystem;
		const std::function<void(Core::ISystem*)> destroyInputSystem = [](Core::ISystem* system) 
		{
			assert((dynamic_cast<IInputSystem*>(system) != nullptr));
			DestroyInputSystem(static_cast<IInputSystem*>(system)); 
		};

		return Core::SystemFactoryInfo(createInputSystem, destroyInputSystem);
	}
}
