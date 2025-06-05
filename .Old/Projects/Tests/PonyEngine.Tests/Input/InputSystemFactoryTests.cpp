/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <typeindex>
#include <typeinfo>
#include <variant>

import Mocks;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputSystemFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto application = Mocks::Application();
			const auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			Assert::IsNotNull(factory.systemFactory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto application = Mocks::Application();
			auto logger = Mocks::Logger();
			auto engine = Mocks::Engine();
			application.logger = &logger;
			engine.application = &application;
			const auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			auto inputSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto system = std::get<1>(inputSystem.system).get();
			Assert::IsNotNull(system);

			auto interfaces = inputSystem.publicInterfaces.Span();
			Assert::AreEqual(std::size_t{1}, interfaces.size());
			Assert::IsTrue(std::type_index(typeid(PonyEngine::Input::IInputSystem)) == std::type_index(interfaces[0].first));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputSystem*>(system)), reinterpret_cast<std::uintptr_t>(interfaces[0].second));
		}

		TEST_METHOD(SystemInfoTest)
		{
			auto application = Mocks::Application();
			auto logger = Mocks::Logger();
			auto engine = Mocks::Engine();
			application.logger = &logger;
			engine.application = &application;
			const auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			auto inputSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			const PonyEngine::Core::ISystemInfo& info = factory.systemFactory->SystemInfo();
			Assert::IsTrue(typeid(*std::get<1>(inputSystem.system)) == info.SystemType());
			Assert::IsTrue(info.IsTickable());
			Assert::AreEqual(std::size_t{1}, info.InterfaceCount());
		}
	};
}
