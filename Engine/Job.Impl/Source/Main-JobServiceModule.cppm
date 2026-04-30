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

import PonyEngine.Application.Ext;

import :JobService;

export namespace PonyEngine::Job
{
	class JobServiceModule final : public Application::IModule
	{
	public:
		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

	private:
		Application::ServiceHandle jobServiceHandle;
	};
}

namespace PonyEngine::Job
{
	void JobServiceModule::StartUp(Application::IModuleContext& context)
	{
		jobServiceHandle = context.ServiceModuleContext().AddService([](Application::IApplicationContext& application)
		{
			return std::make_shared<JobService>(application);
		});
	}

	void JobServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.ServiceModuleContext().RemoveService(jobServiceHandle);
	}
}
