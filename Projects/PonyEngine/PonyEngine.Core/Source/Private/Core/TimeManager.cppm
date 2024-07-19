/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/EngineLog.h"

export module PonyEngine.Core.Implementation:TimeManager;

import <chrono>;
import <cstddef>;

import PonyEngine.Core;
import PonyEngine.Log;

export namespace PonyEngine::Core
{
	/// @brief Engine time manager.
	class TimeManager final : public ITimeManager
	{
	public:
		explicit TimeManager(const IEngine& engine) noexcept;
		TimeManager(const TimeManager&) = delete;
		TimeManager(TimeManager&&) = delete;

		~TimeManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual float GetTargetFrameTime() const noexcept override;
		virtual void SetTargetFrameTime(float frameTime) noexcept override;

		/// @brief Tick the time manager.
		void Tick() noexcept;

		TimeManager& operator =(const TimeManager&) = delete;
		TimeManager& operator =(TimeManager&&) = delete;

	private:
		/// @brief Waits for the target frame time.
		void WaitForTargetTime() noexcept;

		std::chrono::duration<float> targetFrameTime; ///< Target frame time.
		std::chrono::time_point<std::chrono::steady_clock> previousTickTime; ///< Previous tick time.

		std::size_t frameCount; ///< Current frame.

		const IEngine* const engine; ///< Engine that owns the manager.
	};
}

namespace PonyEngine::Core
{
	TimeManager::TimeManager(const IEngine& engine) noexcept :
		targetFrameTime(0.f),
		frameCount{0},
		engine{&engine}
	{
	}

	std::size_t TimeManager::GetFrameCount() const noexcept
	{
		return frameCount;
	}

	float TimeManager::GetTargetFrameTime() const noexcept
	{
		return targetFrameTime.count();
	}

	void TimeManager::SetTargetFrameTime(const float frameTime) noexcept
	{
		targetFrameTime = std::chrono::duration<float>(frameTime);
	}

	void TimeManager::Tick() noexcept
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Verbose, "Wait for target frame time.");
		WaitForTargetTime();

		PONY_LOG(engine, PonyEngine::Log::LogType::Verbose, "Increase frame count.");
		++frameCount;
	}

	void TimeManager::WaitForTargetTime() noexcept
	{
		std::chrono::time_point<std::chrono::steady_clock> now;

		do
		{
			now = std::chrono::steady_clock::now();
		} while (std::chrono::duration<float>(now - previousTickTime) < targetFrameTime);

		previousTickTime = now;
	}
}
