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
#include <typeindex>
#include <variant>

import Mocks;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Time.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(TimeSystemFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto application = Mocks::Application();
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), PonyEngine::Time::TimeSystemParams{});
			Assert::IsNotNull(factory.systemFactory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), PonyEngine::Time::TimeSystemParams{});
			auto timeSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			Assert::IsNotNull(std::get<1>(timeSystem.system).get());

			auto interfaces = timeSystem.publicInterfaces.Span();
			Assert::AreEqual(std::size_t{1}, interfaces.size());
			Assert::IsTrue(std::type_index(typeid(PonyEngine::Time::ITimeSystem)) == std::type_index(interfaces[0].first));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Time::ITimeSystem*>(std::get<1>(timeSystem.system).get())), reinterpret_cast<std::uintptr_t>(interfaces[0].second));
		}

		TEST_METHOD(SystemInfoTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), PonyEngine::Time::TimeSystemParams{});
			auto timeSystem = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());

			const PonyEngine::Core::ISystemInfo& info = factory.systemFactory->SystemInfo();
			Assert::IsTrue(typeid(*std::get<1>(timeSystem.system)) == info.SystemType());
			Assert::IsTrue(info.IsTickable());
			Assert::AreEqual(std::size_t{1}, info.InterfaceCount());
		}
	};
}
