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

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <memory>;
import <stdexcept>;

import PonyEngine.Common;
import PonyEngine.Core.Factory;
import PonyEngine.Log;

import :SystemManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class Engine final : public IEngine, public ITickableEngine
	{
	public:
		/// @brief Creates an @p Engine.
		/// @param application Application.
		/// @param systemFactories System factories.
		[[nodiscard("Pure constructor")]]
		Engine(IApplication& application, const SystemFactoriesContainer& systemFactories);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::size_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode = static_cast<int>(Common::ExitCodes::Success)) noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Core::Engine"; ///< Class name.

	private:
		/// @brief Creates a system manager.
		/// @param systemFactories Engine parameters.
		/// @return Created system manager.
		[[nodiscard("Pure function")]]
		std::unique_ptr<Core::SystemManager> CreateSystemManager(const SystemFactoriesContainer& systemFactories);

		std::size_t frameCount; ///< Frame count.
		int engineExitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
		bool isTicking; ///< @a True if the engine is ticking now; @a false otherwise.

		IApplication* application; ///< Application

		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Core
{
	Engine::Engine(IApplication& application, const SystemFactoriesContainer& systemFactories) :
		frameCount{0},
		isRunning{true},
		isTicking{false},
		application{&application},
		systemManager{CreateSystemManager(systemFactories)}
	{
		PONY_LOG(this, Log::LogType::Info, "Begin system manager.");
		systemManager->Begin();
		PONY_LOG(this, Log::LogType::Info, "System manager begun.");

		PONY_LOG(this, Log::LogType::Debug, "Engine created in '{}' application.", application.Name());
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(this, Log::LogType::Info, "End system manager.");
		systemManager->End();
		PONY_LOG(this, Log::LogType::Info, "System manager ended.");

		PONY_LOG(this, Log::LogType::Info, "Destroy system manager.");
		systemManager.reset();
		PONY_LOG(this, Log::LogType::Info, "System manager destroyed.");
	}

	std::size_t Engine::FrameCount() const noexcept
	{
		return frameCount;
	}

	Log::ILogger& Engine::Logger() const noexcept
	{
		return application->Logger();
	}

	ISystemManager& Engine::SystemManager() const noexcept
	{
		return *systemManager;
	}

	bool Engine::IsRunning() const noexcept
	{
		return isRunning;
	}

	int Engine::ExitCode() const noexcept
	{
		PONY_LOG_IF(isRunning, this, Log::LogType::Warning, "Tried to get exit code when engine is still running.");

		return engineExitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			engineExitCode = exitCode;
			isRunning = false;
			PONY_LOG(this, Log::LogType::Info, "Engine stopped with exit code '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(this, Log::LogType::Info, "Tried to stop already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!isRunning) [[unlikely]]
		{
			throw std::logic_error("Engine is ticked when it's already been stopped.");
		}

		if (isTicking) [[unlikely]]
		{
			throw std::logic_error("Engine is ticked inside another tick.");
		}
		isTicking = true;

		PONY_LOG(this, Log::LogType::Verbose, "Tick system manager.");

		try
		{
			systemManager->Tick();
		}
		catch (...)
		{
			// Logging is done in the system manager.
			Stop(static_cast<int>(Common::ExitCodes::SystemTickException));
			isTicking = false;

			throw;
		}

		++frameCount;
		isTicking = false;
	}

	const char* Engine::Name() const noexcept
	{
		return StaticName;
	}

	std::unique_ptr<Core::SystemManager> Engine::CreateSystemManager(const SystemFactoriesContainer& systemFactories)
	{
		PONY_LOG(this, Log::LogType::Info, "Create system manager.");
		const auto manager = new Core::SystemManager(systemFactories, *this);
		PONY_LOG(this, Log::LogType::Info, "System manager created.");

		return std::unique_ptr<Core::SystemManager>(manager);
	}
}
