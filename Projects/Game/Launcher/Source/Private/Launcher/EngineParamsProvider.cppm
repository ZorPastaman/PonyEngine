/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:EngineParamsProvider;

import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log.Factories;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Input.Factories;
import PonyEngine.Input.Implementation;

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
		m_consoleSubLoggerFactory = PonyEngine::Debug::Log::CreateConsoleSubLoggerFactory();
		m_fileSubLoggerFactory = PonyEngine::Debug::Log::CreateFileSubLoggerFactory();
		m_inputSystemFactory = PonyEngine::Input::CreateInputSystemFactory();
	}

	EngineParamsProvider::~EngineParamsProvider() noexcept
	{
		// Destroy all platform-independent factories here.
		PonyEngine::Input::DestroyInputSystemFactory(m_inputSystemFactory);

		PonyEngine::Debug::Log::DestroyFileSubLoggerFactory(m_fileSubLoggerFactory);
		PonyEngine::Debug::Log::DestroyConsoleSubLoggerFactory(m_consoleSubLoggerFactory);
	}

	void EngineParamsProvider::Modify(PonyEngine::Core::EngineParams& engineParams) const
	{
		// Set all platform-independent factories and other parameters here.
		engineParams.subLoggerFactories.push_back(m_consoleSubLoggerFactory);
		engineParams.subLoggerFactories.push_back(m_fileSubLoggerFactory);
		engineParams.systemFactories.push_back(m_inputSystemFactory);
	}
}
