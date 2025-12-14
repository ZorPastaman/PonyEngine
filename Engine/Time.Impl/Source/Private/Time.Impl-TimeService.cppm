/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Impl:TimeService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Time;

export namespace PonyEngine::Time
{
	/// @brief Time service.
	class TimeService final : public Application::ITickableService, private ITimeService
	{
	public:
		/// @brief Creates a time service.
		[[nodiscard("Pure constructor")]]
		TimeService() noexcept;
		TimeService(const TimeService&) = delete;
		TimeService(TimeService&&) = delete;

		~TimeService() noexcept = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;
		virtual void Tick() noexcept override;

		[[nodiscard("Pure function")]]
		virtual double NowTime() const noexcept override;

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
		virtual void DeltaTimeCap(float cap) override;

		[[nodiscard("Pure function")]]
		virtual float TimeScale() const noexcept override;
		virtual void TimeScale(float scale) override;

		[[nodiscard("Pure function")]]
		virtual float FramePeriod() const noexcept override;
		virtual void FramePeriod(float period) override;

		[[nodiscard("Pure function")]]
		virtual float TargetFrameTime() const noexcept override;
		virtual void TargetFrameTime(float frameTime) override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> FrameTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> NowTimePoint() const noexcept override;

		/// @brief Gets the public time service.
		/// @return Public time service.
		[[nodiscard("Pure function")]]
		ITimeService& PublicTimeService() noexcept;
		/// @brief Gets the public time service.
		/// @return Public time service.
		[[nodiscard("Pure function")]]
		const ITimeService& PublicTimeService() const noexcept;

		TimeService& operator =(const TimeService&) = delete;
		TimeService& operator =(TimeService&&) = delete;

	private:
		/// @brief Waits for the next frame time point according to the @p deltaTimeCap.
		/// @return Now time point.
		[[nodiscard("Must used to update times")]]
		std::chrono::time_point<std::chrono::steady_clock> WaitForNextFrame() noexcept;
		/// @brief Updates times and frame counts.
		/// @param now Now time point.
		void UpdateTimes(std::chrono::time_point<std::chrono::steady_clock> now) noexcept;

		float deltaTimeCap; ///< Delta time cap.
		float timeScale; ///< Time scale.
		float framePeriod; ///< Frame period.
		std::chrono::duration<float> targetFrameTime; ///< Target frame time.

		std::chrono::time_point<std::chrono::steady_clock> startTimePoint; ///< Start time point.
		std::chrono::time_point<std::chrono::steady_clock> prevFrameTimePoint; ///< Previous frame time point.
		std::chrono::time_point<std::chrono::steady_clock> thisFrameTimePoint; ///< This frame time point.

		double realTime; ///< Real time elapsed since the start in seconds.
		double unscaledVirtualTime; ///< Unscaled virtual time elapsed since the start in seconds.
		double virtualTime; ///< Virtual time elapsed since the start in seconds.

		std::uint64_t realFrameCount; ///< Real frame count since the start.
		std::uint64_t unscaledVirtualFrameCount; ///< Unscaled virtual frame count since the start.
		std::uint64_t virtualFrameCount; ///< Virtual frame count since the start.

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
	TimeService::TimeService() noexcept :
		deltaTimeCap{1.f},
		timeScale{1.f},
		framePeriod{1.f / 60.f},
		targetFrameTime(0.f),
		startTimePoint(NowTimePoint()),
		prevFrameTimePoint(startTimePoint),
		thisFrameTimePoint(startTimePoint),
		realTime{0.},
		unscaledVirtualTime{0.},
		virtualTime{0.},
		realFrameCount{0ull},
		unscaledVirtualFrameCount{0ull},
		virtualFrameCount{0ull},
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

	void TimeService::Begin() noexcept
	{
	}

	void TimeService::End() noexcept
	{
	}

	void TimeService::Tick() noexcept
	{
		const std::chrono::time_point<std::chrono::steady_clock> now = WaitForNextFrame();
		UpdateTimes(now);
	}

	double TimeService::NowTime() const noexcept
	{
		return std::chrono::duration<double>(NowTimePoint() - startTimePoint).count();
	}

	double TimeService::RealTime() const noexcept
	{
		return realTime;
	}

	double TimeService::VirtualTime() const noexcept
	{
		return virtualTime;
	}

	double TimeService::UnscaledVirtualTime() const noexcept
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

	float TimeService::RealDeltaTime() const noexcept
	{
		return realDeltaTime;
	}

	float TimeService::VirtualDeltaTime() const noexcept
	{
		return virtualDeltaTime;
	}

	float TimeService::UnscaledVirtualDeltaTime() const noexcept
	{
		return unscaledVirtualDeltaTime;
	}

	std::uint32_t TimeService::RealDeltaFrame() const noexcept
	{
		return realDeltaFrame;
	}

	std::uint32_t TimeService::VirtualDeltaFrame() const noexcept
	{
		return virtualDeltaFrame;
	}

	std::uint32_t TimeService::UnscaledVirtualDeltaFrame() const noexcept
	{
		return unscaledVirtualDeltaFrame;
	}

	float TimeService::DeltaTimeCap() const noexcept
	{
		return deltaTimeCap;
	}

	void TimeService::DeltaTimeCap(const float cap)
	{
		if (cap <= 0.f) [[unlikely]]
		{
			throw std::invalid_argument("Delta time cap must be greater than zero");
		}

		deltaTimeCap = cap;
	}

	float TimeService::TimeScale() const noexcept
	{
		return timeScale;
	}

	void TimeService::TimeScale(const float scale)
	{
		if (scale < 0.f) [[unlikely]]
		{
			throw std::invalid_argument("Time scale must be greater or equal zero");
		}

		timeScale = scale;
	}

	float TimeService::FramePeriod() const noexcept
	{
		return framePeriod;
	}

	void TimeService::FramePeriod(const float period)
	{
		if (period <= 0.f) [[unlikely]]
		{
			throw std::invalid_argument("Frame period must be greater than zero");
		}

		framePeriod = period;
	}

	float TimeService::TargetFrameTime() const noexcept
	{
		return targetFrameTime.count();
	}

	void TimeService::TargetFrameTime(const float frameTime)
	{
		if (frameTime < 0.f) [[unlikely]]
		{
			throw std::invalid_argument("Target frame time must be greater or equal zero");
		}

		targetFrameTime = std::chrono::duration<float>(frameTime);
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

	ITimeService& TimeService::PublicTimeService() noexcept
	{
		return *this;
	}

	const ITimeService& TimeService::PublicTimeService() const noexcept
	{
		return *this;
	}

	std::chrono::time_point<std::chrono::steady_clock> TimeService::WaitForNextFrame() noexcept
	{
		std::chrono::time_point<std::chrono::steady_clock> now;
		do
		{
			now = NowTimePoint();
		} while (std::chrono::duration<float>(now - thisFrameTimePoint) < targetFrameTime);

		return now;
	}

	void TimeService::UpdateTimes(const std::chrono::time_point<std::chrono::steady_clock> now) noexcept
	{
		prevFrameTimePoint = thisFrameTimePoint;
		thisFrameTimePoint = now;

		realDeltaTime = std::chrono::duration<float>(thisFrameTimePoint - prevFrameTimePoint).count();
		unscaledVirtualDeltaTime = std::min(realDeltaTime, deltaTimeCap);
		virtualDeltaTime = unscaledVirtualDeltaTime * timeScale;

		realTime = std::chrono::duration<double>(thisFrameTimePoint - startTimePoint).count();
		unscaledVirtualTime += unscaledVirtualDeltaTime;
		virtualTime += virtualDeltaTime;

		realTimeAccumulator += realDeltaTime;
		unscaledVirtualTimeAccumulator += unscaledVirtualDeltaTime;
		virtualTimeAccumulator += virtualDeltaTime;

		const float inverseFramePeriod = 1.f / framePeriod;
		realDeltaFrame = static_cast<std::uint32_t>(realTimeAccumulator * inverseFramePeriod);
		unscaledVirtualDeltaFrame = static_cast<std::uint32_t>(unscaledVirtualTimeAccumulator * inverseFramePeriod);
		virtualDeltaFrame = static_cast<std::uint32_t>(virtualTimeAccumulator * inverseFramePeriod);

		realTimeAccumulator -= static_cast<float>(realDeltaFrame) * framePeriod;
		unscaledVirtualTimeAccumulator -= static_cast<float>(unscaledVirtualDeltaFrame) * framePeriod;
		virtualTimeAccumulator -= static_cast<float>(virtualDeltaFrame) * framePeriod;

		realFrameCount += realDeltaFrame;
		unscaledVirtualFrameCount += unscaledVirtualDeltaFrame;
		virtualFrameCount += virtualDeltaFrame;
	}
}
