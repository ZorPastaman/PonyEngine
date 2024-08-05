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
#include "PonyEngine/Platform/Windows/Framework.h"

export module Launcher.Windows:WindowsEngineParamsProvider;

import <stdexcept>;

import PonyEngine.Core.Factory;
import PonyEngine.Input.Implementation;
import PonyEngine.Log;
import PonyEngine.Window.Windows.Implementation;

import Game.Implementation;

import Launcher;

export namespace Launcher
{
	/// @brief Windows engine system factories provider.
	class SystemFactoriesProvider final : public ISystemFactoriesProvider
	{
	public:
		/// @brief Creates a system factories provider.
		/// @param loggerToUse Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit SystemFactoriesProvider(PonyEngine::Log::ILogger& loggerToUse);
		SystemFactoriesProvider(const SystemFactoriesProvider&) = delete;
		SystemFactoriesProvider(SystemFactoriesProvider&&) = delete;

		~SystemFactoriesProvider() noexcept;

		virtual void AddSystemFactories(PonyEngine::Core::EngineParams& engineParams) const override;

		SystemFactoriesProvider& operator =(const SystemFactoriesProvider&) = delete;
		SystemFactoriesProvider& operator =(SystemFactoriesProvider&&) = delete;

	private:
		PonyEngine::Log::ILogger* const logger; ///< Logger.

		// Set all factories here.

		PonyEngine::Window::WindowsWindowUniquePtr windowsWindowSystemFactory; ///< Window system factory.
		PonyEngine::Input::InputUniquePtr inputSystemFactory; ///< Input system factory.
		Game::GameUniquePtr gameSystemFactory; ///< Game system factory.
	};
}

namespace Launcher
{
	SystemFactoriesProvider::SystemFactoriesProvider(PonyEngine::Log::ILogger& loggerToUse) :
		logger{&loggerToUse}
	{
		// Create all factories here.

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create Windows window system factory.");
		const auto windowClassParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Game", .style = CS_OWNDC};
		windowsWindowSystemFactory = PonyEngine::Window::CreateWindowsWindowFactory(*logger, windowClassParams);
		if (!windowsWindowSystemFactory)
		{
			throw std::logic_error("The Windows window system factory is nullptr.");
		}
		PonyEngine::Window::WindowParams& nextWindowParams = windowsWindowSystemFactory->NextWindowParams();
		nextWindowParams.title = L"Pony Engine Game";
		nextWindowParams.horizontalPosition = CW_USEDEFAULT;
		nextWindowParams.verticalPosition = CW_USEDEFAULT;
		nextWindowParams.width = CW_USEDEFAULT;
		nextWindowParams.height = CW_USEDEFAULT;
		PonyEngine::Window::WindowsWindowParams& nextWindowsWindowParams =  windowsWindowSystemFactory->NextWindowsWindowParams();
		nextWindowsWindowParams.style = WS_OVERLAPPEDWINDOW;
		nextWindowsWindowParams.extendedStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW;
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Windows window system factory created.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create input system factory.");
		inputSystemFactory = PonyEngine::Input::CreateInputSystemFactory();
		if (!inputSystemFactory)
		{
			throw std::logic_error("The input system factory is nullptr.");
		}
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Input system factory created.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create game system factory.");
		gameSystemFactory = Game::CreateGameSystemFactory(*logger);
		if (!gameSystemFactory)
		{
			throw std::logic_error("The game system factory is nullptr.");
		}
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Game system factory created.");
	}

	SystemFactoriesProvider::~SystemFactoriesProvider() noexcept
	{
		// Destroy all factories here.

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy game system factory.");
		gameSystemFactory.reset();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Game system factory destroyed.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy input system factory.");
		inputSystemFactory.reset();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Input system factory destroyed.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy Windows window factory.");
		windowsWindowSystemFactory.reset();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Windows window factory destroyed.");
	}

	void SystemFactoriesProvider::AddSystemFactories(PonyEngine::Core::EngineParams& engineParams) const
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add Windows window system factory.")
		engineParams.AddSystemFactory(*windowsWindowSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Windows window system factory added.")
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add input system factory.")
		engineParams.AddSystemFactory(*inputSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Input system factory added.")
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add game system factory.")
		engineParams.AddSystemFactory(*gameSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Game system factory added.")
	}
}
