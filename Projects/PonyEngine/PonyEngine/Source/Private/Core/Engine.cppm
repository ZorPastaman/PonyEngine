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

#include "Log/LogMacro.h"

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <exception>;
import <format>;
import <functional>;
import <iostream>;
import <stdexcept>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Log;
import PonyEngine.Window;

import :SystemManager;
import :WindowManager;

export namespace PonyEngine::Core
{
	/// @brief Pony Engine main class.
	class Engine final : public IEngine
	{
	public:
		/// @brief Creates an @p Engine with the @p params.
		/// @param params Engine parameters.
		[[nodiscard("Pure constructor")]]
		explicit Engine(const EngineParams& params);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& GetLogger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Window::IWindow* GetWindow() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int GetExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:
		Log::ILogger& m_logger; ///< Logger.

		WindowManager* m_windowManager; ///< Engine window. It can be nullptr.
		SystemManager* m_systemManager; ///< System manager.

		std::size_t m_frameCount; ///< Current frame.

		int m_exitCode; ///< Exit code. It's defined only if @p m_isRunning is @a true.
		bool m_isRunning; ///< @a True if the engine is running; @a false otherwise.
	};
}

namespace PonyEngine::Core
{
	Engine::Engine(const EngineParams& params) :
		m_logger{params.GetLogger()},
		m_frameCount{0},
		m_isRunning{true}
	{
		PONY_LOG_PTR(this, Log::LogType::Info, "Create a window manager.");
		m_windowManager = new WindowManager(params, *this);
		PONY_LOG_PTR(this, Log::LogType::Info, "Window manager created.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Create a system manager.");
		m_systemManager = new SystemManager(params, *this);
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager created.");

		m_windowManager->ShowWindow();

		PONY_LOG_PTR(this, Log::LogType::Info, "Begin a system manager.");
		m_systemManager->Begin();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager begun.");
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG_PTR(this, Log::LogType::Info, "End a system manager.");
		m_systemManager->End();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager ended.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Destroy a system manager.");
		delete m_systemManager;
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager destroyed.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Destroy a window manager.");
		delete m_windowManager;
		PONY_LOG_PTR(this, Log::LogType::Info, "Window manager destroyed.");
	}

	std::size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	Log::ILogger& Engine::GetLogger() const noexcept
	{
		return m_logger;
	}

	Window::IWindow* Engine::GetWindow() const noexcept
	{
		return m_windowManager->GetWindow();
	}

	ISystem* Engine::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
		return m_systemManager->FindSystem(predicate);
	}

	bool Engine::IsRunning() const noexcept
	{
		return m_isRunning;
	}

	int Engine::GetExitCode() const noexcept
	{
		PONY_LOG_IF_PTR(m_isRunning, this, Log::LogType::Warning, "Tried to get an exit code when the engine is still running.");

		return m_exitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (m_isRunning)
		{
			PONY_LOG_PTR(this, Log::LogType::Info, std::format("Stop an engine with the exit code '{}'.", exitCode).c_str());
			m_isRunning = false;
			m_exitCode = exitCode;
		}
		else
		{
			PONY_LOG_PTR(this, Log::LogType::Info, "Tried to stop an already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!m_isRunning)
		{
			throw std::logic_error("The engine is ticked when it's already stopped.");
		}

		PONY_LOG_PTR(this, Log::LogType::Verbose, "Tick engine.");
		m_windowManager->Tick();
		m_systemManager->Tick();

		++m_frameCount;
	}
}
