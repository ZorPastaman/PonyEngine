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

import PonyBase.Core;

import PonyMath.Core;

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
		PonyEngine::Input::InputSystemFactoryData CreateInputSystemFactory();
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
		PonyEngine::Core::EngineData CreateEngine();

		PonyEngine::Core::IApplicationContext* application; ///< Application.

		std::unique_ptr<PonyEngine::Core::Engine> engine; ///< Engine.

		std::unique_ptr<PonyEngine::Input::InputDeviceFactory> keyboardDevice; // TODO: Remove, make it better
		std::array<PonyEngine::Input::IInputDeviceFactory*, 1> devices;
		std::array<PonyEngine::Input::InputBindingEntry, 2> forward;
	};
}

namespace Application
{
	WindowsEngine::WindowsEngine(PonyEngine::Core::IApplicationContext& application) :
		application{&application},
		engine{CreateEngine().engine},
		keyboardDevice(nullptr)
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

	PonyEngine::Input::InputSystemFactoryData WindowsEngine::CreateInputSystemFactory()
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create input system factory.");
			keyboardDevice.release();
			keyboardDevice = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory();
			devices = std::array<PonyEngine::Input::IInputDeviceFactory*, 1>{ keyboardDevice.get() };
			auto inputParams = PonyEngine::Input::InputSystemParams{};
			inputParams.inputDeviceFactories = devices;
			forward = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::W, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::S, .multiplier = -1.f},
			};
			inputParams.inputBindings["Forward"] = forward;
			constexpr auto right = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::D, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::A, .multiplier = -1.f},
			};
			inputParams.inputBindings["Right"] = right;
			constexpr auto up = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::Space, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::LeftCtrl, .multiplier = -1.f},
			};
			inputParams.inputBindings["Up"] = up;
			constexpr auto rotateRight = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::ArrowRight, .multiplier = -1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::ArrowLeft, .multiplier = 1.f},
			};
			inputParams.inputBindings["RotateRight"] = rotateRight;
			constexpr auto rotateUp = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::ArrowUp, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::ArrowDown, .multiplier = -1.f},
			};
			inputParams.inputBindings["Forward"] = forward;
			constexpr auto xScale = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::X, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::Z, .multiplier = -1.f},
			};
			inputParams.inputBindings["XScale"] = xScale;
			constexpr auto yScale = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::V, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::C, .multiplier = -1.f},
			};
			inputParams.inputBindings["YScale"] = yScale;
			constexpr auto zScale = std::array<PonyEngine::Input::InputBindingEntry, 2>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::N, .multiplier = 1.f},
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::B, .multiplier = -1.f},
			};
			inputParams.inputBindings["ZScale"] = zScale;
			constexpr auto reset = std::array<PonyEngine::Input::InputBindingEntry, 1>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::Enter, .multiplier = 1.f}
			};
			inputParams.inputBindings["Reset"] = reset;
			constexpr auto exit = std::array<PonyEngine::Input::InputBindingEntry, 1>
			{
				PonyEngine::Input::InputBindingEntry{.inputCode = PonyEngine::Input::InputCode::Escape, .multiplier = 1.f}
			};
			inputParams.inputBindings["Exit"] = exit;
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

	PonyEngine::Core::EngineData WindowsEngine::CreateEngine()
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create system factories.");
			auto screenSystemFactory = CreateScreenSystemFactory();
			auto frameRateSystemFactory = CreateFrameRateSystemFactory();
			auto windowSystemFactory = CreateWindowSystemFactory();
			auto inputSystemFactory = CreateInputSystemFactory();
			auto renderSystemFactory = CreateRenderSystemFactory();
			auto gameSystemFactory = CreateGameSystemFactory();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factories created.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create engine.");
			const auto systemFactories = std::array<const std::pair<PonyEngine::Core::ISystemFactory*, std::int32_t>, 6>
			{
				std::pair(screenSystemFactory.systemFactory.get(), 0),
				std::pair(frameRateSystemFactory.systemFactory.get(), 1),
				std::pair(windowSystemFactory.systemFactory.get(), 2),
				std::pair(inputSystemFactory.systemFactory.get(), 3),
				std::pair(renderSystemFactory.systemFactory.get(), 5),
				std::pair(gameSystemFactory.systemFactory.get(), 4),
			};
			const auto params = PonyEngine::Core::EngineParams{.systemFactories = systemFactories};
			PonyEngine::Core::EngineData engineData = PonyEngine::Core::CreateEngine(*application, params);
			assert(engineData.engine && "The engine is nullptr.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine created.");

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy system factories.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system factory.", typeid(*gameSystemFactory.systemFactory).name());
			gameSystemFactory.systemFactory.reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factory destroyed.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system factory.", typeid(*renderSystemFactory.systemFactory).name());
			renderSystemFactory.systemFactory.reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factory destroyed.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system factory.", typeid(*inputSystemFactory.systemFactory).name());
			inputSystemFactory.systemFactory.reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factory destroyed.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system factory.", typeid(*windowSystemFactory.systemFactory).name());
			windowSystemFactory.systemFactory.reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factory destroyed.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system factory.", typeid(*frameRateSystemFactory.systemFactory).name());
			frameRateSystemFactory.systemFactory.reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factory destroyed.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system factory.", typeid(*screenSystemFactory.systemFactory).name());
			screenSystemFactory.systemFactory.reset();
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factory destroyed.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "System factories destroyed.");

			return engineData;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating engine.");

			throw;
		}
	}
}
