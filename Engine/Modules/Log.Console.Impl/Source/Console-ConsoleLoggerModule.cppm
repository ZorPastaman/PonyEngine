/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Console.Impl:ConsoleLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :ConsoleLogger;

export namespace PonyEngine::Log::Console
{
	/// @brief Console logger module.
	class ConsoleLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleLoggerModule() noexcept = default;
		ConsoleLoggerModule(const ConsoleLoggerModule&) = delete;
		ConsoleLoggerModule(ConsoleLoggerModule&&) = delete;

		~ConsoleLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		ConsoleLoggerModule& operator =(const ConsoleLoggerModule&) = delete;
		ConsoleLoggerModule& operator =(ConsoleLoggerModule&&) = delete;

	private:
		std::unique_ptr<ConsoleLogger> logger; ///< Console logger.
	};
}

namespace PonyEngine::Log::Console
{
	void ConsoleLoggerModule::StartUp(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logger = std::make_unique<ConsoleLogger>();

		try
		{
			logHub.AddLogger(*logger);
		}
		catch (...)
		{
			logger.reset();
			throw;
		}
	}

	void ConsoleLoggerModule::ShutDown(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logHub.RemoveLogger(*logger);
		logger.reset();
	}
}
