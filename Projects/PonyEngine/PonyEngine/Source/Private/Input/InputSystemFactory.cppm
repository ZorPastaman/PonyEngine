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

export module PonyEngine.Input.Implementation:InputSystemFactory;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Input.Factories;

import :InputSystem;

export namespace PonyEngine::Input
{
	class InputSystemFactory final : public IInputSystemFactory
	{
	public:
		InputSystemFactory() noexcept = default;
		InputSystemFactory(const InputSystemFactory&) = delete;
		InputSystemFactory(InputSystemFactory&&) = delete;

		~InputSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemInfo Create(Core::IEngine& engine) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept override;

		InputSystemFactory& operator =(const InputSystemFactory&) = delete;
		InputSystemFactory& operator =(InputSystemFactory&&) = delete;

		static constexpr const char* Name = "PonyEngine::Input::InputSystemFactory";
	};
}

namespace PonyEngine::Input
{
	Core::SystemInfo InputSystemFactory::Create(Core::IEngine& engine)
	{
		const auto inputSystem = new InputSystem(engine);

		Core::SystemInfo systemInfo;
		systemInfo.system = inputSystem;

		systemInfo.interfaces.AddObjectInterface<IInputSystem>(inputSystem);

		return systemInfo;
	}

	void InputSystemFactory::Destroy(Core::ISystem* system) noexcept
	{
		assert((dynamic_cast<InputSystem*>(system) != nullptr));
		delete static_cast<InputSystem*>(system);
	}

	const char* InputSystemFactory::GetName() const noexcept
	{
		return Name;
	}

	const char* InputSystemFactory::GetSystemName() const noexcept
	{
		return InputSystem::Name;
	}
}
