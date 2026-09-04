/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.WinDebug.Impl:WinDebugLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :WinDebugLogger;

export namespace PonyEngine::Log::WinDebug
{
	/// @brief WinAPI debug logger module.
	class WinDebugLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		WinDebugLoggerModule() noexcept = default;
		WinDebugLoggerModule(const WinDebugLoggerModule&) = delete;
		WinDebugLoggerModule(WinDebugLoggerModule&&) = delete;

		~WinDebugLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		WinDebugLoggerModule& operator =(const WinDebugLoggerModule&) = delete;
		WinDebugLoggerModule& operator =(WinDebugLoggerModule&&) = delete;

	private:
		std::unique_ptr<WinDebugLogger> logger; ///< WinAPI debug logger.
	};
}

namespace PonyEngine::Log::WinDebug
{
	void WinDebugLoggerModule::StartUp(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logger = std::make_unique<WinDebugLogger>();

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

	void WinDebugLoggerModule::ShutDown(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logHub.RemoveLogger(*logger);
		logger.reset();
	}
}
