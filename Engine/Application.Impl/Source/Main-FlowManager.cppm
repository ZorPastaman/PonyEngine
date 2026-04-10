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
		void Stop(int exitCode);
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

		/// @brief Sets the flow state.
		/// @param state Flow state to set.
		void FlowState(enum FlowState state) noexcept;

		/// @brief Flow info.
		struct FlowInfo final
		{
			int exitCode; ///< Exit code.
			enum FlowState flowState; ///< Flow state.
		};

		IApplicationContext* application; ///< Application context.

		std::atomic<std::uint64_t> frameCount; ///< Frame count.
		std::atomic<FlowInfo> flowInfo; ///< Flow info.

		static_assert(std::atomic<std::uint64_t>::is_always_lock_free, "Uint64 is not lock-free");
		static_assert(std::atomic<FlowInfo>::is_always_lock_free, "(int, FlowState) struct is not lock-free");
	};
}

namespace PonyEngine::Application
{
	FlowManager::FlowManager(IApplicationContext& application) noexcept :
		application{&application},
		frameCount{0ull},
		flowInfo(FlowInfo{.exitCode = ExitCodes::InitialExitCode, .flowState = FlowState::StartingUp})
	{
	}

	std::uint64_t FlowManager::FrameCount() const noexcept
	{
		return frameCount.load(std::memory_order::relaxed);
	}

	int FlowManager::ExitCode() const noexcept
	{
		return flowInfo.load(std::memory_order::relaxed).exitCode;
	}

	enum FlowState FlowManager::FlowState() const noexcept
	{
		return flowInfo.load(std::memory_order::relaxed).flowState;
	}

	int FlowManager::Run(const std::function<void()>& begin, const std::function<void()>& end, const std::function<void()>& tick)
	{
		assert(FlowState() == FlowState::StartingUp && "The flow state is incorrect for running.");

		Begin(begin);

		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Starting application main loop.");
			for (StartRun(); IsRunning(); NextFrame())
			{
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Starting application frame: '{}'.", FrameCount());
				tick();
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Finishing application frame: '{}'.", FrameCount());
			}
			PONY_LOG(application->Logger(), Log::LogType::Info, "Finishing application main loop. Exit code: '{}'.", FrameCount());
		}
		catch (...)
		{
			End(end);
			throw;
		}

		End(end);

		return ExitCode();
	}

	void FlowManager::Stop(const int exitCode)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		if (FlowState() == FlowState::Running)
		{
			flowInfo.store(FlowInfo{.exitCode = exitCode, .flowState = FlowState::Stopped}, std::memory_order::relaxed);
			PONY_LOG(application->Logger(), Log::LogType::Info, "Application stopped. Exit code: '{}'.", ExitCode());
		}
		else
		{
			if (FlowState() == FlowState::Stopped) [[likely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Debug, "Tried to stop already stopped Application. Ignoring.");
			}
			else [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Debug, "Tried to stop Application in inappropriate state. Ignoring. Current flow state: '{}'.", FlowState());
			}
		}
	}

	void FlowManager::ShutDown() noexcept
	{
		FlowState(FlowState::ShuttingDown);
	}

	void FlowManager::Begin(const std::function<void()>& begin)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application...");
		FlowState(FlowState::Beginning);
		begin();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application done.");
	}

	void FlowManager::End(const std::function<void()>& end) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application...");
		FlowState(FlowState::Ending);
		end();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application done.");
	}

	void FlowManager::StartRun()
	{
		FlowState(FlowState::Running);
	}

	bool FlowManager::IsRunning() const noexcept
	{
		return FlowState() == FlowState::Running;
	}

	void FlowManager::NextFrame() noexcept
	{
		frameCount.fetch_add(IsRunning(), std::memory_order::relaxed);
	}

	void FlowManager::FlowState(const enum FlowState state) noexcept
	{
		flowInfo.store(FlowInfo{.exitCode = ExitCode(), .flowState = state}, std::memory_order::relaxed);
	}
}
