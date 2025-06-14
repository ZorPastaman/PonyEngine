/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.PlatformConsole.WinCore:PlatformConsoleSubLoggerFactory;

import std;

import PonyEngine.Log.Extension;

import :PlatformConsoleSubLogger;

export namespace PonyEngine::Log::PlatformConsole::WinCore
{
	/// @brief WinCore platform console sub-logger factory.
	class PlatformConsoleSubLoggerFactory final : public Extension::ISubLoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLoggerFactory() noexcept = default;
		PlatformConsoleSubLoggerFactory(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory(PlatformConsoleSubLoggerFactory&&) = delete;

		~PlatformConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Extension::ISubLogger> CreateSubLogger(const Core::IModuleContext& context) override;

		PlatformConsoleSubLoggerFactory& operator =(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory& operator =(PlatformConsoleSubLoggerFactory&&) = delete;
	};
}

namespace PonyEngine::Log::PlatformConsole::WinCore
{
	std::shared_ptr<Extension::ISubLogger> PlatformConsoleSubLoggerFactory::CreateSubLogger(const Core::IModuleContext& context)
	{
		return std::make_shared<PlatformConsoleSubLogger>();
	}
}
