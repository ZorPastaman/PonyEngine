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

export module Application.Windows:WindowsEngineSetupAgent;

import PonyEngine.Time;

import TimeHelpers;

import Application;

export namespace Application
{
	/// @brief Windows engine set-up agent.
	class WindowsEngineSetupAgent final : public IEngineSetupAgent
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsEngineSetupAgent() noexcept = default;
		WindowsEngineSetupAgent(const WindowsEngineSetupAgent&) = delete;
		WindowsEngineSetupAgent(WindowsEngineSetupAgent&&) = delete;

		~WindowsEngineSetupAgent() noexcept = default;

		virtual void Setup(PonyEngine::Core::IEngine& engine) const override;

		WindowsEngineSetupAgent& operator =(const WindowsEngineSetupAgent&) = delete;
		WindowsEngineSetupAgent& operator =(WindowsEngineSetupAgent&&) = delete;
	};
}

namespace Application
{
	/// @brief Sets up a frame rate system.
	/// @param engine Target engine.
	void SetupFrameRateSystem(const PonyEngine::Core::IEngine& engine) noexcept;

	void WindowsEngineSetupAgent::Setup(PonyEngine::Core::IEngine& engine) const
	{
		SetupFrameRateSystem(engine);
	}

	void SetupFrameRateSystem(const PonyEngine::Core::IEngine& engine) noexcept
	{
		const auto frameRateSystem = engine.SystemManager().FindSystem<PonyEngine::Time::IFrameRateSystem>();
		assert(frameRateSystem && "Frame rate system is nullptr.");

		TimeHelpers::SetupFrameRateSystem(*frameRateSystem);
	}
}
