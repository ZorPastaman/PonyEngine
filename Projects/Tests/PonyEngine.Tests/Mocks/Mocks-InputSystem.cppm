/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:InputSystem;

import <cstddef>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Input;

export namespace Mocks
{
	class InputSystem final : public PonyEngine::Input::IInputSystemContext
	{
	public:
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyEngine::Core::ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;

		virtual void AddInputEvent(const PonyEngine::Input::InputEvent& inputEvent) override;

		std::vector<PonyEngine::Input::InputEvent> events;

		PonyEngine::Core::IEngineContext* engine = nullptr;
	};
}

namespace Mocks
{
	std::uint64_t InputSystem::FrameCount() const noexcept
	{
		return 0ULL;
	}

	PonyDebug::Log::ILogger& InputSystem::Logger() noexcept
	{
		return engine->Logger();
	}

	const PonyDebug::Log::ILogger& InputSystem::Logger() const noexcept
	{
		return engine->Logger();
	}

	const PonyEngine::Core::ISystemManager& InputSystem::SystemManager() const noexcept
	{
		return engine->SystemManager();
	}

	bool InputSystem::IsRunning() const noexcept
	{
		return true;
	}

	void InputSystem::AddInputEvent(const PonyEngine::Input::InputEvent& inputEvent)
	{
		events.emplace_back(inputEvent);
	}
}
