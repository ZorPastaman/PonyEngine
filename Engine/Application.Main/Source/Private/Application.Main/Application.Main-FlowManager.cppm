/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Main:FlowManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :ExitCodes;

export namespace PonyEngine::Application
{
	/// @brief Flow manager.
	class FlowManager final
	{
	public:
		/// @brief Creates a flow manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit FlowManager(IApplicationContext& application) noexcept;
		FlowManager(const FlowManager&) = delete;
		FlowManager(FlowManager&&) = delete;

		~FlowManager() noexcept = default;

		/// @brief Gets the frame count.
		/// @return Frame count.
		[[nodiscard("Pure function")]]
		std::uint64_t FrameCount() const noexcept;
		/// @brief Gets the exit code.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		int ExitCode() const noexcept;
		/// @brief Checks if the application is running.
		/// @return @a True if it's running; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsRunning() const noexcept;

		/// @brief Increments the frame count.
		void Next() noexcept;
		/// @brief Stops the application.
		/// @param exitCode Exit code. It's ignored if the application is already stopped.
		void Stop(int exitCode) noexcept;

		FlowManager& operator =(const FlowManager&) = delete;
		FlowManager& operator =(FlowManager&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.

		std::uint64_t frameCount; ///< Frame count.
		int exitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
	};
}

namespace PonyEngine::Application
{
	FlowManager::FlowManager(IApplicationContext& application) noexcept :
		application{&application},
		frameCount{0ull},
		exitCode{ExitCodes::InitialExitCode},
		isRunning{true}
	{
	}

	std::uint64_t FlowManager::FrameCount() const noexcept
	{
		return frameCount;
	}

	int FlowManager::ExitCode() const noexcept
	{
		return exitCode;
	}

	bool FlowManager::IsRunning() const noexcept
	{
		return isRunning;
	}

	void FlowManager::Next() noexcept
	{
		++frameCount;
	}

	void FlowManager::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			this->exitCode = exitCode;
			isRunning = false;
			PONY_LOG(application->Logger(), Log::LogType::Info, "Application is stopped. Exit code: '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Application is stopped when it's not running. Ignoring.");
		}
	}
}
