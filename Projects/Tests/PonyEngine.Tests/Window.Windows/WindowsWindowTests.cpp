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
#include <format>
#include <string>
#include <string_view>
#include <typeinfo>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Engine.h"
#include "Mocks/Logger.h"
#include "Mocks/ScreenSystem.h"

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Screen;
import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowTests)
	{
		class MessageObserver final : public PonyEngine::Window::IWindowsMessageObserver
		{
		public:
			std::size_t version;
			UINT lastMessage;
			WPARAM lastWParam;
			LPARAM lastLParam;

			virtual void Observe(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) override
			{
				++version;
				lastMessage = uMsg;
				lastWParam = wParam;
				lastLParam = lParam;
			}
		};

		TEST_METHOD(GetSetTitleTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)});
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
			constexpr std::string_view title = "Test title";
			windowsWindow->TitleBar().MainTitle(title);
			wchar_t gotTitle[64];
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(title.data(), PonyBase::Utility::ConvertToString(gotTitle).c_str());
			Assert::AreEqual(title, windowsWindow->TitleBar().MainTitle());

			constexpr std::string_view secondaryTitle = "Secondary";
			windowsWindow->TitleBar().SecondaryTitle(secondaryTitle);
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(secondaryTitle, windowsWindow->TitleBar().SecondaryTitle());
			Assert::AreEqual(std::format("{} - {}", title, secondaryTitle).c_str(), PonyBase::Utility::ConvertToString(gotTitle).c_str());

			std::get<1>(window.system)->End();
		}

		TEST_METHOD(ShowHideWindowTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)});
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
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
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			std::string title = "Test title";
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.rect.fullscreen = false;
			systemParams.title = title;
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
			Assert::AreEqual(std::string_view(title), windowsWindow->TitleBar().MainTitle());
		}

		TEST_METHOD(WindowRectTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
			RECT rect;
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(0L, rect.left);
			Assert::AreEqual(0L, rect.top);
			Assert::AreEqual(static_cast<LONG>(screenSystem.DisplayResolution().Width()), rect.right);
			Assert::AreEqual(static_cast<LONG>(screenSystem.DisplayResolution().Height()), rect.bottom);
			std::get<1>(window.system)->End();

			systemParams.rect.fullscreen = false;
			factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.X()), rect.left);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.Y()), rect.top);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.X() + systemParams.rect.resolution.Width()), rect.right);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.Y() + systemParams.rect.resolution.Height()), rect.bottom);
			std::get<1>(window.system)->End();
		}

		TEST_METHOD(DestroyMessageTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			const auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
			PostMessageW(windowsWindow->WindowHandle(), WM_DESTROY, 0, 0);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(0, engine.ExitCode());
			std::get<1>(window.system)->End();
		}

		TEST_METHOD(MessageObserverTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			const auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) };
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get());
			auto messageObserver = MessageObserver();
			constexpr auto messages = std::array<UINT, 2>{ WM_KEYDOWN, WM_KEYUP };
			windowsWindow->AddMessageObserver(messageObserver, messages);

			PostMessageW(windowsWindow->WindowHandle(), WM_KEYDOWN, 0, 1310721);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(std::size_t{1}, messageObserver.version);
			Assert::AreEqual(static_cast<UINT>(WM_KEYDOWN), messageObserver.lastMessage);
			Assert::AreEqual(static_cast<WPARAM>(0), messageObserver.lastWParam);
			Assert::AreEqual(static_cast<LPARAM>(1310721), messageObserver.lastLParam);

			PostMessageW(windowsWindow->WindowHandle(), WM_KEYUP, 0, 3080193);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(std::size_t{2}, messageObserver.version);
			Assert::AreEqual(static_cast<UINT>(WM_KEYUP), messageObserver.lastMessage);
			Assert::AreEqual(static_cast<WPARAM>(0), messageObserver.lastWParam);
			Assert::AreEqual(static_cast<LPARAM>(3080193), messageObserver.lastLParam);

			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYUP, 0, 3080193);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(std::size_t{2}, messageObserver.version);

			windowsWindow->RemoveMessageObserver(messageObserver);
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYDOWN, 0, 1310721);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(std::size_t{2}, messageObserver.version);

			std::get<1>(window.system)->End();
		}
	};
}
