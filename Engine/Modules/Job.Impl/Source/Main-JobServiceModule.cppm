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

export module PonyEngine.Job.Impl:JobServiceModule;

import std;

import PonyEngine.Application;

import :JobService;

export namespace PonyEngine::Job
{
	/// @brief Job service module.
	class JobServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		JobServiceModule() noexcept = default;
		JobServiceModule(const JobServiceModule&) = delete;
		JobServiceModule(JobServiceModule&&) = delete;

		~JobServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		JobServiceModule& operator =(const JobServiceModule&) = delete;
		JobServiceModule& operator =(JobServiceModule&&) = delete;

	private:
		Application::ServiceHandle jobServiceHandle; ///< Job service handle.
	};
}

namespace PonyEngine::Job
{
	void JobServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(JobService).name());
		jobServiceHandle = context.ServiceModuleContext().AddService([](Application::IApplication& application)
		{
			return std::make_shared<JobService>(application);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(JobService).name());
	}

	void JobServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(JobService).name());
		context.ServiceModuleContext().RemoveService(jobServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(JobService).name());
	}
}
