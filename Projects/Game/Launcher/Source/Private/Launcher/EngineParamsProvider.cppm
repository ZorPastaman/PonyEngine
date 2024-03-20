/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "Debug/Log/LogMacro.h"

export module Launcher:EngineParamsProvider;

import <iostream>;

import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Factories;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Input.Factories;
import PonyEngine.Input.Implementation;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Launcher
{
	/// @brief Platform-independent engine params provider.
	export class EngineParamsProvider final
	{
	public:
		/// @brief Creates an @p EngineParamsProvider.
		[[nodiscard("Pure constructor")]]
		EngineParamsProvider();
		EngineParamsProvider(const EngineParamsProvider&) = delete;
		EngineParamsProvider(EngineParamsProvider&&) = delete;

		~EngineParamsProvider() noexcept;

		/// @brief Modifies engine params.
		/// @param engineParams Engine params to modify.
		void Modify(PonyEngine::Core::EngineParams& engineParams) const;

		EngineParamsProvider& operator =(const EngineParamsProvider&) = delete;
		EngineParamsProvider& operator =(EngineParamsProvider&&) = delete;

	private:
		// Set all platform-independent factories here.
		PonyEngine::Debug::Log::ISubLoggerFactory* m_consoleSubLoggerFactory;
		PonyEngine::Debug::Log::ISubLoggerFactory* m_fileSubLoggerFactory;

		PonyEngine::Input::IInputSystemFactory* m_inputSystemFactory;
	};

	EngineParamsProvider::EngineParamsProvider()
	{
		// Create all platform-independent factories here.
		PONY_CONSOLE(LogType::Info, "Create a console sub-logger factory.");
		m_consoleSubLoggerFactory = PonyEngine::Debug::Log::CreateConsoleSubLoggerFactory();
		assert((m_consoleSubLoggerFactory != nullptr));
		PONY_CONSOLE(LogType::Info, "Console sub-logger factory created.");
		PONY_CONSOLE(LogType::Info, "Create a file sub-logger factory.");
		m_fileSubLoggerFactory = PonyEngine::Debug::Log::CreateFileSubLoggerFactory();
		assert((m_fileSubLoggerFactory != nullptr));
		PONY_CONSOLE(LogType::Info, "File sub-logger factory created.");

		PONY_CONSOLE(LogType::Info, "Create an input system factory.");
		m_inputSystemFactory = PonyEngine::Input::CreateInputSystemFactory();
		assert((m_inputSystemFactory != nullptr));
		PONY_CONSOLE(LogType::Info, "Input system factory created.");
	}

	EngineParamsProvider::~EngineParamsProvider() noexcept
	{
		// Destroy all platform-independent factories here.
		PONY_CONSOLE(LogType::Info, "Destroy an input system factory.");
		PonyEngine::Input::DestroyInputSystemFactory(m_inputSystemFactory);
		PONY_CONSOLE(LogType::Info, "Input system factory destroyed.");

		PONY_CONSOLE(LogType::Info, "Destroy a file sub-logger factory.");
		PonyEngine::Debug::Log::DestroyFileSubLoggerFactory(m_fileSubLoggerFactory);
		PONY_CONSOLE(LogType::Info, "File sub-logger factory destroyed.");
		PONY_CONSOLE(LogType::Info, "Destroy a console sub-logger factory.");
		PonyEngine::Debug::Log::DestroyConsoleSubLoggerFactory(m_consoleSubLoggerFactory);
		PONY_CONSOLE(LogType::Info, "Console sub-logger factory destroyed.");
	}

	void EngineParamsProvider::Modify(PonyEngine::Core::EngineParams& engineParams) const
	{
		// Set all platform-independent factories and other parameters here.
		PONY_CONSOLE(LogType::Debug, "Push a console sub-logger factory.");
		engineParams.subLoggerFactories.push_back(m_consoleSubLoggerFactory);
		PONY_CONSOLE(LogType::Debug, "Push a file sub-logger factory.");
		engineParams.subLoggerFactories.push_back(m_fileSubLoggerFactory);
		PONY_CONSOLE(LogType::Debug, "Push an input system factory.");
		engineParams.systemFactories.push_back(m_inputSystemFactory);
	}
}
