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
#include <vector>

import PonyEngine.Core;
import PonyEngine.Input;

namespace Mocks
{
	class InputSystem final : public PonyEngine::Input::IInputSystemContext
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::ISystemManager& SystemManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyEngine::Core::ISystemManager& SystemManager() const noexcept override;

		virtual void AddInputEvent(const PonyEngine::Input::InputEvent& inputEntry) override;

		std::vector<PonyEngine::Input::InputEvent> events;

		PonyEngine::Core::IEngineContext* engine = nullptr;
	};
}
