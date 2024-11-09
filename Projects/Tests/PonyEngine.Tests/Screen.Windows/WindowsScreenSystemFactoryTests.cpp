/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <typeindex>
#include <typeinfo>
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
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{}, PonyEngine::Screen::WindowsScreenSystemParams{});
			Assert::IsNotNull(factory.systemFactory.Get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{}, PonyEngine::Screen::WindowsScreenSystemParams{});
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams{});
			auto screenSystem = std::get<0>(system.system).Get();
			Assert::IsNotNull(screenSystem);

			auto interfaces = system.publicInterfaces.Span();
			Assert::AreEqual(std::size_t{2}, interfaces.size());
			Assert::IsTrue(std::type_index(typeid(PonyEngine::Screen::IScreenSystem)) == std::type_index(interfaces[0].first));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Screen::IScreenSystem*>(screenSystem)), reinterpret_cast<std::uintptr_t>(interfaces[0].second));
			Assert::IsTrue(std::type_index(typeid(PonyEngine::Screen::IWindowsScreenSystem)) == std::type_index(interfaces[1].first));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Screen::IWindowsScreenSystem*>(screenSystem)), reinterpret_cast<std::uintptr_t>(interfaces[1].second));
		}

		TEST_METHOD(SystemNameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{}, PonyEngine::Screen::WindowsScreenSystemParams{});
			Assert::AreEqual(std::string_view("PonyEngine::Screen::WindowsScreenSystem"), factory.systemFactory->SystemName());
		}

		TEST_METHOD(NameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{}, PonyEngine::Screen::WindowsScreenSystemParams{});
			Assert::AreEqual(std::string_view("PonyEngine::Screen::WindowsScreenSystemFactory"), factory.systemFactory->Name());
		}
	};
}
