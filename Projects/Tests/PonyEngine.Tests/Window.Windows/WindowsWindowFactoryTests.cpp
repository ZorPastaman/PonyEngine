/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <string_view>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Engine.h"
#include "Mocks/Logger.h"

import PonyDebug.Log;

import PonyEngine.Core.Factory;
import PonyEngine.Input;
import PonyEngine.Window.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = windowsClass});
			Assert::IsNotNull(factory.systemFactory.Get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto classParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Test" };
			const auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto systemParams = PonyEngine::Window::WindowsWindowSystemParams{.windowsClass = windowsClass};
			systemParams.rect.fullscreen = false;
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, systemParams);
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			Assert::IsNotNull(std::get<1>(window.system).Get());

			auto it = window.publicInterfaces.Begin();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Window::IWindowSystem*>(std::get<1>(window.system).Get())), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).Get())), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IKeyboardProvider*>(std::get<1>(window.system).Get())), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(it == window.publicInterfaces.End());
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass });
			Assert::AreEqual(std::string_view("PonyEngine::Window::WindowsWindowSystemFactory"), factory.systemFactory->Name());
		}

		TEST_METHOD(GetSystemName)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = windowsClass });
			Assert::AreEqual(std::string_view("PonyEngine::Window::WindowsWindowSystem"), factory.systemFactory->SystemName());
		}
	};
}
