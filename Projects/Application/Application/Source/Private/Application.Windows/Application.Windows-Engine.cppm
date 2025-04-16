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

export module Application.Windows:Engine;

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

export namespace Application::Windows
{
	/// @brief Pony Engine for Windows wrapper.
	class Engine final
	{
	public:
		/// @brief Creates a @p Engine.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit Engine(PonyEngine::Core::IApplicationContext& application);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		/// @brief Ticks the engine.
		/// @param exitCode Engine exit code.
		/// @return @a True if the engine is running; @a false otherwise.
		bool Tick(int& exitCode);

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:
		/// @brief Creates a screen system factory.
		/// @return Screen system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Screen::Windows::ScreenSystemFactoryData CreateScreenSystemFactory() const;
		/// @brief Creates a frame rate system factory.
		/// @return Frame rate system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Time::FrameRateSystemFactoryData CreateFrameRateSystemFactory() const;
		/// @brief Creates a time system factory.
		/// @return Time system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Time::TimeSystemFactoryData CreateTimeSystemFactory() const;
		/// @brief Creates a window system factory.
		/// @return Window system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Window::Windows::WindowSystemFactoryData CreateWindowSystemFactory() const;
		/// @brief Creates an input system factory.
		/// @return Input system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Input::InputSystemFactoryData CreateInputSystemFactory() const;
		/// @brief Creates a render system factory.
		/// @return Render system factory.
		[[nodiscard("Pure function")]]
		PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryData CreateRenderSystemFactory() const;
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

namespace Application::Windows
{
	Engine::Engine(PonyEngine::Core::IApplicationContext& application) :
		application{&application},
		engine{CreateEngine().engine}
	{
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' engine.", typeid(*engine).name());
		engine.reset();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine destroyed.");
	}

	bool Engine::Tick(int& exitCode)
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

	PonyEngine::Screen::Windows::ScreenSystemFactoryData Engine::CreateScreenSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows screen system factory.");
			PonyEngine::Screen::Windows::ScreenSystemFactoryData factory = PonyEngine::Screen::Windows::CreateScreenFactory(*application, PonyEngine::Screen::Windows::ScreenSystemFactoryParams{}, PonyEngine::Screen::Windows::ScreenSystemParams{});
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

	PonyEngine::Time::FrameRateSystemFactoryData Engine::CreateFrameRateSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create frame rate system factory.");
			constexpr auto systemParams = PonyEngine::Time::FrameRateSystemParams{.targetFrameTime = PonyEngine::Time::ConvertFrameRateFrameTime(0.f)};
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

	PonyEngine::Time::TimeSystemFactoryData Engine::CreateTimeSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create time system factory.");
			constexpr auto systemParams = PonyEngine::Time::TimeSystemParams{};
			PonyEngine::Time::TimeSystemFactoryData factory = PonyEngine::Time::CreateTimeSystemFactory(*application, PonyEngine::Time::TimeSystemFactoryParams{}, systemParams);
			assert(factory.systemFactory && "The time system factory is nullptr.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' time system factory created.", typeid(*factory.systemFactory).name());

			return factory;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating time system factory.");

			throw;
		}
	}

	PonyEngine::Window::Windows::WindowSystemFactoryData Engine::CreateWindowSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window system factory.");
			const auto windowsClassParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Game"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(*application, windowsClassParams);
			auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.cursorParams.visible = false;
			systemParams.cursorParams.cursorClipping = PonyMath::Shape::Rect<float>(0.5f, 0.5f, 0.f, 0.f);
			systemParams.windowsWindowStyle.extendedStyle |= WS_EX_APPWINDOW;
			PonyEngine::Window::Windows::WindowSystemFactoryData factory = PonyEngine::Window::Windows::CreateWindowFactory(*application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
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

	PonyEngine::Input::InputSystemFactoryData Engine::CreateInputSystemFactory() const
	{
		try
		{
			auto inputParams = PonyEngine::Input::InputSystemParams{};
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create input device factories.");
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows keyboard device factory.");
			PonyEngine::Input::Windows::KeyboardDeviceFactoryData keyboardDeviceFactory = PonyEngine::Input::Windows::CreateKeyboardDeviceFactory(*application, PonyEngine::Input::Windows::KeyboardDeviceFactoryParams{}, PonyEngine::Input::Windows::KeyboardDeviceParams{});
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows keyboard device factory created.", typeid(*keyboardDeviceFactory.inputDeviceFactory).name());
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows mouse device factory.");
			PonyEngine::Input::Windows::MouseDeviceFactoryData mouseDeviceFactory = PonyEngine::Input::Windows::CreateMouseDeviceFactory(*application, PonyEngine::Input::Windows::MouseDeviceFactoryParams{}, PonyEngine::Input::Windows::MouseDeviceParams{.sensitivity = 0.001f});
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "'{}' Windows mouse device factory created.", typeid(*mouseDeviceFactory.inputDeviceFactory).name());
			inputParams.inputDeviceFactories.push_back(std::shared_ptr<PonyEngine::Input::DeviceFactory>(std::move(keyboardDeviceFactory.inputDeviceFactory)));
			inputParams.inputDeviceFactories.push_back(std::shared_ptr<PonyEngine::Input::DeviceFactory>(std::move(mouseDeviceFactory.inputDeviceFactory)));
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
			inputParams.inputBindings["Rotate"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::Q, .multiplier = 1.f},
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::E, .multiplier = -1.f},
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

	PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryData Engine::CreateRenderSystemFactory() const
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render system for Windows factory.");
			auto renderParams = PonyEngine::Render::Direct3D12::Windows::RenderSystemParams{};
			renderParams.mainFrameParams.msaa.sampleCount = 4u;
			PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryData factory = PonyEngine::Render::Direct3D12::Windows::CreateRenderSystemFactory(*application, PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryParams{}, renderParams);
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

	Game::GameSystemFactoryData Engine::CreateGameSystemFactory() const
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

	PonyEngine::Core::EngineData Engine::CreateEngine() const
	{
		try
		{
			auto params = PonyEngine::Core::EngineParams{};

			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create system factories.");
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Screen::ScreenSystemFactory>(std::move(CreateScreenSystemFactory().systemFactory))});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Time::FrameRateSystemFactory>(std::move(CreateFrameRateSystemFactory().systemFactory)), .tickOrder = 1});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Time::TimeSystemFactory>(std::move(CreateTimeSystemFactory().systemFactory)), .tickOrder = 2});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Window::WindowSystemFactory>(std::move(CreateWindowSystemFactory().systemFactory)), .tickOrder = 3});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Input::InputSystemFactory>(std::move(CreateInputSystemFactory().systemFactory)), .tickOrder = 4});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<PonyEngine::Render::RenderSystemFactory>(std::move(CreateRenderSystemFactory().systemFactory)), .tickOrder = 6});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = std::shared_ptr<Game::GameSystemFactory>(std::move(CreateGameSystemFactory().systemFactory)), .tickOrder = 5});
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
