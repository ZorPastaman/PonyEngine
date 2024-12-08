/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <typeinfo>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/System.h"
#include "Mocks/SystemFactory.h"
#include "Mocks/TickableSystem.h"
#include "Mocks/TickableSystemFactory.h"

import PonyDebug.Log;

import PonyEngine.Core.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			const auto engine = PonyEngine::Core::CreateEngine(application, PonyEngine::Core::EngineParams());
			Assert::IsNotNull(engine.engine.get());
		}

		TEST_METHOD(GetFrameCountTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			const auto engine = PonyEngine::Core::CreateEngine(application, PonyEngine::Core::EngineParams());

			for (std::size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, engine.engine->FrameCount());
				engine.engine->Tick();
				Assert::AreEqual(i + 1, engine.engine->FrameCount());
			}
		}

		TEST_METHOD(ExitTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = PonyEngine::Core::CreateEngine(application, PonyEngine::Core::EngineParams());
			Assert::IsTrue(engine.engine->IsRunning());
			engine.engine->Stop();
			Assert::IsFalse(engine.engine->IsRunning());
			Assert::AreEqual(0, engine.engine->ExitCode());
			engine.engine.reset();
			engine = PonyEngine::Core::CreateEngine(application, PonyEngine::Core::EngineParams());
			engine.engine->Stop(100);
			Assert::AreEqual(100, engine.engine->ExitCode());
		}

		TEST_METHOD(SystemTickTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto systemFactory = std::make_shared<Mocks::TickableSystemFactory>();
			auto params = PonyEngine::Core::EngineParams{};
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = systemFactory});
			auto engine = PonyEngine::Core::CreateEngine(application, params);

			Assert::IsNotNull(systemFactory->GetSystem());
			Assert::AreEqual(std::size_t{1}, systemFactory->Version());
			Assert::AreEqual(std::size_t{1}, systemFactory->GetSystem()->BeginCount());

			Assert::AreEqual(std::size_t{0}, systemFactory->GetSystem()->TickCount());

			engine.engine->Tick();
			Assert::AreEqual(std::size_t{1}, systemFactory->GetSystem()->TickCount());

			engine.engine->Tick();
			Assert::AreEqual(std::size_t{2}, systemFactory->GetSystem()->TickCount());

			bool ended = false;
			systemFactory->GetSystem()->onDestructed = &ended;
			engine.engine.reset();
			Assert::IsTrue(ended);
		}

		TEST_METHOD(FindSystemTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto systemFactory = std::make_shared<Mocks::SystemFactory>();
			auto tickableSystemFactory = std::make_shared<Mocks::TickableSystemFactory>();
			auto params = PonyEngine::Core::EngineParams{};
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = systemFactory});
			params.systemFactories.push_back(PonyEngine::Core::SystemFactoryEntry{.factory = tickableSystemFactory});
			auto engine = PonyEngine::Core::CreateEngine(application, params);

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<Mocks::ISystemInterface*>(systemFactory->GetSystem())), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem(typeid(Mocks::ISystemInterface))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<Mocks::ISystemInterface*>(systemFactory->GetSystem())), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem<Mocks::ISystemInterface>()));

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<Mocks::ITickableSystemInterface*>(tickableSystemFactory->GetSystem())), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem(typeid(Mocks::ITickableSystemInterface))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<Mocks::ITickableSystemInterface*>(tickableSystemFactory->GetSystem())), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem<Mocks::ITickableSystemInterface>()));

			Assert::IsNull(engine.engine->SystemManager().FindSystem(typeid(Mocks::System)));
			Assert::IsNull(engine.engine->SystemManager().FindSystem<Mocks::System>());

			Assert::IsNull(engine.engine->SystemManager().FindSystem(typeid(Mocks::TickableSystem)));
			Assert::IsNull(engine.engine->SystemManager().FindSystem<Mocks::TickableSystem>());
		}
	};
} 
