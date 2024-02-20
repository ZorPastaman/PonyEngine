/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Implementation:InputSystem;

import PonyEngine.Input;

namespace PonyEngine::Input
{
	export class InputSystem final : public IInputSystem
	{
	public:
		InputSystem() noexcept = default;

		virtual ~InputSystem() noexcept = default;

		virtual void Tick() override;
	};

	void InputSystem::Tick()
	{
	}
}
