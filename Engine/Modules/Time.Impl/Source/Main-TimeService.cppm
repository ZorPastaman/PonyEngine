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
		virtual std::chrono::nanoseconds RealTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualTime() const override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealFixedStepCount() const override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFixedStepCount() const override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFixedStepCount() const override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealDeltaTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualDeltaTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualDeltaTime() const override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaFixedStepCount() const override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaFixedStepCount() const override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaFixedStepCount() const override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTimeCap() const override;
		virtual void DeltaTimeCap(std::chrono::nanoseconds cap) override;

		[[nodiscard("Pure function")]]
		virtual double TimeScale() const override;
		virtual void TimeScale(double scale) override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds FixedStepPeriod() const override;
		virtual void FixedStepPeriod(std::chrono::nanoseconds period) override;

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
		std::chrono::nanoseconds fixedStepPeriod; ///< Fixed step period.

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
	TimeService::TimeService(const Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		deltaTimeCap(std::max(Chrono::ToDuration<std::chrono::nanoseconds>(double{PONY_ENGINE_TIME_DELTA_TIME_CAP}), std::chrono::nanoseconds(1))),
		timeScale{std::max(PONY_ENGINE_TIME_SCALE, 0.)},
		fixedStepPeriod(std::max(Chrono::ToDuration<std::chrono::nanoseconds>(double{PONY_ENGINE_TIME_FIXED_STEP_PERIOD}), std::chrono::nanoseconds(1))),
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

	std::chrono::nanoseconds TimeService::RealTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return realTime;
	}

	std::chrono::nanoseconds TimeService::VirtualTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return virtualTime;
	}

	std::chrono::nanoseconds TimeService::UnscaledVirtualTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return unscaledVirtualTime;
	}

	std::uint64_t TimeService::RealFixedStepCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return realFixedStepCount;
	}

	std::uint64_t TimeService::VirtualFixedStepCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return virtualFixedStepCount;
	}

	std::uint64_t TimeService::UnscaledVirtualFixedStepCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return unscaledVirtualFixedStepCount;
	}

	std::chrono::nanoseconds TimeService::RealDeltaTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return realDeltaTime;
	}

	std::chrono::nanoseconds TimeService::VirtualDeltaTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return virtualDeltaTime;
	}

	std::chrono::nanoseconds TimeService::UnscaledVirtualDeltaTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return unscaledVirtualDeltaTime;
	}

	std::uint64_t TimeService::RealDeltaFixedStepCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return realDeltaFixedStepCount;
	}

	std::uint64_t TimeService::VirtualDeltaFixedStepCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return virtualDeltaFixedStepCount;
	}

	std::uint64_t TimeService::UnscaledVirtualDeltaFixedStepCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return unscaledVirtualDeltaFixedStepCount;
	}

	std::chrono::nanoseconds TimeService::DeltaTimeCap() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return deltaTimeCap;
	}

	void TimeService::DeltaTimeCap(const std::chrono::nanoseconds cap)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		deltaTimeCap = std::max(cap, std::chrono::nanoseconds(1));
		PONY_LOG(logService, Log::LogType::Debug, "Delta time cap changed to '{}'.", deltaTimeCap);
	}

	double TimeService::TimeScale() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return timeScale;
	}

	void TimeService::TimeScale(const double scale)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		timeScale = std::max(scale, 0.);
		PONY_LOG(logService, Log::LogType::Debug, "Time scale changed to '{}'.", timeScale);
	}

	std::chrono::nanoseconds TimeService::FixedStepPeriod() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return fixedStepPeriod;
	}

	void TimeService::FixedStepPeriod(const std::chrono::nanoseconds period)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		fixedStepPeriod = std::max(period, std::chrono::nanoseconds(1));
		PONY_LOG(logService, Log::LogType::Debug, "Frame period changed to '{}'.", fixedStepPeriod);
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
