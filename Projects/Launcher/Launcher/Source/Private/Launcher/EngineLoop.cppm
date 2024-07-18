/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/EngineLog.h"

export module Launcher:EngineLoop;

import <format>;

import PonyEngine.Core;
import PonyEngine.Core.Factory;
import PonyEngine.Core.Implementation;
import PonyEngine.Log;

import :EngineSettings;
import :ILoopElement;
import :ISystemFactoriesProvider;

export namespace Launcher
{
	/// @brief Engine loop.
	class EngineLoop final : public ILoopElement
	{
	public:
		/// @brief Creates an engine loop.
		/// @param logger Logger to use.
		/// @param systemFactoriesProvider Engine system factories provider.
		/// @param engineSettings Engine settings.
		[[nodiscard("Pure constructor")]]
		EngineLoop(PonyEngine::Log::ILogger& logger, const ISystemFactoriesProvider& systemFactoriesProvider, const EngineSettings& engineSettings);
		EngineLoop(const EngineLoop&) = delete;
		EngineLoop(EngineLoop&&) = delete;

		~EngineLoop() noexcept;

		virtual bool Tick(int& exitCode) override;

		EngineLoop& operator =(const EngineLoop&) = delete;
		EngineLoop& operator =(EngineLoop&&) = delete;

	private:
		PonyEngine::Core::EngineUniquePtr engine; ///< Engine.
		PonyEngine::Log::ILogger* const logger; ///< logger;
	};
}

namespace Launcher
{
	EngineLoop::EngineLoop(PonyEngine::Log::ILogger& logger, const ISystemFactoriesProvider& systemFactoriesProvider, const EngineSettings& engineSettings) :
		logger{&logger}
	{
		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Info, "Create engine params.");
		auto engineParams = PonyEngine::Core::EngineParams(*this->logger);
		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Debug, "Add system factories.");
		systemFactoriesProvider.AddSystemFactories(engineParams);
		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Debug, "System factories added.");
		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Info, "Engine params created.");

		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Info, "Create engine.");
		engine = PonyEngine::Core::CreateEngine(engineParams);
		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Info, "Engine created.");

		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Info, "Set engine settings.");
		engine->GetTimeManager().SetTargetFrameRate(engineSettings.targetFrameRate);
		PONY_LOG_GENERAL(this->logger, PonyEngine::Log::LogType::Info, "Engine settings set.");
	}

	EngineLoop::~EngineLoop() noexcept
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy engine.");
		engine.reset();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine destroyed.");
	}

	bool EngineLoop::Tick(int& exitCode)
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Verbose, "Tick engine.");
		engine->Tick();

		if (engine->IsRunning()) [[likely]]
		{
			return false;
		}

		exitCode = engine->GetExitCode();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, std::format("Engine exited with code '{}'.", exitCode).c_str());

		return true;
	}
}
