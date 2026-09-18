/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

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
		std::unique_ptr<JobService> jobService; ///< Job service.
	};
}

namespace PonyEngine::Job
{
	void JobServiceModule::StartUp(Application::IModuleContext& context)
	{
		jobService = std::make_unique<JobService>(context.Application());
		context.AddInterface<IJobService>(*jobService);
	}

	void JobServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IJobService>(*jobService);
		jobService.reset();
	}
}
