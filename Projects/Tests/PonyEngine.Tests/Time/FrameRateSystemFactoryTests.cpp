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
import PonyEngine.Time.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(FrameRateSystemFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto application = Core::Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			Assert::IsNotNull(factory.systemFactory.Get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto inputSystem = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			Assert::IsNotNull(std::get<1>(inputSystem.system).Get());
		}

		TEST_METHOD(GetSystemNameTest)
		{
			auto application = Core::Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			Assert::AreEqual(std::string_view("PonyEngine::Time::FrameRateSystem"), factory.systemFactory->SystemName());
		}

		TEST_METHOD(GetNameTest)
		{
			auto application = Core::Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			Assert::AreEqual(std::string_view("PonyEngine::Time::FrameRateSystemFactory"), factory.systemFactory->Name());
		}
	};
}