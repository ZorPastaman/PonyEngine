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

import <functional>;

import PonyEngine.Core;
import PonyEngine.Core.Factory;
import PonyEngine.Input.Factory;

import :InputSystem;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class InputSystemFactory final : public IInputSystemFactory, public Core::ISystemDestroyer
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
		virtual const char* GetSystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		InputSystemFactory& operator =(const InputSystemFactory&) = delete;
		InputSystemFactory& operator =(InputSystemFactory&&) = delete;

		static constexpr const char* StaticName = "PonyEngine::Input::InputSystemFactory"; ///< Class name.
	};
}

namespace PonyEngine::Input
{
	Core::SystemInfo InputSystemFactory::Create(Core::IEngine& engine)
	{
		const auto inputSystem = new InputSystem(engine);

		return Core::SystemInfo::Create<InputSystem, IInputSystem>(*inputSystem, *this, true);
	}

	void InputSystemFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<InputSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<InputSystem*>(system);
	}

	const char* InputSystemFactory::GetSystemName() const noexcept
	{
		return InputSystem::StaticName;
	}

	const char* InputSystemFactory::GetName() const noexcept
	{
		return StaticName;
	}
}
