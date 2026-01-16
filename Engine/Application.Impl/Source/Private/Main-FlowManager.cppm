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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:FlowManager;

import std;

import PonyEngine.Application.Ext;
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
		/// @brief Gets the flow state.
		/// @return Flow state.
		[[nodiscard("Pure function")]]
		enum FlowState FlowState() const noexcept;

		/// @brief Runs the flow.
		/// @param begin Begin function.
		/// @param end End function. Must be noexcept.
		/// @param tick Tick function.
		/// @return Exit code.
		int Run(const std::function<void()>& begin, const std::function<void()>& end, const std::function<void()>& tick);
		/// @brief Stops the flow.
		/// @param exitCode Exit code.
		void Stop(int exitCode) noexcept;
		/// @brief Shuts down the flow.
		void ShutDown() noexcept;

		FlowManager& operator =(const FlowManager&) = delete;
		FlowManager& operator =(FlowManager&&) = delete;

	private:
		/// @brief Begins the flow.
		/// @param begin Begin function.
		void Begin(const std::function<void()>& begin);
		/// @brief Ends the flow.
		/// @param end End function.
		void End(const std::function<void()>& end) noexcept;

		/// @brief Starts a run.
		void StartRun();
		/// @brief Checks if the flow is running.
		/// @return @a True if it's running; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsRunning() const noexcept;
		/// @brief Increments the frame count.
		void NextFrame() noexcept;

		IApplicationContext* application; ///< Application context.

		std::uint64_t frameCount; ///< Frame count.
		int exitCode; ///< Exit code.
		enum FlowState flowState; ///< Flow state.
	};
}

namespace PonyEngine::Application
{
	FlowManager::FlowManager(IApplicationContext& application) noexcept :
		application{&application},
		frameCount{0ull},
		exitCode{ExitCodes::InitialExitCode},
		flowState{FlowState::StartingUp}
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

	int FlowManager::Run(const std::function<void()>& begin, const std::function<void()>& end, const std::function<void()>& tick)
	{
		assert(flowState == FlowState::StartingUp && "The flow state is incorrect for running.");

		Begin(begin);

		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Starting application main loop.");
			for (StartRun(); IsRunning(); NextFrame())
			{
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Starting application frame: '{}'.", frameCount);
				tick();
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Finishing application frame: '{}'.", frameCount);
			}
			PONY_LOG(application->Logger(), Log::LogType::Info, "Finishing application main loop. Exit code: '{}'.", exitCode);
		}
		catch (...)
		{
			End(end);
			throw;
		}

		End(end);

		return exitCode;
	}

	void FlowManager::Stop(const int exitCode) noexcept
	{
		if (flowState == FlowState::Running)
		{
			this->exitCode = exitCode;
			flowState = FlowState::Stopped;
			PONY_LOG(application->Logger(), Log::LogType::Info, "Application stopped. Exit code: '{}'.", this->exitCode);
		}
		else
		{
			if (flowState == FlowState::Stopped) [[likely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Debug, "Tried to stop already stopped Application. Ignoring.");
			}
			else [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Debug, "Tried to stop Application in inappropriate state. Ignoring. Current flow state: '{}'.", flowState);
			}
		}
	}

	void FlowManager::ShutDown() noexcept
	{
		flowState = FlowState::ShuttingDown;
	}

	enum FlowState FlowManager::FlowState() const noexcept
	{
		return flowState;
	}

	void FlowManager::Begin(const std::function<void()>& begin)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application...");
		flowState = FlowState::Beginning;
		begin();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application done.");
	}

	void FlowManager::End(const std::function<void()>& end) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application...");
		flowState = FlowState::Ending;
		end();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application done.");
	}

	void FlowManager::StartRun()
	{
		flowState = FlowState::Running;
	}

	bool FlowManager::IsRunning() const noexcept
	{
		return flowState == FlowState::Running;
	}

	void FlowManager::NextFrame() noexcept
	{
		frameCount += IsRunning();
	}
}
