/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "PonyBase/Core/Windows/Framework.h"

#include <cstddef>
#include <exception>
#include <string>
#include <string_view>
#include <typeinfo>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Engine.h"
#include "Mocks/Logger.h"

import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core.Factory;
import PonyEngine.Input;
import PonyEngine.Screen;
import PonyEngine.Window.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowTests)
	{
		class KeyboardObserver final : public PonyEngine::Input::IKeyboardObserver
		{
		public:
			PonyEngine::Input::KeyboardMessage lastMessage;
			std::size_t version = 0;

			virtual void Observe(const PonyEngine::Input::KeyboardMessage& keyboardMessage) override
			{
				lastMessage = keyboardMessage;
				++version;
			}

			[[nodiscard("Pure function")]]
			virtual std::string_view Name() const noexcept override
			{
				return "";
			}
		};

		class ScreenSystem final : public PonyEngine::Screen::IScreenSystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual PonyMath::Utility::Resolution<unsigned int> DisplayResolution() const noexcept override
			{
				return PonyMath::Utility::Resolution<unsigned int>(static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN)), static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN)));
			}

			[[nodiscard("Pure function")]]
			virtual std::string_view Name() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(GetSetTitleTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass });
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			constexpr std::wstring_view title = L"Test title";
			windowsWindow->MainTitle(title);
			wchar_t gotTitle[64];
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(title, std::wstring_view(gotTitle));
			Assert::AreEqual(title, windowsWindow->MainTitle());

			constexpr std::wstring_view secondaryTitle = L"Secondary";
			windowsWindow->SecondaryTitle(secondaryTitle);
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(secondaryTitle, windowsWindow->SecondaryTitle());
			Assert::AreEqual((std::wstring(title) + L" - " + std::wstring(secondaryTitle)).c_str(), gotTitle);

			std::get<1>(window.system)->End();
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass };
			systemParams.rect.fullscreen = false;
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			Assert::AreEqual(std::string_view("PonyEngine::Window::WindowsWindowSystem"), windowsWindow->Name());
		}

		TEST_METHOD(ShowHideWindowTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass });
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			windowsWindow->ShowWindow();
			Assert::IsTrue(IsWindowVisible(windowsWindow->WindowHandle()));
			Assert::IsTrue(windowsWindow->IsVisible());
			windowsWindow->HideWindow();
			Assert::IsFalse(IsWindowVisible(windowsWindow->WindowHandle()));
			Assert::IsFalse(windowsWindow->IsVisible());
			std::get<1>(window.system)->End();
		}

		TEST_METHOD(CreateTitleTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			std::wstring title = L"Test title";
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass };
			systemParams.rect.fullscreen = false;
			systemParams.title = title;
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			Assert::AreEqual(std::wstring_view(title), windowsWindow->MainTitle());
		}

		TEST_METHOD(WindowRectTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = windowsClass};
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			RECT rect;
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(0L, rect.left);
			Assert::AreEqual(0L, rect.top);
			Assert::AreEqual(static_cast<LONG>(GetSystemMetrics(SM_CXSCREEN)), rect.right);
			Assert::AreEqual(static_cast<LONG>(GetSystemMetrics(SM_CYSCREEN)), rect.bottom);
			std::get<1>(window.system)->End();

			systemParams.rect.fullscreen = false;
			factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			std::get<1>(window.system)->Begin();
			windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.X()), rect.left);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.Y()), rect.top);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.X() + systemParams.rect.resolution.Width()), rect.right);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.Y() + systemParams.rect.resolution.Height()), rect.bottom);
			std::get<1>(window.system)->End();
		}

		TEST_METHOD(DestroyMessageTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			const auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = windowsClass };
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			PostMessageW(windowsWindow->WindowHandle(), WM_DESTROY, 0, 0);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(0, engine.ExitCode());
			std::get<1>(window.system)->End();
		}

		TEST_METHOD(InputMessageTest)
		{
			auto logger = Core::Logger();
			auto screenSystem = ScreenSystem();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass });
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get());
			auto keyboardObserver = KeyboardObserver();
			auto keyboardProvider = dynamic_cast<PonyEngine::Input::IKeyboardProvider*>(std::get<1>(window.system).Get());
			keyboardProvider->AddKeyboardObserver(keyboardObserver);
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYDOWN, 0, LPARAM{1310721});
			std::get<1>(window.system)->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::T, .isDown = true});
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYUP, 0, LPARAM{3080193});
			std::get<1>(window.system)->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::V, .isDown = false});
			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYDOWN, 0, LPARAM{540540929});
			std::get<1>(window.system)->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::LeftAlt, .isDown = true});
			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYUP, 0, LPARAM{557318145});
			std::get<1>(window.system)->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::RightAlt, .isDown = false});
			std::get<1>(window.system)->End();
		}
	};
}
