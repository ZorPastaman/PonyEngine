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
	/// @brief Creates an input system.
	/// @param engine Engine that owns the input system.
	/// @return Created input system.
	export [[nodiscard("Pure function")]] 
	__declspec(dllexport) IInputSystem* CreateInputSystem(Core::IEngine& engine);

	/// @brief Destroys an input system.
	/// @param inputSystem Input system to destroy.
	export __declspec(dllexport) void DestroyInputSystem(IInputSystem* inputSystem) noexcept;

	/// @brief Creates a factory info wrapper over functions @p CreateInputSystem() and DestroyInputSystem().
	/// @return Created factory info wrapper.
	export [[nodiscard("Pure function")]] 
	__declspec(dllexport) Core::SystemFactoryInfo CreateSystemFactoryInfo();

	IInputSystem* CreateInputSystem(Core::IEngine& engine)
	{
		return new InputSystem(engine);
	}

	void DestroyInputSystem(IInputSystem* const inputSystem) noexcept
	{
		assert((dynamic_cast<InputSystem*>(inputSystem) != nullptr));
		delete static_cast<InputSystem*>(inputSystem);
	}

	Core::SystemFactoryInfo CreateSystemFactoryInfo()
	{
		static const std::function<Core::ISystem*(Core::IEngine&)> createInputSystem = &CreateInputSystem;
		static const std::function<void(Core::ISystem*)> destroyInputSystem = [](Core::ISystem* system) 
		{
			assert((dynamic_cast<IInputSystem*>(system) != nullptr));
			DestroyInputSystem(static_cast<IInputSystem*>(system)); 
		};

		return Core::SystemFactoryInfo(createInputSystem, destroyInputSystem);
	}
}
