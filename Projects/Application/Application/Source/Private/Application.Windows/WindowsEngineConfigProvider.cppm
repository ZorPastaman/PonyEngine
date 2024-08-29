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

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module Application.Windows:WindowsEngineConfigProvider;

import <array>;

import PonyEngine.Core.Factory;
import PonyEngine.Input.Implementation;
import PonyEngine.Log;
import PonyEngine.Render.Direct3D12.Windows.Implementation;
import PonyEngine.Time.Implementation;
import PonyEngine.Window.Windows.Implementation;

import Game.Implementation;

import Application;

export namespace Application
{
	/// @brief Windows engine config provider.
	class WindowsEngineConfigProvider final : public IEngineConfigProvider
	{
	public:
		/// @brief Creates a system factories provider.
		/// @param loggerToUse Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit WindowsEngineConfigProvider(PonyEngine::Log::ILogger& loggerToUse);
		WindowsEngineConfigProvider(const WindowsEngineConfigProvider&) = delete;
		WindowsEngineConfigProvider(WindowsEngineConfigProvider&&) = delete;

		~WindowsEngineConfigProvider() noexcept;

		virtual void AddSystemFactories(PonyEngine::Core::SystemFactoriesContainer& systemFactories) const override;

		virtual void SetupSystems(PonyEngine::Core::ISystemManager& systemManager) const override;

		WindowsEngineConfigProvider& operator =(const WindowsEngineConfigProvider&) = delete;
		WindowsEngineConfigProvider& operator =(WindowsEngineConfigProvider&&) = delete;

	private:
		PonyEngine::Log::ILogger* const logger; ///< Logger.

		std::array<PonyEngine::Core::SystemFactoryUniquePtr, 5> factories; ///< System factories;
	};
}

namespace Application
{
	/// @brief Creates a frame rate system factory.
	/// @param logger Logger to use.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PonyEngine::Time::FrameRateSystemFactoryData CreateFrameRateSystemFactory(PonyEngine::Log::ILogger& logger);
	/// @brief Creates a window system factory.
	/// @param logger Logger to use.
	/// @return Window system factory.
	[[nodiscard("Pure function")]]
	PonyEngine::Window::WindowsWindowSystemFactoryData CreateWindowSystemFactory(PonyEngine::Log::ILogger& logger);
	/// @brief Creates an input system factory.
	/// @param logger Logger to use.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PonyEngine::Input::InputSystemFactoryData CreateInputSystemFactory(PonyEngine::Log::ILogger& logger);
	/// @brief Creates a game system factory.
	/// @param logger Logger to use.
	/// @return Game system factory.
	[[nodiscard("Pure function")]]
	Game::GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Log::ILogger& logger);
	/// @brief Creates a render system factory.
	/// @param logger Logger to use.
	/// @return Render system factory.
	[[nodiscard("Pure function")]]
	PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData CreateRenderSystemFactory(PonyEngine::Log::ILogger& logger);

	WindowsEngineConfigProvider::WindowsEngineConfigProvider(PonyEngine::Log::ILogger& loggerToUse) :
		logger{&loggerToUse},
		factories{CreateFrameRateSystemFactory(*logger).systemFactory, CreateWindowSystemFactory(*logger).systemFactory,
			CreateInputSystemFactory(*logger).systemFactory, CreateGameSystemFactory(*logger).systemFactory, CreateRenderSystemFactory(*logger).systemFactory}
	{
	}

	WindowsEngineConfigProvider::~WindowsEngineConfigProvider() noexcept
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy system factories");
		for (auto it = factories.rbegin(); it != factories.rend(); ++it)
		{
			PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Destroy '{}' system factory.", (*it)->Name());
			it->reset();
			PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "System factory destroyed.");
		}
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "System factories destroyed.");
	}

	void WindowsEngineConfigProvider::AddSystemFactories(PonyEngine::Core::SystemFactoriesContainer& systemFactories) const
	{
		for (const PonyEngine::Core::SystemFactoryUniquePtr& factory : factories)
		{
			PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Add '{}' system factory.", factory->Name());
			systemFactories.AddSystemFactory(*factory);
		}
	}

	void WindowsEngineConfigProvider::SetupSystems(PonyEngine::Core::ISystemManager& systemManager) const
	{
		if (const auto frameRateSystem = systemManager.FindSystem<PonyEngine::Time::IFrameRateSystem>())
		{
			frameRateSystem->TargetFrameTime(PonyEngine::Time::ConvertFrameRateFrameTime(60.f));
		}
	}

	PonyEngine::Time::FrameRateSystemFactoryData CreateFrameRateSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create frame rate system factory.");
		PonyEngine::Time::FrameRateSystemFactoryData factory = PonyEngine::Time::CreateFrameRateSystemFactory(PonyEngine::Time::FrameRateSystemFactoryParams());
		assert(factory.systemFactory && "The frame rate system factory is nullptr.");
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "'{}' frame rate system factory created.", factory.systemFactory->Name());

		return factory;
	}

	PonyEngine::Window::WindowsWindowSystemFactoryData CreateWindowSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create Windows window system factory.");
		const auto windowClassParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Game", .style = CS_OWNDC};
		const auto windowSystemFactoryParams = PonyEngine::Window::WindowsWindowSystemFactoryParams{.logger = logger, .windowsClassParams = windowClassParams};
		PonyEngine::Window::WindowsWindowSystemFactoryData factory = PonyEngine::Window::CreateWindowsWindowFactory(windowSystemFactoryParams);
		assert(factory.systemFactory && "The Windows window system factory is nullptr.");
		assert(factory.windowsWindowSystemFactory && "The pointer to a Windows window system factory is nullptr.");

		constexpr int width = 1280;
		constexpr int height = 720;

		auto windowParams = PonyEngine::Window::WindowsWindowParams();
		windowParams.title = L"Pony Engine Game";
		windowParams.position = PonyEngine::Math::Vector2<int>(GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2);
		windowParams.size = PonyEngine::Math::Vector2<int>(width, height);
		windowParams.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		windowParams.extendedStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW;
		windowParams.cmdShow = SW_NORMAL;
		factory.windowsWindowSystemFactory->NextWindowsWindowParams(windowParams);

		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "'{}' Windows window system factory created.", factory.systemFactory->Name());

		return factory;
	}

	PonyEngine::Input::InputSystemFactoryData CreateInputSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create input system factory.");
		PonyEngine::Input::InputSystemFactoryData factory = PonyEngine::Input::CreateInputSystemFactory(PonyEngine::Input::InputSystemFactoryParams());
		assert(factory.systemFactory && "The input system factory is nullptr");
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "'{}' input system factory created.", factory.systemFactory->Name());

		return factory;
	}

	Game::GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create game system factory.");
		Game::GameSystemFactoryData factory = Game::CreateGameSystemFactory(Game::GameSystemFactoryParams());
		assert(factory.systemFactory && "The game system factory is nullptr");
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "'{}' game system factory created.");

		return factory;
	}

	PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData CreateRenderSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create Direct3D 12 render system for Windows factory.");
		PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData factory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams());
		assert(factory.systemFactory && "The Direct3D render system for Windows factory is nullptr.");
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "'{}' Direct3D 12 render system for Windows factory created.", factory.systemFactory->Name());

		return factory;
	}
}
