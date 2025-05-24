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
#include <optional>
#include <string>
#include <string_view>
#include <typeinfo>
#include <variant>

import Mocks;

import PonyBase.Utility;

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
		class MessageObserver final : public PonyEngine::Window::Windows::IMessageObserver
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
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)});
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
			constexpr std::string_view title = "Test title";
			windowsWindow->TitleBar().Title(title);
			wchar_t gotTitle[64];
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(title.data(), PonyBase::Utility::ConvertToString(gotTitle).c_str());
			Assert::AreEqual(title, windowsWindow->TitleBar().Title());

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
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)});
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
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
			const auto classParams = PonyEngine::Window::Windows::ClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.rect.fullscreen = false;
			systemParams.title = title;
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
			Assert::AreEqual(std::string_view(title), windowsWindow->TitleBar().Title());
		}

		TEST_METHOD(CreateCursorTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::Windows::ClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.rect.fullscreen = false;
			systemParams.cursorParams.visible = false;
			const auto clipping = PonyMath::Shape::Rect<float>(0.25f, 0.25f, 0.5f, 0.5f);;
			systemParams.cursorParams.cursorClipping = clipping;
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
			Assert::IsFalse(windowsWindow->Cursor().IsVisible());
			Assert::IsTrue(clipping == windowsWindow->Cursor().ClippingRect());
		}

		TEST_METHOD(CreateWindowRectTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
			RECT rect;
			GetClientRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(0L, rect.left);
			Assert::AreEqual(0L, rect.top);
			Assert::AreEqual(static_cast<LONG>(screenSystem.DisplayResolution().Width()), rect.right);
			Assert::AreEqual(static_cast<LONG>(screenSystem.DisplayResolution().Height()), rect.bottom);
			std::get<1>(window.system)->End();

			systemParams.rect.fullscreen = false;
			systemParams.rect.position = PonyMath::Core::Vector2<std::int32_t>(120, 130);
			systemParams.rect.resolution = PonyMath::Utility::Resolution<std::uint32_t>(1200u, 670u);
			factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
			GetClientRect(windowsWindow->WindowHandle(), &rect);
			auto leftTop = POINT{.x = rect.left, .y = rect.top};
			auto rightBottom = POINT{.x = rect.right, .y = rect.bottom};
			ClientToScreen(windowsWindow->WindowHandle(), &leftTop);
			ClientToScreen(windowsWindow->WindowHandle(), &rightBottom);
			rect.left = leftTop.x;
			rect.top = leftTop.y;
			rect.right = rightBottom.x;
			rect.bottom = rightBottom.y;
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.X()), rect.left);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.Y()), rect.top);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.X() + systemParams.rect.resolution.Width()), rect.right);
			Assert::AreEqual(static_cast<LONG>(systemParams.rect.position.Y() + systemParams.rect.resolution.Height()), rect.bottom);
			std::get<1>(window.system)->End();
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
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.rect.fullscreen = false;
			systemParams.windowsWindowStyle.style = WS_OVERLAPPEDWINDOW;
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());

			RECT rect;
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			PonyMath::Shape::Rect<std::int32_t> windowRect = windowsWindow->WindowRect();
			Assert::AreEqual(rect.left, static_cast<LONG>(windowRect.MinX()));
			Assert::AreEqual(rect.top, static_cast<LONG>(windowRect.MinY()));
			Assert::AreEqual(rect.right, static_cast<LONG>(windowRect.MaxX()));
			Assert::AreEqual(rect.bottom, static_cast<LONG>(windowRect.MaxY()));

			GetClientRect(windowsWindow->WindowHandle(), &rect);
			auto leftTop = POINT{ .x = rect.left, .y = rect.top };
			auto rightBottom = POINT{ .x = rect.right, .y = rect.bottom };
			ClientToScreen(windowsWindow->WindowHandle(), &leftTop);
			ClientToScreen(windowsWindow->WindowHandle(), &rightBottom);
			rect.left = leftTop.x;
			rect.top = leftTop.y;
			rect.right = rightBottom.x;
			rect.bottom = rightBottom.y;
			windowRect = windowsWindow->WindowClientRect();
			Assert::AreEqual(rect.left, static_cast<LONG>(windowRect.MinX()));
			Assert::AreEqual(rect.top, static_cast<LONG>(windowRect.MinY()));
			Assert::AreEqual(rect.right, static_cast<LONG>(windowRect.MaxX()));
			Assert::AreEqual(rect.bottom, static_cast<LONG>(windowRect.MaxY()));

			std::get<1>(window.system)->End();
		}

		TEST_METHOD(CursorClippingTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			systemParams.rect.fullscreen = false;
			systemParams.windowsWindowStyle.style = WS_OVERLAPPEDWINDOW;
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());

			auto rect = PonyMath::Shape::Rect<float>(0.1f, 0.1f, 0.7f, 0.7f);
			windowsWindow->Cursor().ClippingRect(rect);
			Assert::IsTrue(rect == windowsWindow->Cursor().ClippingRect());

			windowsWindow->Cursor().ClippingRect(std::nullopt);
			Assert::IsTrue(std::nullopt == windowsWindow->Cursor().ClippingRect());
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
			const auto classParams = PonyEngine::Window::Windows::ClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			const auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)};
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
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
			const auto classParams = PonyEngine::Window::Windows::ClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			const auto systemParams = PonyEngine::Window::Windows::WindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) };
			auto factory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			std::get<1>(window.system)->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get());
			auto messageObserver = MessageObserver();
			constexpr auto messages = std::array<UINT, 2>{ WM_KEYDOWN, WM_KEYUP };
			windowsWindow->MessagePump().AddMessageObserver(messageObserver, messages);

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

			windowsWindow->MessagePump().RemoveMessageObserver(messageObserver);
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYDOWN, 0, 1310721);
			std::get<1>(window.system)->Tick();
			Assert::AreEqual(std::size_t{2}, messageObserver.version);

			std::get<1>(window.system)->End();
		}
	};
}
