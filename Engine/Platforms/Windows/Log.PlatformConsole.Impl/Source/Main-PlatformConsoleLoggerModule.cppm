/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.PlatformConsole.Impl:PlatformConsoleLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :PlatformConsoleLogger;

export namespace PonyEngine::Log::PlatformConsole
{
	/// @brief Platform console logger module.
	class PlatformConsoleLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleLoggerModule() noexcept = default;
		PlatformConsoleLoggerModule(const PlatformConsoleLoggerModule&) = delete;
		PlatformConsoleLoggerModule(PlatformConsoleLoggerModule&&) = delete;

		~PlatformConsoleLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		PlatformConsoleLoggerModule& operator =(const PlatformConsoleLoggerModule&) = delete;
		PlatformConsoleLoggerModule& operator =(PlatformConsoleLoggerModule&&) = delete;

	private:
		std::unique_ptr<PlatformConsoleLogger> logger; ///< Platform console logger.
	};
}

namespace PonyEngine::Log::PlatformConsole
{
	void PlatformConsoleLoggerModule::StartUp(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logger = std::make_unique<PlatformConsoleLogger>();

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

	void PlatformConsoleLoggerModule::ShutDown(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logHub.RemoveLogger(*logger);
		logger.reset();
	}
}
