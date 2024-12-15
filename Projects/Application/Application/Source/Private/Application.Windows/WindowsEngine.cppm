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
import <cstdint>;
import <exception>;
import <format>;
import <memory>;
import <typeinfo>;
import <utility>;
import <vector>;

import PonyBase.Core;

import PonyMath.Core;
import PonyMath.Shape;

import PonyDebug.Log;

import PonyEngine.Core.Impl;
import PonyEngine.Input.Windows.Impl;
import PonyEngine.Render.Direct3D12.Windows.Impl;
import PonyEngine.Screen.Windows.Impl;
import PonyEngine.Time.Impl;
import PonyEngine.Window.Windows.Impl;

import Game.Impl;

export namespace Application
{
	/// @brief Pony Engine for Windows wrapper.
	class WindowsEngine final
	{
	public:
		/// @brief Creates a @p WindowsEngine.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit WindowsEngine(PonyEngine::Core::IApplicationContext& application);
		WindowsEngine(const WindowsEngine&) = delete;
		WindowsEngine(WindowsEngine&&) = delete;

		~WindowsEngine() noexcept;

		/// @brief Ticks the engine.
		/// @param exitCode Engine exit code.
		/// @return @a True if the engine is running; @a false otherwise.
		bool Tick(int& exitCode);

		WindowsEngine& operator =(const WindowsEngine&) = delete;
		WindowsEngine& operator =(WindowsEngine&&) = delete;

	private:
		/// @brief Creates a screen system factory.
		/// @return Screen system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Screen::WindowsScreenSystemFactoryData CreateScreenSystemFactory() const;
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
		/// @brief Creates a render system factory.
		/// @return Render system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData CreateRenderSystemFactory() const;
		/// @brief Creates a game system factory.
		/// @return Game system factory.
		[[nodiscard("Pure function")]]
		Game::GameSystemFactoryData CreateGameSystemFactory() const;

		/// @brief Creates an engine.
		/// @return Created engine.
		[[nodiscard("Pure function")]]
		PonyEngine::Core::EngineData CreateEngine() const;

		PonyEngine::Core::IApplicationContext* application; ///< Application.

		std::unique_ptr<PonyEngine::Core::Engine> engine; ///< Engine.
	};
}

namespace Application
{
	WindowsEngine::WindowsEngine(PonyEngine::Core::IApplicationContext& application) :
		application{&application},
		engine{CreateEngine().engine}
	{
	}

	WindowsEngine::~WindowsEngine() noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' engine.", typeid(*engine).name());
		engine.reset();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine destroyed.");
	}

	bool WindowsEngine::Tick(int& exitCode)
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Verbose, "Tick engine.");

		try
		{
			engine->Tick();
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On ticking engine.");
			exitCode = engine->IsRunning() ? static_cast<int>(PonyBase::Core::ExitCodes::EngineTickException) : engine->ExitCode();

			return false;
		}

		if (engine->IsRunning()) [[likely]]
		{
			return true;
		}

		exitCode = engine->ExitCode();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine exited with code '{}'.", exitCode);

		return false;
	}

	PonyEngine::Screen::WindowsScreenSystemFactoryData WindowsEngine::CreateScreenSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows screen system factory.");
			PonyEngine::Screen::WindowsScreenSystemFactoryData factory = PonyEngine::Screen::CreateWindowsScreenFactory(*application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{}, PonyEngine::Screen::WindowsScreenSystemParams{});
			assert(factory.systemFactory && "The Windows screen system factory is nullptr.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows screen system factory created.", typeid(*factory.systemFactory).name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating Windows screen system factory.");

			throw;
		}
	}

	PonyEngine::Time::FrameRateSystemFactoryData WindowsEngine::CreateFrameRateSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create frame rate system factory.");
			const auto systemParams = PonyEngine::Time::FrameRateSystemParams{.targetFrameTime = PonyEngine::Time::ConvertFrameRateFrameTime(60.f)};
			PonyEngine::Time::FrameRateSystemFactoryData factory = PonyEngine::Time::CreateFrameRateSystemFactory(*application, PonyEngine::Time::FrameRateSystemFactoryParams{}, systemParams);
			assert(factory.systemFactory && "The frame rate system factory is nullptr.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' frame rate system factory created.", typeid(*factory.systemFactory).name());

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
			const auto windowsClassParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Game"};
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(*application, windowsClassParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.cursorParams.visible = false;
			systemParams.cursorParams.cursorClipping = PonyMath::Shape::Rect<float>(0.5f, 0.5f, 0.f, 0.f);
			systemParams.windowsWindowStyle.extendedStyle |= WS_EX_APPWINDOW;
			PonyEngine::Window::WindowsWindowSystemFactoryData factory = PonyEngine::Window::CreateWindowsWindowFactory(*application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			assert(factory.systemFactory && "The Windows window system factory is nullptr.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows window system factory created.", typeid(*factory.systemFactory).name());

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
			auto inputParams = PonyEngine::Input::InputSystemParams{};

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create input device factories.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows keyboard device factory.");
			PonyEngine::Input::WindowsKeyboardDeviceFactoryData keyboardDeviceFactory = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory(*application, PonyEngine::Input::WindowsKeyboardDeviceFactoryParams{}, PonyEngine::Input::WindowsKeyboardDeviceParams{});
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows keyboard device factory created.", typeid(*keyboardDeviceFactory.inputDeviceFactory).name());
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows mouse device factory.");
			PonyEngine::Input::WindowsMouseDeviceFactoryData mouseDeviceFactory = PonyEngine::Input::CreateWindowsMouseDeviceFactory(*application, PonyEngine::Input::WindowsMouseDeviceFactoryParams{}, PonyEngine::Input::WindowsMouseDeviceParams{.sensitivity = 0.001f});
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows mouse device factory created.", typeid(*mouseDeviceFactory.inputDeviceFactory).name());
			inputParams.inputDeviceFactories.push_back(std::shared_ptr<PonyEngine::Input::InputDeviceFactory>(std::move(keyboardDeviceFactory.inputDeviceFactory)));
			inputParams.inputDeviceFactories.push_back(std::shared_ptr<PonyEngine::Input::InputDeviceFactory>(std::move(mouseDeviceFactory.inputDeviceFactory)));
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Input device factories created.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Set up input mapping.");
			inputParams.inputBindings["Forward"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::W, .multiplier = 1.f},
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::S, .multiplier = -1.f},
			};
			inputParams.inputBindings["Right"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::D, .multiplier = 1.f},
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::A, .multiplier = -1.f},
			};
			inputParams.inputBindings["Up"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::Space, .multiplier = 1.f},
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::LeftCtrl, .multiplier = -1.f},
			};
			inputParams.inputBindings["Reset"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::Enter, .multiplier = 1.f}
			};
			inputParams.inputBindings["Exit"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::Escape, .multiplier = 1.f}
			};
			inputParams.inputBindings["MouseX"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::MouseXDelta, .multiplier = 1.f}
			};
			inputParams.inputBindings["MouseY"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::MouseYDelta, .multiplier = 1.f}
			};
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Input mapping set up.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create input system factory.");
			PonyEngine::Input::InputSystemFactoryData factory = PonyEngine::Input::CreateInputSystemFactory(*application, PonyEngine::Input::InputSystemFactoryParams{}, inputParams);
			assert(factory.systemFactory && "The input system factory is nullptr");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' input system factory created.", typeid(*factory.systemFactory).name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating input system factory.");

			throw;
		}
	}

	PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData WindowsEngine::CreateRenderSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render system for Windows factory.");
			PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryData factory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(*application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{},
				PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			assert(factory.systemFactory && "The Direct3D render system for Windows factory is nullptr.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Direct3D 12 render system for Windows factory created.", typeid(*factory.systemFactory).name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating Direct3D 12 render system for Windows factory.");

			throw;
		}
	}

	Game::GameSystemFactoryData WindowsEngine::CreateGameSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create game system factory.");
			Game::GameSystemFactoryData factory = Game::CreateGameSystemFactory(*application, Game::GameSystemFactoryParams{}, Game::GameSystemParams{});
			assert(factory.systemFactory && "The game system factory is nullptr");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' game system factory created.", typeid(*factory.systemFactory).name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating game system factory.");

			throw;
		}
	}

	PonyEngine::Core::EngineData WindowsEngine::CreateEngine() const
	{
		try
		{
			auto params = PonyEngine::Core::EngineParams{};

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create system factories.");
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Screen::ScreenSystemFactory>(std::move(CreateScreenSystemFactory().systemFactory))});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Time::FrameRateSystemFactory>(std::move(CreateFrameRateSystemFactory().systemFactory)), .tickOrder = 1});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Window::WindowSystemFactory>(std::move(CreateWindowSystemFactory().systemFactory)), .tickOrder = 2});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Input::InputSystemFactory>(std::move(CreateInputSystemFactory().systemFactory)), .tickOrder = 3});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Render::RenderSystemFactory>(std::move(CreateRenderSystemFactory().systemFactory)), .tickOrder = 5});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<Game::GameSystemFactory>(std::move(CreateGameSystemFactory().systemFactory)), .tickOrder = 4});
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factories created.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create engine.");
			PonyEngine::Core::EngineData engineData = PonyEngine::Core::CreateEngine(*application, params);
			assert(engineData.engine && "The engine is nullptr.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine created.");

			return engineData;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating engine.");

			throw;
		}
	}
}
