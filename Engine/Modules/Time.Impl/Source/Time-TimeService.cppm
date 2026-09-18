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

export module PonyEngine.Time.Impl:TimeService;

import std;

import PonyEngine.Application;
import PonyEngine.Chrono;
import PonyEngine.Log;
import PonyEngine.Time;

export namespace PonyEngine::Time
{
	/// @brief Time service.
	class TimeService final : public ITimeService, private Application::ITickable
	{
	public:
		/// @brief Creates a time service.
		[[nodiscard("Pure constructor")]]
		explicit TimeService(const Application::IApplication& application) noexcept;
		TimeService(const TimeService&) = delete;
		TimeService(TimeService&&) = delete;

		~TimeService() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualStepCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualDeltaTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualDeltaTime() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaStepCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaStepCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTimeCap() const noexcept override;
		virtual void DeltaTimeCap(std::chrono::nanoseconds cap) noexcept override;

		[[nodiscard("Pure function")]]
		virtual double TimeScale() const noexcept override;
		virtual void TimeScale(double scale) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds StepPeriod() const noexcept override;
		virtual void StepPeriod(std::chrono::nanoseconds period) noexcept override;

		/// @brief Gets the tickable.
		/// @return Tickable.
		[[nodiscard("Pure function")]]
		Application::ITickable& Tickable() noexcept;

		TimeService& operator =(const TimeService&) = delete;
		TimeService& operator =(TimeService&&) = delete;

	private:
		virtual void Tick() noexcept override;

		const Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.

		std::chrono::nanoseconds deltaTimeCap; ///< Delta time cap.
		double timeScale; ///< Time scale.
		std::chrono::nanoseconds stepPeriod; ///<  step period.

		std::chrono::nanoseconds realTime; ///< Real time elapsed since the start.
		std::chrono::nanoseconds unscaledVirtualTime; ///< Unscaled virtual time elapsed since the start.
		std::chrono::nanoseconds virtualTime; ///< Virtual time elapsed since the start.

		std::uint64_t realStepCount; ///< Real  step count since the start.
		std::uint64_t unscaledVirtualStepCount; ///< Unscaled virtual  step count since the start.
		std::uint64_t virtualStepCount; ///< Virtual  step count since the start.

		std::chrono::nanoseconds realDeltaTime; ///< Real delta time.
		std::chrono::nanoseconds unscaledVirtualDeltaTime; ///< Unscaled virtual delta time.
		std::chrono::nanoseconds virtualDeltaTime; ///< Virtual delta time.

		std::uint64_t realDeltaStepCount; ///< Real delta  step count.
		std::uint64_t unscaledVirtualDeltaStepCount; ///< Unscaled virtual delta  step count.
		std::uint64_t virtualDeltaStepCount; ///< Virtual delta  step count.

		std::chrono::nanoseconds realTimeAccumulator; ///< Real time accumulator.
		std::chrono::nanoseconds unscaledVirtualTimeAccumulator; ///< Unscaled virtual time accumulator.
		std::chrono::nanoseconds virtualTimeAccumulator; ///< Virtual time accumulator.
	};
}

namespace PonyEngine::Time
{
	TimeService::TimeService(const Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		deltaTimeCap(std::max(Chrono::ToDuration<std::chrono::nanoseconds>(double{PONY_ENGINE_TIME_DELTA_TIME_CAP}), std::chrono::nanoseconds(1))),
		timeScale{std::max(PONY_ENGINE_TIME_SCALE, 0.)},
		stepPeriod(std::max(Chrono::ToDuration<std::chrono::nanoseconds>(double{PONY_ENGINE_TIME_STEP_PERIOD}), std::chrono::nanoseconds(1))),
		realTime(0),
		unscaledVirtualTime(0),
		virtualTime(0),
		realStepCount{0ull},
		unscaledVirtualStepCount{0ull},
		virtualStepCount{0ull},
		realDeltaTime(0),
		unscaledVirtualDeltaTime(0),
		virtualDeltaTime(0),
		realDeltaStepCount{0ull},
		unscaledVirtualDeltaStepCount{0ull},
		virtualDeltaStepCount{0ull},
		realTimeAccumulator(0),
		unscaledVirtualTimeAccumulator(0),
		virtualTimeAccumulator(0)
	{
	}

	std::chrono::nanoseconds TimeService::RealTime() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return realTime;
	}

	std::chrono::nanoseconds TimeService::VirtualTime() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return virtualTime;
	}

	std::chrono::nanoseconds TimeService::UnscaledVirtualTime() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return unscaledVirtualTime;
	}

	std::uint64_t TimeService::RealStepCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return realStepCount;
	}

	std::uint64_t TimeService::VirtualStepCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return virtualStepCount;
	}

	std::uint64_t TimeService::UnscaledVirtualStepCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return unscaledVirtualStepCount;
	}

	std::chrono::nanoseconds TimeService::RealDeltaTime() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return realDeltaTime;
	}

	std::chrono::nanoseconds TimeService::VirtualDeltaTime() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return virtualDeltaTime;
	}

	std::chrono::nanoseconds TimeService::UnscaledVirtualDeltaTime() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return unscaledVirtualDeltaTime;
	}

	std::uint64_t TimeService::RealDeltaStepCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return realDeltaStepCount;
	}

	std::uint64_t TimeService::VirtualDeltaStepCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return virtualDeltaStepCount;
	}

	std::uint64_t TimeService::UnscaledVirtualDeltaStepCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return unscaledVirtualDeltaStepCount;
	}

	std::chrono::nanoseconds TimeService::DeltaTimeCap() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return deltaTimeCap;
	}

	void TimeService::DeltaTimeCap(const std::chrono::nanoseconds cap) noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		deltaTimeCap = std::max(cap, std::chrono::nanoseconds(1));
		PONY_LOG(logService, Log::LogType::Debug, "Delta time cap changed to '{}'.", deltaTimeCap);
	}

	double TimeService::TimeScale() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return timeScale;
	}

	void TimeService::TimeScale(const double scale) noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		timeScale = std::max(scale, 0.);
		PONY_LOG(logService, Log::LogType::Debug, "Time scale changed to '{}'.", timeScale);
	}

	std::chrono::nanoseconds TimeService::StepPeriod() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return stepPeriod;
	}

	void TimeService::StepPeriod(const std::chrono::nanoseconds period) noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		stepPeriod = std::max(period, std::chrono::nanoseconds(1));
		PONY_LOG(logService, Log::LogType::Debug, "Frame period changed to '{}'.", stepPeriod);
	}

	Application::ITickable& TimeService::Tickable() noexcept
	{
		return *this;
	}

	void TimeService::Tick() noexcept
	{
		realDeltaTime = application->DeltaTime();
		unscaledVirtualDeltaTime = std::min(realDeltaTime, deltaTimeCap);
		virtualDeltaTime = std::chrono::round<std::chrono::nanoseconds>(unscaledVirtualDeltaTime * timeScale);

		realTime = application->ThisFrameTime();
		unscaledVirtualTime += unscaledVirtualDeltaTime;
		virtualTime += virtualDeltaTime;

		realTimeAccumulator += realDeltaTime;
		unscaledVirtualTimeAccumulator += unscaledVirtualDeltaTime;
		virtualTimeAccumulator += virtualDeltaTime;

		realDeltaStepCount = realTimeAccumulator / stepPeriod;
		unscaledVirtualDeltaStepCount = unscaledVirtualTimeAccumulator / stepPeriod;
		virtualDeltaStepCount = virtualTimeAccumulator / stepPeriod;

		realTimeAccumulator %= stepPeriod;
		unscaledVirtualTimeAccumulator %= stepPeriod;
		virtualTimeAccumulator %= stepPeriod;

		realStepCount += realDeltaStepCount;
		unscaledVirtualStepCount += unscaledVirtualDeltaStepCount;
		virtualStepCount += virtualDeltaStepCount;
	}
}
