/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <exception>;
import <format>;
import <iostream>;
import <stdexcept>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Window.Implementation;

import :EngineFeatures;
import :LoggerOwnerKit;

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
		inline virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		inline virtual int GetExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

	private:
		LoggerOwnerKit m_loggerKit; /// @brief Logger and sub-logger that are owned by the @p Engine.
		Window::IEngineWindow* m_window; /// @brief Engine window. It can be nullptr.

		std::size_t m_frameCount; /// @brief Current frame.

		int m_exitCode; /// @brief Exit code. It's defined only if @p m_isRunning is @a true.
		bool m_isRunning; /// @brief @a True if the engine is running; @a false otherwise.
	};

	Engine::Engine(const EngineParams& params) :
		m_frameCount{0},
		m_isRunning{true}
	{
		m_loggerKit = CreateLogger(params.loggerParams, *this);
		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine created");

		m_window = CreateWindow(params.windowParams, *this);

		if (m_window != nullptr)
		{
			m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Show an engine window");
			m_window->ShowWindow();
		}

		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine initialized");
	}

	Engine::~Engine() noexcept
	{
		if (m_window != nullptr)
		{
			m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Destruct an engine window");
			delete m_window;
		}

		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine destructed");

		for (Debug::Log::ISubLogger* const subLogger : m_loggerKit.subLoggers)
		{
			try
			{
				m_loggerKit.logger->RemoveSubLogger(*subLogger);
			}
			catch (const std::exception& e)
			{
				std::cerr << "Exception on removing sub logger: " << e.what() << std::endl;
			}

			delete subLogger;
		}

		delete m_loggerKit.logger;
	}

	inline std::size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	inline Debug::Log::ILogger& Engine::GetLogger() const noexcept
	{
		return *m_loggerKit.logger;
	}

	inline Window::IWindow* Engine::GetWindow() const noexcept
	{
		return m_window;
	}

	inline bool Engine::IsRunning() const noexcept
	{
		return m_isRunning;
	}

	inline int Engine::GetExitCode() const noexcept
	{
		return m_exitCode;
	}

	void Engine::Stop(int exitCode) noexcept
	{
		if (m_isRunning)
		{
			m_loggerKit.logger->Log(Debug::Log::LogType::Info, std::format("Stop an engine with the exit code '{}'", exitCode));
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

		if (m_window != nullptr)
		{
			m_window->Tick();
		}

		++m_frameCount;
	}
}
