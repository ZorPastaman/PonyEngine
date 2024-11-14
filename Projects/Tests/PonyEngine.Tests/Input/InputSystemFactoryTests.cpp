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
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"

import PonyDebug.Log;

import PonyEngine.Core.Factory;
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
			Assert::IsNotNull(factory.systemFactory.Get());
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
			Assert::IsNotNull(std::get<1>(inputSystem.system).get());
		}

		TEST_METHOD(GetSystemNameTest)
		{
			auto application = Core::Application();
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			Assert::AreEqual(std::string_view("PonyEngine::Input::InputSystem"), factory.systemFactory->SystemName());
		}

		TEST_METHOD(GetNameTest)
		{
			auto application = Core::Application();
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			Assert::AreEqual(std::string_view("PonyEngine::Input::InputSystemFactory"), factory.systemFactory->Name());
		}
	};
}
