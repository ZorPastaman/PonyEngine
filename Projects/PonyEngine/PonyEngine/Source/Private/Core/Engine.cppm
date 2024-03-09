/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <exception>;
import <format>;
import <iostream>;
import <stdexcept>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Window;

import :LoggerManager;
import :ServiceManager;
import :SystemManager;
import :WindowManager;

namespace PonyEngine::Core
{
	/// @brief Pony Engine main class.
	export class Engine final : public IEngine
	{
	public:
		/// @brief Creates an @p Engine with the @p params.
		/// @param params Engine parameters.
		[[nodiscard("Pure constructor")]]
		Engine(const EngineParams& params);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		virtual ~Engine() noexcept;

		[[nodiscard("Pure function")]]
		inline virtual std::size_t GetFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual Debug::Log::ILogger& GetLogger() const noexcept override;
		[[nodiscard("Pure function")]]
		inline virtual Window::IWindow* GetWindow() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual IServiceManager& GetServiceManager() const noexcept override;
		[[nodiscard("Pure function")]]
		inline virtual ISystemManager& GetSystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		inline virtual int GetExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

	private:
		LoggerManager* m_loggerManager; /// @brief Logger and sub-logger that are owned by the @p Engine.
		WindowManager* m_windowManager; /// @brief Engine window. It can be nullptr.

		ServiceManager* m_serviceManager; /// @brief Service manager.
		SystemManager* m_systemManager; /// @brief System manager.

		std::size_t m_frameCount; /// @brief Current frame.

		int m_exitCode; /// @brief Exit code. It's defined only if @p m_isRunning is @a true.
		bool m_isRunning; /// @brief @a True if the engine is running; @a false otherwise.
	};

	Engine::Engine(const EngineParams& params) :
		m_frameCount{0},
		m_isRunning{true}
	{
		m_loggerManager = new LoggerManager(params.subLoggerFactories, *this);
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Initialize an engine");

		m_windowManager = new WindowManager(params.windowFactory, *this);

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Create a service manager")
		m_serviceManager = new ServiceManager(params.serviceFactories, *this);
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Service manager created");
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Create a system manager");
		m_systemManager = new SystemManager(params.systemFactories, *this);
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "System manager created");

		if (m_windowManager->GetWindow() != nullptr)
		{
			PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Show an engine window");
			m_windowManager->GetWindow()->ShowWindow();
			PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Engine window shown");
		}

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Begin a service manager");
		m_serviceManager->Begin();
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Service manager begun");
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Begin a system manager");
		m_systemManager->Begin();
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "System manager begun");

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Engine initialized");
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Deinitialize an engine");
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "End a system manager");
		m_systemManager->End();
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "System manager ended");
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "End a service manager");
		m_serviceManager->End();
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Service manager ended");

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Destroy a system manager");
		delete m_systemManager;
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "System manager destroyed");

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Destroy a service manager");
		delete m_serviceManager;
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Service manager destroyed");

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Destroy an engine window");
		delete m_windowManager;
		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Engine window destroyed");

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, "Engine deinitialized");

		delete m_loggerManager;
	}

	inline std::size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	inline Debug::Log::ILogger& Engine::GetLogger() const noexcept
	{
		return m_loggerManager->GetLogger();
	}

	inline Window::IWindow* Engine::GetWindow() const noexcept
	{
		return m_windowManager->GetWindow();
	}

	inline IServiceManager& Engine::GetServiceManager() const noexcept
	{
		return *m_serviceManager;
	}

	inline ISystemManager& Engine::GetSystemManager() const noexcept
	{
		return *m_systemManager;
	}

	inline bool Engine::IsRunning() const noexcept
	{
		return m_isRunning;
	}

	inline int Engine::GetExitCode() const noexcept
	{
		PONY_LOG_IF(m_isRunning, m_loggerManager->GetLogger(), Debug::Log::LogType::Warning, "Got an exit code when the engine is still running");

		return m_exitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (m_isRunning)
		{
			PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Info, std::format("Stop an engine with the exit code '{}'", exitCode));
			m_isRunning = false;
			m_exitCode = exitCode;
		}
	}

	void Engine::Tick()
	{
		if (!m_isRunning)
		{
			throw std::logic_error("The engine is ticked when it's already stopped.");
		}

		if (m_windowManager->GetWindow() != nullptr)
		{
			PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Verbose, "Tick an engine window");
			m_windowManager->GetWindow()->Tick();
		}

		PONY_LOG(m_loggerManager->GetLogger(), Debug::Log::LogType::Verbose, "Tick a system manager");
		m_systemManager->Tick();

		++m_frameCount;
	}
}
