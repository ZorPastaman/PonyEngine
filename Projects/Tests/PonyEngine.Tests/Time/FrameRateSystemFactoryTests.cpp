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
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Engine.h"
#include "Mocks/Logger.h"

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Time.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(FrameRateSystemFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto application = Mocks::Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams(), PonyEngine::Time::FrameRateSystemParams{});
			Assert::IsNotNull(factory.systemFactory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams(), PonyEngine::Time::FrameRateSystemParams{});
			auto frameRateSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			Assert::IsNotNull(std::get<1>(frameRateSystem.system).get());

			auto interfaces = frameRateSystem.publicInterfaces.Span();
			Assert::AreEqual(std::size_t{1}, interfaces.size());
			Assert::IsTrue(std::type_index(typeid(PonyEngine::Time::IFrameRateSystem)) == std::type_index(interfaces[0].first));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Time::IFrameRateSystem*>(std::get<1>(frameRateSystem.system).get())), reinterpret_cast<std::uintptr_t>(interfaces[0].second));
		}

		TEST_METHOD(SystemTypeTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams(), PonyEngine::Time::FrameRateSystemParams{});
			auto frameRateSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			Assert::IsTrue(typeid(*std::get<1>(frameRateSystem.system)) == factory.systemFactory->SystemType());
		}
	};
}