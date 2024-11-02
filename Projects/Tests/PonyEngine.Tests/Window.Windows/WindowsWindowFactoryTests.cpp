/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <string_view>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Engine.h"
#include "Mocks/Logger.h"

import PonyDebug.Log;

import PonyEngine.Core.Factory;
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
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			Assert::IsNotNull(factory.systemFactory.Get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{ .windowsClassParams = classParams });
			auto window = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			Assert::IsNotNull(std::get<1>(window.system).Get());
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams });
			Assert::AreEqual(std::string_view("PonyEngine::Window::WindowsWindowSystemFactory"), factory.systemFactory->Name());
		}

		TEST_METHOD(GetSystemName)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams });
			Assert::AreEqual(std::string_view("PonyEngine::Window::WindowsWindowSystem"), factory.systemFactory->SystemName());
		}
	};
}
