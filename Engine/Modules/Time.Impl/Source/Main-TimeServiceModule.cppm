/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Impl:TimeServiceModule;

import PonyEngine.Application;
import PonyEngine.Time;

import :TimeService;

export namespace PonyEngine::Time
{
	/// @brief Time service module.
	class TimeServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		TimeServiceModule() noexcept = default;
		TimeServiceModule(const TimeServiceModule&) = delete;
		TimeServiceModule(TimeServiceModule&&) = delete;

		~TimeServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		TimeServiceModule& operator =(const TimeServiceModule&) = delete;
		TimeServiceModule& operator =(TimeServiceModule&&) = delete;

	private:
		std::unique_ptr<TimeService> timeService; ///< Time service.
	};
}

namespace PonyEngine::Time
{
	void TimeServiceModule::StartUp(Application::IModuleContext& context)
	{
		timeService = std::make_unique<TimeService>(context.Application());

		try
		{
			context.AddInterface<ITimeService>(*timeService);
			try
			{
				context.AddTickable(timeService->Tickable(), Application::TickableOrder{.tickOrder = PONY_ENGINE_TIME_TICK_ORDER});
			}
			catch (...)
			{
				context.RemoveInterface<ITimeService>(*timeService);
				throw;
			}
		}
		catch (...)
		{
			timeService.reset();
			throw;
		}
	}

	void TimeServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveTickable(timeService->Tickable(), Application::TickableOrder{.tickOrder = PONY_ENGINE_TIME_TICK_ORDER});
		context.RemoveInterface<ITimeService>(*timeService);
		timeService.reset();
	}
}
