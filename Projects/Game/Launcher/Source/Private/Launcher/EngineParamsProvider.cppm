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
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Input.Factories;
import PonyEngine.Input.Implementation;

using LogType = PonyEngine::Debug::Log::LogType;

export namespace Launcher
{
	/// @brief Platform-independent engine params provider.
	class EngineParamsProvider final
	{
	public:
		/// @brief Creates an @p EngineParamsProvider.
		/// @param logger Logger.
		[[nodiscard("Pure constructor")]]
		explicit EngineParamsProvider(PonyEngine::Debug::Log::ILogger& logger);
		EngineParamsProvider(const EngineParamsProvider&) = delete;
		EngineParamsProvider(EngineParamsProvider&&) = delete;

		~EngineParamsProvider() noexcept;

		/// @brief Modifies engine params.
		/// @param engineParams Engine params to modify.
		void Modify(PonyEngine::Core::EngineParams& engineParams) const;

		EngineParamsProvider& operator =(const EngineParamsProvider&) = delete;
		EngineParamsProvider& operator =(EngineParamsProvider&&) = delete;

	private:
		PonyEngine::Debug::Log::ILogger& m_logger; ///< Logger.

		// Set all platform-independent factories here.

		PonyEngine::Input::IInputSystemFactory* m_inputSystemFactory;
	};
}

namespace Launcher
{
	EngineParamsProvider::EngineParamsProvider(PonyEngine::Debug::Log::ILogger& logger) :
		m_logger{logger}
	{
		// Create all platform-independent factories here.

		PONY_LOG_GENERAL(m_logger, LogType::Info, "Create an input system factory.");
		m_inputSystemFactory = PonyEngine::Input::CreateInputSystemFactory();
		assert((m_inputSystemFactory != nullptr));
		PONY_LOG_GENERAL(m_logger, LogType::Info, "Input system factory created.");
	}

	EngineParamsProvider::~EngineParamsProvider() noexcept
	{
		// Destroy all platform-independent factories here.

		PONY_LOG_GENERAL(m_logger, LogType::Info, "Destroy an input system factory.");
		PonyEngine::Input::DestroyInputSystemFactory(m_inputSystemFactory);
		PONY_LOG_GENERAL(m_logger, LogType::Info, "Input system factory destroyed.");
	}

	void EngineParamsProvider::Modify(PonyEngine::Core::EngineParams& engineParams) const
	{
		// Set all platform-independent factories and other parameters here.

		PONY_LOG_GENERAL(m_logger, LogType::Debug, "Push an input system factory.");
		engineParams.AddSystemFactory(m_inputSystemFactory);
	}
}
