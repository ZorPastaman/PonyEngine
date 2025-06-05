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

import <cstdint>;
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
	class EngineImpl final : public Engine, private IEngineContext
	{
	public:
		/// @brief Creates an @p Engine.
		/// @param application Application context.
		/// @param params Engine parameters.
		[[nodiscard("Pure constructor")]]
		EngineImpl(IApplicationContext& application, const EngineParams& params);
		EngineImpl(const EngineImpl&) = delete;
		EngineImpl(EngineImpl&&) = delete;

		virtual ~EngineImpl() noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode = static_cast<int>(PonyBase::Core::ExitCodes::Success)) noexcept override;

		virtual void Tick() override;

		EngineImpl& operator =(const EngineImpl&) = delete;
		EngineImpl& operator =(EngineImpl&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		/// @brief Before tick procedure.
		void BeginTick();
		/// @brief After tick procedure.
		void EndTick() noexcept;

		/// @brief Ticks systems.
		void TickSystems();

		std::uint64_t frameCount; ///< Frame count.
		int engineExitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
		bool isTicking; ///< @a True if the engine is ticking now; @a false otherwise.

		IApplicationContext* application; ///< Application

		std::unique_ptr<EngineLogger> logger; ///< Engine logger.
		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Core
{
	EngineImpl::EngineImpl(IApplicationContext& application, const EngineParams& params) :
		frameCount{0ULL},
		isRunning{true},
		isTicking{false},
		application{&application}
	{
		try
		{
			PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Create engine logger.");
			logger = std::make_unique<EngineLogger>(*static_cast<IEngineContext*>(this), this->application->Logger());
			PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Engine logger created.");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(this->application->Logger(), e, "On creating engine logger.");

			throw;
		}

		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create system manager.");
			systemManager = std::make_unique<Core::SystemManager>(*static_cast<IEngineContext*>(this));
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager created.");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On creating system manager.");

			throw;
		}

		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create systems.");
			systemManager->CreateSystems(params.systemFactories);
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
		logger.reset();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine logger destroyed.");
	}

	std::uint64_t EngineImpl::FrameCount() const noexcept
	{
		return frameCount;
	}

	ISystemManager& EngineImpl::SystemManager() noexcept
	{
		return *systemManager;
	}

	const ISystemManager& EngineImpl::SystemManager() const noexcept
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

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Tick systems.");
		TickSystems();

		EndTick();
	}

	PonyDebug::Log::ILogger& EngineImpl::Logger() noexcept
	{
		return *logger;
	}

	const PonyDebug::Log::ILogger& EngineImpl::Logger() const noexcept
	{
		return *logger;
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
}
