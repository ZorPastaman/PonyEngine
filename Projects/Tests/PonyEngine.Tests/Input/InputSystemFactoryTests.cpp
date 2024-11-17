/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <typeinfo>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"

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
			auto application = Core::Application();
			const auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			Assert::IsNotNull(factory.systemFactory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto application = Core::Application();
			auto logger = Core::Logger();
			auto engine = Core::Engine();
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

		TEST_METHOD(SystemTypeTest)
		{
			auto application = Core::Application();
			auto logger = Core::Logger();
			auto engine = Core::Engine();
			application.logger = &logger;
			engine.application = &application;
			const auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			auto inputSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			Assert::IsTrue(typeid(*std::get<1>(inputSystem.system)) == factory.systemFactory->SystemType());
		}
	};
}
