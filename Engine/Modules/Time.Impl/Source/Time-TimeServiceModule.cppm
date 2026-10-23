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
import PonyEngine.Utility;

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
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		timeService = std::make_unique<TimeService>(context.Application());
		const auto timeScopeGuard = Utility::ScopeGuard([&]() noexcept { timeService.reset(); }, scopeGuardFlag);
		context.AddInterface<ITimeService>(*timeService);
		const auto timeServiceScopeGuard = Utility::ScopeGuard([&]() noexcept { context.RemoveInterface<ITimeService>(*timeService); }, scopeGuardFlag);
		context.AddTickable(timeService->Tickable(), Application::TickableOrder{.tickOrder = PONY_ENGINE_TIME_TICK_ORDER});

		scopeGuardFlag.Release();
	}

	void TimeServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveTickable(timeService->Tickable(), Application::TickableOrder{.tickOrder = PONY_ENGINE_TIME_TICK_ORDER});
		context.RemoveInterface<ITimeService>(*timeService);
		timeService.reset();
	}
}
