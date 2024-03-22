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

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <exception>;
import <format>;
import <functional>;
import <iostream>;
import <stdexcept>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;
import PonyEngine.Window;

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
		inline virtual IService* FindService(const std::function<bool(const IService*)>& predicate) const override;
		[[nodiscard("Pure function")]]
		inline virtual ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const override;

		[[nodiscard("Pure function")]]
		inline virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		inline virtual int GetExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:
		Debug::Log::ILogger* const m_logger; /// @brief Logger.

		WindowManager* m_windowManager; /// @brief Engine window. It can be nullptr.

		ServiceManager* m_serviceManager; /// @brief Service manager.
		SystemManager* m_systemManager; /// @brief System manager.

		std::size_t m_frameCount; /// @brief Current frame.

		int m_exitCode; /// @brief Exit code. It's defined only if @p m_isRunning is @a true.
		bool m_isRunning; /// @brief @a True if the engine is running; @a false otherwise.
	};

	Engine::Engine(const EngineParams& params) :
		m_logger{params.logger},
		m_frameCount{0},
		m_isRunning{true}
	{
		assert((m_logger != nullptr));

		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Create a window manager.");
		m_windowManager = new WindowManager(params.windowFactory, *this);
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Window manager created.");

		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Create a service manager.");
		m_serviceManager = new ServiceManager(params.serviceFactories, *this);
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Service manager created.");
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Create a system manager.");
		m_systemManager = new SystemManager(params.systemFactories, *this);
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "System manager created.");

		m_windowManager->ShowWindow();

		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Begin a service manager.");
		m_serviceManager->Begin();
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Service manager begun.");
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Begin a system manager.");
		m_systemManager->Begin();
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "System manager begun.");
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "End a system manager.");
		m_systemManager->End();
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "System manager ended.");
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "End a service manager.");
		m_serviceManager->End();
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Service manager ended.");

		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Destroy a system manager.");
		delete m_systemManager;
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "System manager destroyed.");

		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Destroy a service manager.");
		delete m_serviceManager;
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Service manager destroyed.");

		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Destroy a window manager.");
		delete m_windowManager;
		PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Window manager destroyed.");
	}

	inline std::size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	inline Debug::Log::ILogger& Engine::GetLogger() const noexcept
	{
		return *m_logger;
	}

	inline Window::IWindow* Engine::GetWindow() const noexcept
	{
		return m_windowManager->GetWindow();
	}

	inline IService* Engine::FindService(const std::function<bool(const IService*)>& predicate) const
	{
		return m_serviceManager->FindService(predicate);
	}

	inline ISystem* Engine::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
		return m_systemManager->FindSystem(predicate);
	}

	inline bool Engine::IsRunning() const noexcept
	{
		return m_isRunning;
	}

	inline int Engine::GetExitCode() const noexcept
	{
		PONY_LOG_IF_PTR(m_isRunning, this, Debug::Log::LogType::Warning, "Tried to get an exit code when the engine is still running.");

		return m_exitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (m_isRunning)
		{
			PONY_LOG_PTR(this, Debug::Log::LogType::Info, std::format("Stop an engine with the exit code '{}'.", exitCode).c_str());
			m_isRunning = false;
			m_exitCode = exitCode;
		}
		else
		{
			PONY_LOG_PTR(this, Debug::Log::LogType::Info, "Tried to stop an already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!m_isRunning)
		{
			throw std::logic_error("The engine is ticked when it's already stopped.");
		}

		PONY_LOG_PTR(this, Debug::Log::LogType::Verbose, "Tick engine.");
		m_windowManager->Tick();
		m_systemManager->Tick();

		++m_frameCount;
	}
}
