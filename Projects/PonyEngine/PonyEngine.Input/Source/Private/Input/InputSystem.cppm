/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Implementation:InputSystem;

import <string>;

import PonyEngine.Input;

namespace PonyEngine::Input
{
	export class InputSystem final : public IInputSystem
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputSystem() noexcept = default;

		virtual ~InputSystem() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::string& GetName() const noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;
	};

	const std::string& InputSystem::GetName() const noexcept
	{
		static const std::string name = "PonyEngine::Input::InputSystem";
		return name;
	}

	void InputSystem::Begin()
	{
	}

	void InputSystem::End()
	{
	}

	void InputSystem::Tick()
	{
	}
}
