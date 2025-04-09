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

export module PonyEngine.Time.Detail:TimeSystem;

import <cmath>;
import <cstdint>;
import <chrono>;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Time;

export namespace PonyEngine::Time
{
	/// @brief Time system.
	class TimeSystem final : public Core::TickableSystem, public ITimeSystem
	{
	public:
		/// @brief Creates a @p TimeSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param timeParams Time system parameters.
		[[nodiscard("Pure constructor")]]
		TimeSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const TimeSystemParams& timeParams) noexcept;
		[[nodiscard("Pure constructor")]]
		TimeSystem(const TimeSystem& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		TimeSystem(TimeSystem&& other) noexcept = default;

		virtual ~TimeSystem() noexcept override = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void Tick() noexcept override;

		[[nodiscard("Pure function")]]
		virtual double RealTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual double VirtualTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual double UnscaledVirtualTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealFrameCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFrameCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual float RealDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual float VirtualDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual float UnscaledVirtualDeltaTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t RealDeltaFrame() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t VirtualDeltaFrame() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t UnscaledVirtualDeltaFrame() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual float DeltaTimeCap() const noexcept override;
		virtual void DeltaTimeCap(float cap) noexcept override;

		[[nodiscard("Pure function")]]
		virtual float TimeScale() const noexcept override;
		virtual void TimeScale(float scale) noexcept override;

		[[nodiscard("Pure function")]]
		virtual float FramePeriod() const noexcept override;
		virtual void FramePeriod(float period) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> EngineStartTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> PrevFrameTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> ThisFrameTimePoint() const noexcept override;

		TimeSystem& operator =(const TimeSystem& other) noexcept = default;
		TimeSystem& operator =(TimeSystem&& other) noexcept = default;

	private:
		float deltaTimeCap; ///< Delta time cap.
		float timeScale; ///< Time scale.
		float framePeriod; ///< Frame period.

		std::chrono::time_point<std::chrono::steady_clock> engineStartTimePoint; ///< Engine start time point.
		std::chrono::time_point<std::chrono::steady_clock> prevFrameTimePoint; ///< Previous frame time point.
		std::chrono::time_point<std::chrono::steady_clock> thisFrameTimePoint; ///< This frame time point.

		double realTime; ///< Real time elapsed since the engine start in seconds.
		double unscaledVirtualTime; ///< Unscaled virtual time elapsed since the engine start in seconds.
		double virtualTime; ///< Virtual time elapsed since the engine start in seconds.

		std::uint64_t realFrameCount; ///< Real frame count since the engine start.
		std::uint64_t unscaledVirtualFrameCount; ///< Unscaled virtual frame count since the engine start.
		std::uint64_t virtualFrameCount; ///< Virtual frame count since the engine start.

		float realDeltaTime; ///< Real delta time.
		float unscaledVirtualDeltaTime; ///< Unscaled virtual delta time.
		float virtualDeltaTime; ///< Virtual delta time.

		std::uint32_t realDeltaFrame; ///< Real delta frame.
		std::uint32_t unscaledVirtualDeltaFrame; ///< Unscaled virtual delta frame.
		std::uint32_t virtualDeltaFrame; ///< Virtual delta frame.

		float realTimeAccumulator; ///< Real time accumulator.
		float unscaledVirtualTimeAccumulator; ///< Unscaled virtual time accumulator.
		float virtualTimeAccumulator; ///< Virtual time accumulator.
	};
}

namespace PonyEngine::Time
{
	TimeSystem::TimeSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const TimeSystemParams& timeParams) noexcept :
		TickableSystem(engine, systemParams),
		deltaTimeCap{timeParams.deltaTimeCap},
		timeScale{timeParams.timeScale},
		framePeriod{timeParams.framePeriod},
		engineStartTimePoint(std::chrono::steady_clock::now()),
		prevFrameTimePoint(engineStartTimePoint),
		thisFrameTimePoint(engineStartTimePoint),
		realTime{0.},
		unscaledVirtualTime{0.},
		virtualTime{0.},
		realFrameCount{0ULL},
		unscaledVirtualFrameCount{0ULL},
		virtualFrameCount{0ULL},
		realDeltaTime{0.f},
		unscaledVirtualDeltaTime{0.f},
		virtualDeltaTime{0.f},
		realDeltaFrame{0u},
		unscaledVirtualDeltaFrame{0u},
		virtualDeltaFrame{0u},
		realTimeAccumulator{0.f},
		unscaledVirtualTimeAccumulator{0.f},
		virtualTimeAccumulator{0.f}
	{
	}

	void TimeSystem::Begin() noexcept
	{
	}

	void TimeSystem::End() noexcept
	{
	}

	void TimeSystem::Tick() noexcept
	{
		prevFrameTimePoint = thisFrameTimePoint;
		thisFrameTimePoint = std::chrono::steady_clock::now();

		realDeltaTime = std::chrono::duration<float>(thisFrameTimePoint - prevFrameTimePoint).count();
		unscaledVirtualDeltaTime = std::min(realDeltaTime, deltaTimeCap);
		virtualDeltaTime = unscaledVirtualDeltaTime * timeScale;

		realTime = std::chrono::duration<double>(thisFrameTimePoint - engineStartTimePoint).count();
		unscaledVirtualTime += unscaledVirtualDeltaTime;
		virtualTime += virtualDeltaTime;

		realTimeAccumulator += realDeltaTime;
		unscaledVirtualTimeAccumulator += unscaledVirtualDeltaTime;
		virtualTimeAccumulator += virtualDeltaTime;

		realDeltaFrame = 0u;
		unscaledVirtualDeltaFrame = 0u;
		virtualDeltaFrame = 0u;
		while (realTimeAccumulator > framePeriod)
		{
			++realDeltaFrame;
			realTimeAccumulator -= framePeriod;
		}
		while (unscaledVirtualTimeAccumulator > framePeriod)
		{
			++unscaledVirtualDeltaFrame;
			unscaledVirtualTimeAccumulator -= framePeriod;
		}
		while (virtualTimeAccumulator > framePeriod)
		{
			++virtualDeltaFrame;
			virtualTimeAccumulator -= framePeriod;
		}

		realFrameCount += realDeltaFrame;
		unscaledVirtualFrameCount += unscaledVirtualDeltaFrame;
		virtualFrameCount += virtualDeltaFrame;
	}

	double TimeSystem::RealTime() const noexcept
	{
		return realTime;
	}

	double TimeSystem::VirtualTime() const noexcept
	{
		return virtualTime;
	}

	double TimeSystem::UnscaledVirtualTime() const noexcept
	{
		return unscaledVirtualTime;
	}

	std::uint64_t TimeSystem::RealFrameCount() const noexcept
	{
		return realFrameCount;
	}

	std::uint64_t TimeSystem::VirtualFrameCount() const noexcept
	{
		return virtualFrameCount;
	}

	std::uint64_t TimeSystem::UnscaledVirtualFrameCount() const noexcept
	{
		return unscaledVirtualFrameCount;
	}

	float TimeSystem::RealDeltaTime() const noexcept
	{
		return realDeltaTime;
	}

	float TimeSystem::VirtualDeltaTime() const noexcept
	{
		return virtualDeltaTime;
	}

	float TimeSystem::UnscaledVirtualDeltaTime() const noexcept
	{
		return unscaledVirtualDeltaTime;
	}

	std::uint32_t TimeSystem::RealDeltaFrame() const noexcept
	{
		return realDeltaFrame;
	}

	std::uint32_t TimeSystem::VirtualDeltaFrame() const noexcept
	{
		return virtualDeltaFrame;
	}

	std::uint32_t TimeSystem::UnscaledVirtualDeltaFrame() const noexcept
	{
		return unscaledVirtualDeltaFrame;
	}

	float TimeSystem::DeltaTimeCap() const noexcept
	{
		return deltaTimeCap;
	}

	void TimeSystem::DeltaTimeCap(const float cap) noexcept
	{
		deltaTimeCap = cap;
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Delta time cap set to '{}'.", deltaTimeCap);
	}

	float TimeSystem::TimeScale() const noexcept
	{
		return timeScale;
	}

	void TimeSystem::TimeScale(const float scale) noexcept
	{
		timeScale = scale;
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Time scale set to '{}'.", timeScale);
	}

	float TimeSystem::FramePeriod() const noexcept
	{
		return framePeriod;
	}

	void TimeSystem::FramePeriod(const float period) noexcept
	{
		framePeriod = period;
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Frame period set to '{}'.", framePeriod);
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeSystem::EngineStartTimePoint() const noexcept
	{
		return engineStartTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeSystem::PrevFrameTimePoint() const noexcept
	{
		return prevFrameTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeSystem::ThisFrameTimePoint() const noexcept
	{
		return thisFrameTimePoint;
	}
}
