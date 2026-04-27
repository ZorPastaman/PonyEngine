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

export module PonyEngine.Time.Impl:TimeService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Time;

export namespace PonyEngine::Time
{
	/// @brief Time service.
	class TimeService final : public Application::IService, private Application::ITickableService, private ITimeService
	{
	public:
		/// @brief Creates a time service.
		[[nodiscard("Pure constructor")]]
		explicit TimeService(Application::IApplicationContext& application) noexcept;
		TimeService(const TimeService&) = delete;
		TimeService(TimeService&&) = delete;

		~TimeService() noexcept = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void AddTickableServices(Application::ITickableServiceAdder& adder) override;
		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		TimeService& operator =(const TimeService&) = delete;
		TimeService& operator =(TimeService&&) = delete;

	private:
		virtual void Tick() noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds NowTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealFixedStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFixedStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFixedStepCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualDeltaTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaFixedStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaFixedStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaFixedStepCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTimeCap() const noexcept override;
		virtual void DeltaTimeCap(std::chrono::nanoseconds cap) noexcept override;

		[[nodiscard("Pure function")]]
		virtual double TimeScale() const noexcept override;
		virtual void TimeScale(double scale) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds FixedStepPeriod() const noexcept override;
		virtual void FixedStepPeriod(std::chrono::nanoseconds period) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds TargetFrameTime() const noexcept override;
		virtual void TargetFrameTime(std::chrono::nanoseconds frameTime) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> FrameTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> NowTimePoint() const noexcept override;

		/// @brief Waits for the next frame time point according to the @p deltaTimeCap.
		/// @return Now time point.
		[[nodiscard("Must used to update times")]]
		std::chrono::time_point<std::chrono::steady_clock> WaitForNextFrame() const noexcept;
		/// @brief Updates times and frame counts.
		/// @param now Now time point.
		void UpdateTimes(std::chrono::time_point<std::chrono::steady_clock> now) noexcept;

		Application::IApplicationContext* application;

		std::chrono::nanoseconds deltaTimeCap; ///< Delta time cap.
		double timeScale; ///< Time scale.
		std::chrono::nanoseconds fixedStepPeriod; ///< Fixed step period.
		std::chrono::nanoseconds targetFrameTime; ///< Target frame time.

		std::chrono::time_point<std::chrono::steady_clock> startTimePoint; ///< Start time point.
		std::chrono::time_point<std::chrono::steady_clock> prevFrameTimePoint; ///< Previous frame time point.
		std::chrono::time_point<std::chrono::steady_clock> thisFrameTimePoint; ///< This frame time point.

		std::chrono::nanoseconds realTime; ///< Real time elapsed since the start.
		std::chrono::nanoseconds unscaledVirtualTime; ///< Unscaled virtual time elapsed since the start.
		std::chrono::nanoseconds virtualTime; ///< Virtual time elapsed since the start.

		std::uint64_t realFixedStepCount; ///< Real fixed step count since the start.
		std::uint64_t unscaledVirtualFixedStepCount; ///< Unscaled virtual fixed step count since the start.
		std::uint64_t virtualFixedStepCount; ///< Virtual fixed step count since the start.

		std::chrono::nanoseconds realDeltaTime; ///< Real delta time.
		std::chrono::nanoseconds unscaledVirtualDeltaTime; ///< Unscaled virtual delta time.
		std::chrono::nanoseconds virtualDeltaTime; ///< Virtual delta time.

		std::uint64_t realDeltaFixedStepCount; ///< Real delta fixed step count.
		std::uint64_t unscaledVirtualDeltaFixedStepCount; ///< Unscaled virtual delta fixed step count.
		std::uint64_t virtualDeltaFixedStepCount; ///< Virtual delta fixed step count.

		std::chrono::nanoseconds realTimeAccumulator; ///< Real time accumulator.
		std::chrono::nanoseconds unscaledVirtualTimeAccumulator; ///< Unscaled virtual time accumulator.
		std::chrono::nanoseconds virtualTimeAccumulator; ///< Virtual time accumulator.
	};
}

namespace PonyEngine::Time
{
	TimeService::TimeService(Application::IApplicationContext& application) noexcept :
		application{&application},
		deltaTimeCap(std::max(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(PONY_ENGINE_TIME_DELTA_TIME_CAP)), std::chrono::nanoseconds(1))),
		timeScale{std::max(PONY_ENGINE_TIME_SCALE, 0.)},
		fixedStepPeriod(std::max(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(PONY_ENGINE_TIME_FIXED_STEP_PERIOD)), std::chrono::nanoseconds(1))),
		targetFrameTime(std::max(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(PONY_ENGINE_TIME_TARGET_FRAME_TIME)), std::chrono::nanoseconds(0))),
		startTimePoint(NowTimePoint()),
		prevFrameTimePoint(startTimePoint),
		thisFrameTimePoint(startTimePoint),
		realTime(0),
		unscaledVirtualTime(0),
		virtualTime(0),
		realFixedStepCount{0ull},
		unscaledVirtualFixedStepCount{0ull},
		virtualFixedStepCount{0ull},
		realDeltaTime(0),
		unscaledVirtualDeltaTime(0),
		virtualDeltaTime(0),
		realDeltaFixedStepCount{0ull},
		unscaledVirtualDeltaFixedStepCount{0ull},
		virtualDeltaFixedStepCount{0ull},
		realTimeAccumulator(0),
		unscaledVirtualTimeAccumulator(0),
		virtualTimeAccumulator(0)
	{
	}

	void TimeService::Begin() noexcept
	{
	}

	void TimeService::End() noexcept
	{
	}

	void TimeService::AddTickableServices(Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, PONY_ENGINE_TIME_TICK_ORDER);
	}

	void TimeService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<ITimeService>(*this);
	}

	void TimeService::Tick() noexcept
	{
		const std::chrono::time_point<std::chrono::steady_clock> now = WaitForNextFrame();
		UpdateTimes(now);
	}

	std::chrono::nanoseconds TimeService::NowTime() const noexcept
	{
		return std::chrono::nanoseconds(NowTimePoint() - startTimePoint);
	}

	std::chrono::nanoseconds TimeService::RealTime() const noexcept
	{
		return realTime;
	}

	std::chrono::nanoseconds TimeService::VirtualTime() const noexcept
	{
		return virtualTime;
	}

	std::chrono::nanoseconds TimeService::UnscaledVirtualTime() const noexcept
	{
		return unscaledVirtualTime;
	}

	std::uint64_t TimeService::RealFixedStepCount() const noexcept
	{
		return realFixedStepCount;
	}

	std::uint64_t TimeService::VirtualFixedStepCount() const noexcept
	{
		return virtualFixedStepCount;
	}

	std::uint64_t TimeService::UnscaledVirtualFixedStepCount() const noexcept
	{
		return unscaledVirtualFixedStepCount;
	}

	std::chrono::nanoseconds TimeService::RealDeltaTime() const noexcept
	{
		return realDeltaTime;
	}

	std::chrono::nanoseconds TimeService::VirtualDeltaTime() const noexcept
	{
		return virtualDeltaTime;
	}

	std::chrono::nanoseconds TimeService::UnscaledVirtualDeltaTime() const noexcept
	{
		return unscaledVirtualDeltaTime;
	}

	std::uint64_t TimeService::RealDeltaFixedStepCount() const noexcept
	{
		return realDeltaFixedStepCount;
	}

	std::uint64_t TimeService::VirtualDeltaFixedStepCount() const noexcept
	{
		return virtualDeltaFixedStepCount;
	}

	std::uint64_t TimeService::UnscaledVirtualDeltaFixedStepCount() const noexcept
	{
		return unscaledVirtualDeltaFixedStepCount;
	}

	std::chrono::nanoseconds TimeService::DeltaTimeCap() const noexcept
	{
		return deltaTimeCap;
	}

	void TimeService::DeltaTimeCap(const std::chrono::nanoseconds cap) noexcept
	{
		deltaTimeCap = std::max(cap, std::chrono::nanoseconds(1));
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Delta time cap changed to '{}'.", deltaTimeCap);
	}

	double TimeService::TimeScale() const noexcept
	{
		return timeScale;
	}

	void TimeService::TimeScale(const double scale) noexcept
	{
		timeScale = std::max(scale, 0.);
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Time scale changed to '{}'.", timeScale);
	}

	std::chrono::nanoseconds TimeService::FixedStepPeriod() const noexcept
	{
		return fixedStepPeriod;
	}

	void TimeService::FixedStepPeriod(const std::chrono::nanoseconds period) noexcept
	{
		fixedStepPeriod = std::max(period, std::chrono::nanoseconds(1));
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Frame period changed to '{}'.", fixedStepPeriod);
	}

	std::chrono::nanoseconds TimeService::TargetFrameTime() const noexcept
	{
		return targetFrameTime;
	}

	void TimeService::TargetFrameTime(const std::chrono::nanoseconds frameTime) noexcept
	{
		targetFrameTime = std::max(frameTime, std::chrono::nanoseconds(0));
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Target frame time changed to '{}'.", targetFrameTime);
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeService::StartTimePoint() const noexcept
	{
		return startTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeService::FrameTimePoint() const noexcept
	{
		return thisFrameTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeService::NowTimePoint() const noexcept
	{
		return std::chrono::steady_clock::now();
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeService::WaitForNextFrame() const noexcept
	{
		std::chrono::time_point<std::chrono::steady_clock> now;
		do
		{
			now = NowTimePoint();
		} while (now - thisFrameTimePoint < targetFrameTime);

		return now;
	}

	void TimeService::UpdateTimes(const std::chrono::time_point<std::chrono::steady_clock> now) noexcept
	{
		prevFrameTimePoint = thisFrameTimePoint;
		thisFrameTimePoint = now;

		realDeltaTime = thisFrameTimePoint - prevFrameTimePoint;
		unscaledVirtualDeltaTime = std::min(realDeltaTime, deltaTimeCap);
		virtualDeltaTime = std::chrono::round<std::chrono::nanoseconds>(unscaledVirtualDeltaTime * timeScale);

		realTime = thisFrameTimePoint - startTimePoint;
		unscaledVirtualTime += unscaledVirtualDeltaTime;
		virtualTime += virtualDeltaTime;

		realTimeAccumulator += realDeltaTime;
		unscaledVirtualTimeAccumulator += unscaledVirtualDeltaTime;
		virtualTimeAccumulator += virtualDeltaTime;

		realDeltaFixedStepCount = realTimeAccumulator / fixedStepPeriod;
		unscaledVirtualDeltaFixedStepCount = unscaledVirtualTimeAccumulator / fixedStepPeriod;
		virtualDeltaFixedStepCount = virtualTimeAccumulator / fixedStepPeriod;

		realTimeAccumulator %= fixedStepPeriod;
		unscaledVirtualTimeAccumulator %= fixedStepPeriod;
		virtualTimeAccumulator %= fixedStepPeriod;

		realFixedStepCount += realDeltaFixedStepCount;
		unscaledVirtualFixedStepCount += unscaledVirtualDeltaFixedStepCount;
		virtualFixedStepCount += virtualDeltaFixedStepCount;
	}
}
