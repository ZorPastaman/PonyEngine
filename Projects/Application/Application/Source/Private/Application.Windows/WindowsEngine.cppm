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

#include "PonyDebug/Log/Log.h"

export module Application.Windows:WindowsEngine;

import <array>;
import <exception>;

import PonyBase.Core;
import PonyBase.Math;
import PonyBase.Screen;

import PonyDebug.Log;

import PonyEngine.Core.Implementation;
import PonyEngine.Input.Implementation;
import PonyEngine.Render.Direct3D12.Windows.Implementation;
import PonyEngine.Time.Implementation;
import PonyEngine.Window.Windows.Implementation;

import Game.Implementation;

export namespace Application
{
	/// @brief Pony Engine for Windows wrapper.
	class WindowsEngine final
	{
	public:
		/// @brief Creates a @p WindowsEngine.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit WindowsEngine(PonyEngine::Core::IApplication& application);
		WindowsEngine(const WindowsEngine&) = delete;
		WindowsEngine(WindowsEngine&&) = delete;

		~WindowsEngine() noexcept;

		/// @brief Ticks the engine.
		/// @param exitCode Engine exit code.
		/// @return @a True if the engine is running; @a false otherwise.
		bool Tick(int& exitCode) const;

		WindowsEngine& operator =(const WindowsEngine&) = delete;
		WindowsEngine& operator =(WindowsEngine&&) = delete;

	private:
		/// @brief Creates a frame rate system factory.
		/// @return Frame rate system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Time::FrameRateSystemFactoryData CreateFrameRateSystemFactory() const;
		/// @brief Creates a window system factory.
		/// @return Window system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Window::WindowsWindowSystemFactoryData CreateWindowSystemFactory() const;
		/// @brief Creates an input system factory.
		/// @return Input system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Input::InputSystemFactoryData CreateInputSystemFactory() const;
		/// @brief Creates a game system factory.
		/// @return Game system factory.
		[[nodiscard("Pure function")]]
		Game::GameSystemFactoryData CreateGameSystemFactory() const;
		/// @brief Creates a render system factory.
		/// @return Render system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData CreateRenderSystemFactory() const;

		/// @brief Creates an engine.
		/// @return Created engine.
		[[nodiscard("Pure function")]]
		PonyEngine::Core::EngineData CreateEngine();

		/// @brief Sets up the frame rate system.
		void SetupFrameRateSystem() const noexcept;

		static constexpr auto DefaultResolution = PonyBase::Screen::Resolution<unsigned int>(1280u, 720u);
		static constexpr bool DefaultWindowed = false;

		PonyEngine::Core::IApplication* application; ///< Application.

		std::array<PonyEngine::Core::SystemFactoryUniquePtr, 5> systemFactories; ///< System factories.
		PonyEngine::Core::EngineData engine; ///< Engine.
	};
}

namespace Application
{
	WindowsEngine::WindowsEngine(PonyEngine::Core::IApplication& application) :
		application{&application},
		systemFactories{CreateFrameRateSystemFactory().systemFactory, CreateWindowSystemFactory().systemFactory, CreateInputSystemFactory().systemFactory, CreateGameSystemFactory().systemFactory, CreateRenderSystemFactory().systemFactory},
		engine{CreateEngine()}
	{
		SetupFrameRateSystem();
	}

	WindowsEngine::~WindowsEngine() noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' engine.", engine.engine->Name());
		engine.engine.reset();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine destroyed.");

		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy system factories.");
		for (auto it = systemFactories.rbegin(); it != systemFactories.rend(); ++it)
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Debug, "Destroy '{}' system factory.", (*it)->Name());
			it->reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Debug, "System factory destroyed.");
		}
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factories destroyed.");
	}

	bool WindowsEngine::Tick(int& exitCode) const
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Verbose, "Tick engine.");

		try
		{
			engine.tickableEngine->Tick();
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On ticking engine.");
			exitCode = engine.engine->IsRunning() ? static_cast<int>(PonyBase::Core::ExitCodes::EngineTickException) : engine.engine->ExitCode();

			return false;
		}

		if (engine.engine->IsRunning()) [[likely]]
		{
			return true;
		}

		exitCode = engine.engine->ExitCode();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine exited with code '{}'.", exitCode);

		return false;
	}

	PonyEngine::Time::FrameRateSystemFactoryData WindowsEngine::CreateFrameRateSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create frame rate system factory.");
			PonyEngine::Time::FrameRateSystemFactoryData factory = PonyEngine::Time::CreateFrameRateSystemFactory(*application, PonyEngine::Time::FrameRateSystemFactoryParams{});
			assert(factory.systemFactory && "The frame rate system factory is nullptr.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' frame rate system factory created.", factory.systemFactory->Name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating frame rate system factory.");

			throw;
		}
	}

	PonyEngine::Window::WindowsWindowSystemFactoryData WindowsEngine::CreateWindowSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window system factory.");
			const auto windowClassParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Game", .style = PonyEngine::Window::DefaultClassStyle};
			const auto windowSystemFactoryParams = PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = windowClassParams };
			PonyEngine::Window::WindowsWindowSystemFactoryData factory = PonyEngine::Window::CreateWindowsWindowFactory(*application, windowSystemFactoryParams);
			assert(factory.systemFactory && "The Windows window system factory is nullptr.");
			assert(factory.windowSystemFactory && "Windows window system factory extended interface is nullptr.");

			const bool windowed = DefaultWindowed;
			const auto size = windowed ? DefaultResolution : PonyEngine::Window::GetDisplaySize();

			PonyEngine::Window::WindowsWindowParams& windowParams = factory.windowSystemFactory->WindowParams();
			windowParams.title = L"Pony Engine Game";
			windowParams.position = PonyEngine::Window::CalculateCenteredWindowPosition(size);
			windowParams.size = size;
			windowParams.style = windowed ? PonyEngine::Window::DefaultWindowedStyle : PonyEngine::Window::DefaultBorderlessWindowedStyle;
			windowParams.extendedStyle = (windowed ? PonyEngine::Window::DefaultWindowedExtendedStyle : PonyEngine::Window::DefaultBorderlessWindowedExtendedStyle) | WS_EX_APPWINDOW;
			windowParams.cmdShow = SW_NORMAL;

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows window system factory created.", factory.systemFactory->Name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating Windows window system factory.");

			throw;
		}
	}

	PonyEngine::Input::InputSystemFactoryData WindowsEngine::CreateInputSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create input system factory.");
			PonyEngine::Input::InputSystemFactoryData factory = PonyEngine::Input::CreateInputSystemFactory(*application, PonyEngine::Input::InputSystemFactoryParams{});
			assert(factory.systemFactory && "The input system factory is nullptr");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' input system factory created.", factory.systemFactory->Name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating input system factory.");

			throw;
		}
	}

	Game::GameSystemFactoryData WindowsEngine::CreateGameSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create game system factory.");
			Game::GameSystemFactoryData factory = Game::CreateGameSystemFactory(*application, Game::GameSystemFactoryParams{});
			assert(factory.systemFactory && "The game system factory is nullptr");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' game system factory created.", factory.systemFactory->Name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating game system factory.");

			throw;
		}
	}

	PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData WindowsEngine::CreateRenderSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render system for Windows factory.");
			PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData factory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(*application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{});
			assert(factory.systemFactory && "The Direct3D render system for Windows factory is nullptr.");
			assert(factory.renderSystemFactory && "The Direct3D render system for Windows factory interface is nullptr.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Direct3D 12 render system for Windows factory created.", factory.systemFactory->Name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating Direct3D 12 render system for Windows factory.");

			throw;
		}
	}

	PonyEngine::Core::EngineData WindowsEngine::CreateEngine()
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create engine.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Debug, "Create engine params.");
			auto params = PonyEngine::Core::EngineParams{};
			for (PonyEngine::Core::SystemFactoryUniquePtr& factory : systemFactories)
			{
				PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' system factory to params", factory->Name());
				params.systemFactories.AddSystemFactory(*factory);
			}
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Debug, "Engine params created.");
			
			PonyEngine::Core::EngineData engineData = PonyEngine::Core::CreateEngine(*application, params);
			assert(engineData.engine && "The engine is nullptr.");
			assert(engineData.tickableEngine && "The tickable engine is nullptr.");

			return engineData;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating engine.");

			throw;
		}
	}

	void WindowsEngine::SetupFrameRateSystem() const noexcept
	{
		const auto frameRateSystem = engine.engine->SystemManager().FindSystem<PonyEngine::Time::IFrameRateSystem>();
		assert(frameRateSystem && "The frame rate system is nullptr.");

		frameRateSystem->TargetFrameTime(PonyEngine::Time::ConvertFrameRateFrameTime(60.f));
	}
}
