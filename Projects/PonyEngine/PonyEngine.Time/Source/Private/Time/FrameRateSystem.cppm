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

export module PonyEngine.Time.Detail:FrameRateSystem;

import <chrono>;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Time;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system.
	class FrameRateSystem final : public Core::TickableSystem, public IFrameRateSystem
	{
	public:
		/// @brief Creates a @p FrameRateSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param frameRateParams Frame rate system parameters.
		[[nodiscard("Pure constructor")]]
		FrameRateSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const FrameRateSystemParams& frameRateParams) noexcept;
		FrameRateSystem(const FrameRateSystem&) = delete;
		FrameRateSystem(FrameRateSystem&&) = delete;

		virtual ~FrameRateSystem() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual float TargetFrameTime() const noexcept override;
		virtual void TargetFrameTime(float frameTime) noexcept override;

		FrameRateSystem& operator =(const FrameRateSystem&) = delete;
		FrameRateSystem& operator =(FrameRateSystem&&) = delete;

	private:
		std::chrono::duration<float> targetFrameTime; ///< Target frame time.
		std::chrono::time_point<std::chrono::steady_clock> previousTickTime; ///< Previous tick time.
	};
}

namespace PonyEngine::Time
{
	FrameRateSystem::FrameRateSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const FrameRateSystemParams& frameRateParams) noexcept :
		TickableSystem(engine, systemParams),
		targetFrameTime(frameRateParams.targetFrameTime)
	{
	}

	void FrameRateSystem::Begin()
	{
	}

	void FrameRateSystem::End()
	{
	}

	void FrameRateSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Wait for target frame time: '{}'.", targetFrameTime);
		std::chrono::time_point<std::chrono::steady_clock> now;

		do
		{
			now = std::chrono::steady_clock::now();
		} while (std::chrono::duration<float>(now - previousTickTime) < targetFrameTime);

		previousTickTime = now;
	}

	float FrameRateSystem::TargetFrameTime() const noexcept
	{
		return targetFrameTime.count();
	}

	void FrameRateSystem::TargetFrameTime(const float frameTime) noexcept
	{
		targetFrameTime = std::chrono::duration<float>(frameTime);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Target frame time set to '{}'.", targetFrameTime);
	}
}
