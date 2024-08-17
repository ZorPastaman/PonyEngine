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
import PonyEngine.Render.Direct3D12.Windows.Implementation;
import PonyEngine.Time.Implementation;
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

		PonyEngine::Time::FrameRateUniquePtr frameRateSystemFactory; ///< Frame rate system factory.
		PonyEngine::Window::WindowsWindowUniquePtr windowsWindowSystemFactory; ///< Window system factory.
		PonyEngine::Input::InputUniquePtr inputSystemFactory; ///< Input system factory.
		Game::GameUniquePtr gameSystemFactory; ///< Game system factory.
		PonyEngine::Render::WindowsDirect3D12RenderUniquePtr windowsDirect3D12RenderFactory; ///< Direct3D 12 render system for Windows factory.
		// TODO: Make work with factories like work with systems
	};
}

namespace Launcher
{
	SystemFactoriesProvider::SystemFactoriesProvider(PonyEngine::Log::ILogger& loggerToUse) :
		logger{&loggerToUse}
	{
		// Create all factories here.

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create frame rate system factory.");
		frameRateSystemFactory = PonyEngine::Time::CreateFrameRateSystemFactory();
		if (!frameRateSystemFactory)
		{
			throw std::logic_error("The frame rate system factory is nullptr.");
		}
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Frame rate system factory created.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create Windows window system factory.");
		const auto windowClassParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Game", .style = CS_OWNDC};
		windowsWindowSystemFactory = PonyEngine::Window::CreateWindowsWindowFactory(*logger, windowClassParams);
		if (!windowsWindowSystemFactory)
		{
			throw std::logic_error("The Windows window system factory is nullptr.");
		}
		constexpr int width = 1280;
		constexpr int height = 720;
		windowsWindowSystemFactory->NextWindowParams() = PonyEngine::Window::WindowParams
		{
			.title = L"Pony Engine Game",
			.horizontalPosition = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
			.verticalPosition = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
			.width = width,
			.height = height
		};
		windowsWindowSystemFactory->NextWindowsWindowParams() = PonyEngine::Window::WindowsWindowParams
		{
			.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			.extendedStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW,
			.showCmd = SW_NORMAL
		};
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

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create Direct3D 12 render system for Windows factory.");
		windowsDirect3D12RenderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory();
		if (!windowsDirect3D12RenderFactory)
		{
			throw std::logic_error("The Direct3D 12 render system for Windows factory is nullptr");
		}
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Direct3D 12 render system for Windows factory created.");
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

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy Direct3D 12 render system for Windows factory.");
		windowsDirect3D12RenderFactory.reset();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Direct3D 12 render system for Windows factory destroyed.");
	}

	void SystemFactoriesProvider::AddSystemFactories(PonyEngine::Core::EngineParams& engineParams) const
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add frame rate system factory.");
		engineParams.AddSystemFactory(*frameRateSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Frame rate system factory added.");
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add Windows window system factory.");
		engineParams.AddSystemFactory(*windowsWindowSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Windows window system factory added.");
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add input system factory.");
		engineParams.AddSystemFactory(*inputSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Input system factory added.");
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add game system factory.");
		engineParams.AddSystemFactory(*gameSystemFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Game system factory added.");
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add Direct3D 12 render system for Windows factory.");
		engineParams.AddSystemFactory(*windowsDirect3D12RenderFactory);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Direct3D 12 render system for Windows factory added.");
	}
}
