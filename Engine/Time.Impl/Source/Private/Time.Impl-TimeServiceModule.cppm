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

export module PonyEngine.Time.Impl:TimeServiceModule;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

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
		Application::ServiceHandle timeServiceHandle; ///< Time service handle.
	};
}

namespace PonyEngine::Time
{
	void TimeServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(TimeService).name());
		timeServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
		{
			return std::make_shared<TimeService>(application);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(TimeService).name());
	}

	void TimeServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(TimeService).name());
		context.ServiceModuleContext().RemoveService(timeServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(TimeService).name());
	}
}
