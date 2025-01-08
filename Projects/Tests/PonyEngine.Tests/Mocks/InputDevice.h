/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <cstddef>

import PonyEngine.Input;

namespace Mocks
{
	class InputDevice final : public PonyEngine::Input::Device
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::DeviceParams& deviceParams) noexcept;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		void AddInput(const PonyEngine::Input::InputEvent& input);

		std::size_t beginCount = 0;
		std::size_t endCount = 0;
		std::size_t tickCount = 0;
	};
}
