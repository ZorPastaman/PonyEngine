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

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyEngine/Log/Log.h"

export module Application.Windows:WindowsEngine;

import <array>;
import <exception>;

import PonyBase.Core;

import PonyEngine.Core.Implementation;
import PonyEngine.Input.Implementation;
import PonyEngine.Log;
import PonyEngine.Render.Direct3D12.Windows.Implementation;
import PonyEngine.Time.Implementation;
import PonyEngine.Window.Windows.Implementation;

import Game.Implementation;

import Application;

export namespace Application
{
	/// @brief Pony Engine for Windows wrapper.
	class WindowsEngine final : PonyEngine::Core::IApplication
	{
	public:
		/// @brief Creates a @p WindowsEngine.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit WindowsEngine(Application::IApplication& application);
		WindowsEngine(const WindowsEngine&) = delete;
		WindowsEngine(WindowsEngine&&) = delete;

		~WindowsEngine() noexcept;

		/// @brief Ticks the engine.
		/// @param exitCode Engine exit code.
		/// @return @a True if the engine is running; @a false otherwise.
		bool Tick(int& exitCode) const;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsEngine& operator =(const WindowsEngine&) = delete;
		WindowsEngine& operator =(WindowsEngine&&) = delete;

	private:
		/// @brief Creates a frame rate system factory.
		/// @return Frame rate system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Time::FrameRateSystemFactoryData CreateFrameRateSystemFactory();
		/// @brief Creates a window system factory.
		/// @return Window system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Window::WindowsWindowSystemFactoryData CreateWindowSystemFactory();
		/// @brief Creates an input system factory.
		/// @return Input system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Input::InputSystemFactoryData CreateInputSystemFactory();
		/// @brief Creates a game system factory.
		/// @return Game system factory.
		[[nodiscard("Pure function")]]
		Game::GameSystemFactoryData CreateGameSystemFactory();
		/// @brief Creates a render system factory.
		/// @return Render system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData CreateRenderSystemFactory();

		/// @brief Creates an engine.
		/// @return Created engine.
		[[nodiscard("Pure function")]]
		PonyEngine::Core::EngineData CreateEngine();

		/// @brief Sets up the frame rate system.
		void SetupFrameRateSystem() const noexcept;

		Application::IApplication* application; ///< Application.

		std::array<PonyEngine::Core::SystemFactoryUniquePtr, 5> systemFactories; ///< System factories.
		PonyEngine::Core::EngineData engine; ///< Engine.
	};
}

namespace Application
{
	WindowsEngine::WindowsEngine(Application::IApplication& application) :
		application{&application},
		systemFactories{CreateFrameRateSystemFactory().systemFactory, CreateWindowSystemFactory().systemFactory, CreateInputSystemFactory().systemFactory, CreateGameSystemFactory().systemFactory, CreateRenderSystemFactory().systemFactory},
		engine{CreateEngine()}
	{
		SetupFrameRateSystem();
	}

	WindowsEngine::~WindowsEngine() noexcept
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Destroy '{}' engine.", engine.engine->Name());
		engine.engine.reset();
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Engine destroyed.");

		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Destroy system factories.");
		for (auto it = systemFactories.rbegin(); it != systemFactories.rend(); ++it)
		{
			PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Debug, "Destroy '{}' system factory.", (*it)->Name());
			it->reset();
			PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Debug, "System factory destroyed.");
		}
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "System factories destroyed.");
	}

	bool WindowsEngine::Tick(int& exitCode) const
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Verbose, "Tick engine.");

		try
		{
			engine.tickableEngine->Tick();
		}
		catch (const std::exception& e)
		{
			if (!engine.engine->IsRunning())
			{
				// Logging is done in the engine.
				exitCode = engine.engine->ExitCode(); // TODO: No guessing. Add exception wrapper for handled by engine exceptions.

				return false;
			}

			PONY_LOG_E_GENERAL(&application->Logger(), e, "On ticking engine.")
			exitCode = static_cast<int>(PonyBase::Core::ExitCodes::EngineTickException);

			return false;
		}

		if (engine.engine->IsRunning()) [[likely]]
		{
			return true;
		}

		exitCode = engine.engine->ExitCode();
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Engine exited with code '{}'.", exitCode);

		return false;
	}

	PonyEngine::Log::ILogger& WindowsEngine::Logger() const noexcept
	{
		return application->Logger();
	}

	const char* WindowsEngine::Name() const noexcept
	{
		return application->Name();
	}

	PonyEngine::Time::FrameRateSystemFactoryData WindowsEngine::CreateFrameRateSystemFactory()
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Create frame rate system factory.");
		PonyEngine::Time::FrameRateSystemFactoryData factory = PonyEngine::Time::CreateFrameRateSystemFactory(*this, PonyEngine::Time::FrameRateSystemFactoryParams());
		assert(factory.systemFactory && "The frame rate system factory is nullptr.");
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "'{}' frame rate system factory created.", factory.systemFactory->Name());

		return factory;
	}

	PonyEngine::Window::WindowsWindowSystemFactoryData WindowsEngine::CreateWindowSystemFactory()
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Create Windows window system factory.");
		const auto windowClassParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Game", .style = CS_OWNDC};
		const auto windowSystemFactoryParams = PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = windowClassParams };
		PonyEngine::Window::WindowsWindowSystemFactoryData factory = PonyEngine::Window::CreateWindowsWindowFactory(*this, windowSystemFactoryParams);
		assert(factory.systemFactory && "The Windows window system factory is nullptr.");
		assert(factory.windowSystemFactory && "Windows window system factory extended interface is nullptr.");

		constexpr int width = 1280;
		constexpr int height = 720;

		PonyEngine::Window::WindowsWindowParams& windowParams = factory.windowSystemFactory->WindowParams();
		windowParams.title = L"Pony Engine Game";
		windowParams.position = PonyBase::Math::Vector2<int>(GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2);
		windowParams.size = PonyBase::Math::Vector2<int>(width, height);
		windowParams.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		windowParams.extendedStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW;
		windowParams.cmdShow = SW_NORMAL;

		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "'{}' Windows window system factory created.", factory.systemFactory->Name());

		return factory;
	}

	PonyEngine::Input::InputSystemFactoryData WindowsEngine::CreateInputSystemFactory()
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Create input system factory.");
		PonyEngine::Input::InputSystemFactoryData factory = PonyEngine::Input::CreateInputSystemFactory(*this, PonyEngine::Input::InputSystemFactoryParams());
		assert(factory.systemFactory && "The input system factory is nullptr");
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "'{}' input system factory created.", factory.systemFactory->Name());

		return factory;
	}

	Game::GameSystemFactoryData WindowsEngine::CreateGameSystemFactory()
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Create game system factory.");
		Game::GameSystemFactoryData factory = Game::CreateGameSystemFactory(*this, Game::GameSystemFactoryParams());
		assert(factory.systemFactory && "The game system factory is nullptr");
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "'{}' game system factory created.");

		return factory;
	}

	PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData WindowsEngine::CreateRenderSystemFactory()
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Create Direct3D 12 render system for Windows factory.");
		PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData factory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(*this, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams());
		assert(factory.systemFactory && "The Direct3D render system for Windows factory is nullptr.");
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "'{}' Direct3D 12 render system for Windows factory created.", factory.systemFactory->Name());

		return factory;
	}

	PonyEngine::Core::EngineData WindowsEngine::CreateEngine()
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Create engine.");

		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Debug, "Create engine params.");
		auto params = PonyEngine::Core::EngineParams();
		for (PonyEngine::Core::SystemFactoryUniquePtr& factory : systemFactories)
		{
			PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Debug, "Add '{}' system factory to params", factory->Name());
			params.systemFactories.AddSystemFactory(*factory);
		}
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Debug, "Engine params created.");
		
		PonyEngine::Core::EngineData engineData = PonyEngine::Core::CreateEngine(*this, params);
		assert(engineData.engine && "The engine is nullptr.");
		assert(engineData.tickableEngine && "The tickable engine is nullptr.");

		return engineData;
	}

	void WindowsEngine::SetupFrameRateSystem() const noexcept
	{
		const auto frameRateSystem = engine.engine->SystemManager().FindSystem<PonyEngine::Time::IFrameRateSystem>();
		assert(frameRateSystem && "The frame rate system is nullptr.");

		frameRateSystem->TargetFrameTime(PonyEngine::Time::ConvertFrameRateFrameTime(60.f));
	}
}
