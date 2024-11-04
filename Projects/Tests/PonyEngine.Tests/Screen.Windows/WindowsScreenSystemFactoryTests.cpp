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
#include <utility>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"

import PonyEngine.Screen.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Screen
{
	TEST_CLASS(WindowsScreenSystemFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{});
			Assert::IsNotNull(factory.systemFactory.Get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{});
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams{});
			auto screenSystem = std::get<0>(system.system).Get();
			Assert::IsNotNull(screenSystem);

			auto it = system.publicInterfaces.Begin();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Screen::IScreenSystem*>(screenSystem)), reinterpret_cast<std::uintptr_t>(it->second));
			++it;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Screen::IWindowsScreenSystem*>(screenSystem)), reinterpret_cast<std::uintptr_t>(it->second));
			++it;
			Assert::IsTrue(it == system.publicInterfaces.End());
		}

		TEST_METHOD(SystemNameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{});
			Assert::AreEqual(std::string_view("PonyEngine::Screen::WindowsScreenSystem"), factory.systemFactory->SystemName());
		}

		TEST_METHOD(NameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{});
			Assert::AreEqual(std::string_view("PonyEngine::Screen::WindowsScreenSystemFactory"), factory.systemFactory->Name());
		}
	};
}
