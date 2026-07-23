/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Impl:LogServiceModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :LogService;

export namespace PonyEngine::Log
{
	/// @brief Logger module.
	class LogServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		LogServiceModule() noexcept = default;
		LogServiceModule(const LogServiceModule&) = delete;
		LogServiceModule(LogServiceModule&&) = delete;

		~LogServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		LogServiceModule& operator =(const LogServiceModule&) = delete;
		LogServiceModule& operator =(LogServiceModule&&) = delete;

	private:
		std::unique_ptr<LogService> logService; ///< Log service.
	};
}

namespace PonyEngine::Log
{
	void LogServiceModule::StartUp(Application::IModuleContext& context)
	{
		logService = std::make_unique<LogService>();

		try
		{
			context.AddInterface<ILogService>(*logService);
			try
			{
				context.AddInterface<ILogHub>(*logService);
			}
			catch (...)
			{
				context.RemoveInterface<ILogService>(*logService);
				throw;
			}
		}
		catch (...)
		{
			logService.reset();
			throw;
		}
	}

	void LogServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<ILogHub>(*logService);
		context.RemoveInterface<ILogService>(*logService);
		logService.reset();
	}
}
