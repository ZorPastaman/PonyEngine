/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:Application;

import PonyEngine.Core;

export namespace Mocks
{
	class Application final : public PonyEngine::Core::IApplicationContext
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		PonyDebug::Log::ILogger* logger = nullptr;
	};
}

namespace Mocks
{
	PonyDebug::Log::ILogger& Application::Logger() noexcept
	{
		return *logger;
	}

	const PonyDebug::Log::ILogger& Application::Logger() const noexcept
	{
		return *logger;
	}
}
