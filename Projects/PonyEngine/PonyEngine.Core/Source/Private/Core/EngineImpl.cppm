/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Core.Detail:EngineImpl;

import <cstddef>;
import <exception>;
import <memory>;
import <stdexcept>;

import PonyBase.Core;

import PonyDebug.Log;

import PonyEngine.Core;

import :EngineLogger;
import :SystemManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class EngineImpl final : public Engine, public IEngineContext
	{
	public:
		/// @brief Creates an @p Engine.
		/// @param application Application context.
		/// @param systemFactories System factories.
		[[nodiscard("Pure constructor")]]
		EngineImpl(IApplicationContext& application, const SystemFactoriesContainer& systemFactories);
		EngineImpl(const EngineImpl&) = delete;
		EngineImpl(EngineImpl&&) = delete;

		virtual ~EngineImpl() noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::size_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode = static_cast<int>(PonyBase::Core::ExitCodes::Success)) noexcept override;

		virtual void Tick() override;

		EngineImpl& operator =(const EngineImpl&) = delete;
		EngineImpl& operator =(EngineImpl&&) = delete;

	private:
		/// @brief Before tick procedure.
		void BeginTick();
		/// @brief After tick procedure.
		void EndTick() noexcept;

		/// @brief Ticks systems.
		void TickSystems();

		/// @brief Creates an engine logger.
		/// @return Created engine logger.
		[[nodiscard("Pure function")]]
		std::unique_ptr<EngineLogger> CreateEngineLogger();

		/// @brief Creates a system manager.
		/// @return Created system manager.
		[[nodiscard("Pure function")]]
		std::unique_ptr<Core::SystemManager> CreateSystemManager();

		std::size_t frameCount; ///< Frame count.
		int engineExitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
		bool isTicking; ///< @a True if the engine is ticking now; @a false otherwise.

		IApplicationContext* application; ///< Application

		std::unique_ptr<EngineLogger> engineLogger; ///< Engine logger.
		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Core
{
	EngineImpl::EngineImpl(IApplicationContext& application, const SystemFactoriesContainer& systemFactories) :
		frameCount{0},
		isRunning{true},
		isTicking{false},
		application{&application},
		engineLogger{CreateEngineLogger()},
		systemManager{CreateSystemManager()}
	{
		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create systems.");
			systemManager->CreateSystems(systemFactories);
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Systems created.");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On creating systems.");

			throw;
		}

		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Begin systems.");
			systemManager->BeginSystems();
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Systems begun.");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On beginning systems.");

			throw;
		}
	}

	EngineImpl::~EngineImpl() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "End systems.");
		systemManager->EndSystems();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Systems ended.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy systems.");
		systemManager->DestroySystems();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Systems destroyed.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy system manager.");
		systemManager.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager destroyed.");

		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy engine logger.");
		engineLogger.reset();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine logger destroyed.");
	}

	std::size_t EngineImpl::FrameCount() const noexcept
	{
		return frameCount;
	}

	PonyDebug::Log::ILogger& EngineImpl::Logger() const noexcept
	{
		return *engineLogger;
	}

	ISystemManager& EngineImpl::SystemManager() const noexcept
	{
		return *systemManager;
	}

	bool EngineImpl::IsRunning() const noexcept
	{
		return isRunning;
	}

	int EngineImpl::ExitCode() const noexcept
	{
		PONY_LOG_IF(isRunning, Logger(), PonyDebug::Log::LogType::Warning, "Tried to get exit code when engine is still running.");

		return engineExitCode;
	}

	void EngineImpl::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			engineExitCode = exitCode;
			isRunning = false;
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Engine stopped with exit code '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Tried to stop already stopped engine. Ignore it.");
		}
	}

	void EngineImpl::Tick()
	{
		BeginTick();

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Tick system manager.");
		TickSystems();

		EndTick();
	}

	void EngineImpl::BeginTick()
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
	}

	void EngineImpl::EndTick() noexcept
	{
		isTicking = false;
		++frameCount;
	}

	void EngineImpl::TickSystems()
	{
		try
		{
			systemManager->TickSystems();
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On ticking system manager.");
			Stop(static_cast<int>(PonyBase::Core::ExitCodes::SystemManagerTickException));

			throw;
		}
	}

	std::unique_ptr<EngineLogger> EngineImpl::CreateEngineLogger()
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create engine logger.");
			auto logger = std::make_unique<EngineLogger>(*this, application->Logger());
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine logger created.");

			return logger;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating engine logger.");

			throw;
		}
	}

	std::unique_ptr<Core::SystemManager> EngineImpl::CreateSystemManager()
	{
		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create system manager.");
			auto manager = std::make_unique<Core::SystemManager>(*this);
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager created.");

			return manager;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On creating system manager.");

			throw;
		}
	}
}
