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

#include "PonyEngine/Log/LogMacro.h"

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
		virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int GetExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

		// TODO: set unique name
		static constexpr const char* Name = "PonyEngine::Engine";

	private:
		Log::ILogger& logger; ///< Logger.

		SystemManager* systemManager; ///< System manager.

		std::size_t frameCount; ///< Current frame.

		int exitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
	};
}

namespace PonyEngine::Core
{
	Engine::Engine(const EngineParams& params) :
		logger{params.GetLogger()},
		frameCount{0},
		isRunning{true}
	{
		PONY_LOG_PTR(this, Log::LogType::Info, "Create a system manager.");
		systemManager = new SystemManager(params, *this);
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager created.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Begin a system manager.");
		systemManager->Begin();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager begun.");

		if (const auto window = IEngine::FindSystem<Window::IWindow>())
		{
			window->ShowWindow();
		}
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG_PTR(this, Log::LogType::Info, "End a system manager.");
		systemManager->End();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager ended.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Destroy a system manager.");
		delete systemManager;
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager destroyed.");
	}

	std::size_t Engine::GetFrameCount() const noexcept
	{
		return frameCount;
	}

	Log::ILogger& Engine::GetLogger() const noexcept
	{
		return logger;
	}

	void* Engine::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		return systemManager->FindSystem(typeInfo);
	}

	bool Engine::IsRunning() const noexcept
	{
		return isRunning;
	}

	int Engine::GetExitCode() const noexcept
	{
		PONY_LOG_IF_PTR(isRunning, this, Log::LogType::Warning, "Tried to get an exit code when the engine is still running.");

		return exitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			PONY_LOG_PTR(this, Log::LogType::Info, std::format("Stop an engine with the exit code '{}'.", exitCode).c_str());
			isRunning = false;
			this->exitCode = exitCode;
		}
		else
		{
			PONY_LOG_PTR(this, Log::LogType::Info, "Tried to stop an already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!isRunning)
		{
			throw std::logic_error("The engine is ticked when it's already stopped.");
		}

		PONY_LOG_PTR(this, Log::LogType::Verbose, "Tick engine.");
		systemManager->Tick();

		++frameCount;
	}

	const char* Engine::GetName() const noexcept
	{
		return Name;
	}
}
