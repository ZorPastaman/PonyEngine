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
import PonyEngine.Math;
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
		virtual std::uint64_t RealFrameCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFrameCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualDeltaTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaFrame() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaFrame() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaFrame() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTimeCap() const noexcept override;
		virtual void DeltaTimeCap(std::chrono::nanoseconds cap) override;

		[[nodiscard("Pure function")]]
		virtual double TimeScale() const noexcept override;
		virtual void TimeScale(double scale) override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds FramePeriod() const noexcept override;
		virtual void FramePeriod(std::chrono::nanoseconds period) override;

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
		std::chrono::nanoseconds framePeriod; ///< Frame period.
		std::chrono::nanoseconds targetFrameTime; ///< Target frame time.

		std::chrono::time_point<std::chrono::steady_clock> startTimePoint; ///< Start time point.
		std::chrono::time_point<std::chrono::steady_clock> prevFrameTimePoint; ///< Previous frame time point.
		std::chrono::time_point<std::chrono::steady_clock> thisFrameTimePoint; ///< This frame time point.

		std::chrono::nanoseconds realTime; ///< Real time elapsed since the start.
		std::chrono::nanoseconds unscaledVirtualTime; ///< Unscaled virtual time elapsed since the start.
		std::chrono::nanoseconds virtualTime; ///< Virtual time elapsed since the start.

		std::uint64_t realFrameCount; ///< Real frame count since the start.
		std::uint64_t unscaledVirtualFrameCount; ///< Unscaled virtual frame count since the start.
		std::uint64_t virtualFrameCount; ///< Virtual frame count since the start.

		std::chrono::nanoseconds realDeltaTime; ///< Real delta time.
		std::chrono::nanoseconds unscaledVirtualDeltaTime; ///< Unscaled virtual delta time.
		std::chrono::nanoseconds virtualDeltaTime; ///< Virtual delta time.

		std::uint64_t realDeltaFrame; ///< Real delta frame.
		std::uint64_t unscaledVirtualDeltaFrame; ///< Unscaled virtual delta frame.
		std::uint64_t virtualDeltaFrame; ///< Virtual delta frame.

		std::chrono::nanoseconds realTimeAccumulator; ///< Real time accumulator.
		std::chrono::nanoseconds unscaledVirtualTimeAccumulator; ///< Unscaled virtual time accumulator.
		std::chrono::nanoseconds virtualTimeAccumulator; ///< Virtual time accumulator.
	};
}

namespace PonyEngine::Time
{
	TimeService::TimeService(Application::IApplicationContext& application) noexcept :
		application{&application},
		deltaTimeCap(std::chrono::seconds(1)),
		timeScale{1.},
		framePeriod(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1. / 60.))),
		targetFrameTime(0ull),
		startTimePoint(NowTimePoint()),
		prevFrameTimePoint(startTimePoint),
		thisFrameTimePoint(startTimePoint),
		realTime(0),
		unscaledVirtualTime(0),
		virtualTime(0),
		realFrameCount{0ull},
		unscaledVirtualFrameCount{0ull},
		virtualFrameCount{0ull},
		realDeltaTime(0),
		unscaledVirtualDeltaTime(0),
		virtualDeltaTime(0),
		realDeltaFrame{0ull},
		unscaledVirtualDeltaFrame{0ull},
		virtualDeltaFrame{0ull},
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

	std::uint64_t TimeService::RealFrameCount() const noexcept
	{
		return realFrameCount;
	}

	std::uint64_t TimeService::VirtualFrameCount() const noexcept
	{
		return virtualFrameCount;
	}

	std::uint64_t TimeService::UnscaledVirtualFrameCount() const noexcept
	{
		return unscaledVirtualFrameCount;
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

	std::uint64_t TimeService::RealDeltaFrame() const noexcept
	{
		return realDeltaFrame;
	}

	std::uint64_t TimeService::VirtualDeltaFrame() const noexcept
	{
		return virtualDeltaFrame;
	}

	std::uint64_t TimeService::UnscaledVirtualDeltaFrame() const noexcept
	{
		return unscaledVirtualDeltaFrame;
	}

	std::chrono::nanoseconds TimeService::DeltaTimeCap() const noexcept
	{
		return deltaTimeCap;
	}

	void TimeService::DeltaTimeCap(const std::chrono::nanoseconds cap)
	{
		if (cap <= std::chrono::nanoseconds(0)) [[unlikely]]
		{
			throw std::invalid_argument("Delta time cap must be greater than zero");
		}

		deltaTimeCap = cap;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Delta time cap changed to '{}'.", deltaTimeCap);
	}

	double TimeService::TimeScale() const noexcept
	{
		return timeScale;
	}

	void TimeService::TimeScale(const double scale)
	{
		if (scale < 0.) [[unlikely]]
		{
			throw std::invalid_argument("Time scale must be greater or equal zero");
		}

		timeScale = scale;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Time scale changed to '{}'.", timeScale);
	}

	std::chrono::nanoseconds TimeService::FramePeriod() const noexcept
	{
		return framePeriod;
	}

	void TimeService::FramePeriod(const std::chrono::nanoseconds period)
	{
		if (period <= std::chrono::nanoseconds(0)) [[unlikely]]
		{
			throw std::invalid_argument("Frame period must be greater than zero");
		}

		framePeriod = period;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Frame period changed to '{}'.", framePeriod);
	}

	std::chrono::nanoseconds TimeService::TargetFrameTime() const noexcept
	{
		return targetFrameTime;
	}

	void TimeService::TargetFrameTime(const std::chrono::nanoseconds frameTime) noexcept
	{
		targetFrameTime = frameTime;
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
		virtualDeltaTime = std::chrono::nanoseconds(Math::RoundToIntegral<std::chrono::nanoseconds::rep>((unscaledVirtualDeltaTime * timeScale).count()));

		realTime = thisFrameTimePoint - startTimePoint;
		unscaledVirtualTime += unscaledVirtualDeltaTime;
		virtualTime += virtualDeltaTime;

		realTimeAccumulator += realDeltaTime;
		unscaledVirtualTimeAccumulator += unscaledVirtualDeltaTime;
		virtualTimeAccumulator += virtualDeltaTime;

		realDeltaFrame = realTimeAccumulator / framePeriod;
		unscaledVirtualDeltaFrame = unscaledVirtualTimeAccumulator / framePeriod;
		virtualDeltaFrame = virtualTimeAccumulator / framePeriod;

		realTimeAccumulator %= framePeriod;
		unscaledVirtualTimeAccumulator %= framePeriod;
		virtualTimeAccumulator %= framePeriod;

		realFrameCount += realDeltaFrame;
		unscaledVirtualFrameCount += unscaledVirtualDeltaFrame;
		virtualFrameCount += virtualDeltaFrame;
	}
}
