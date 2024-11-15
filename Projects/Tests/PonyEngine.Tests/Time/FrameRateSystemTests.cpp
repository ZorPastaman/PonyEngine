/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <chrono>
#include <cstddef>
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
	TEST_CLASS(FrameRateSystemTests)
	{
		TEST_METHOD(TickTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams(), PonyEngine::Time::FrameRateSystemParams{});
			auto frameRateSystemBase = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto frameRateSystem = dynamic_cast<PonyEngine::Time::IFrameRateSystem*>(std::get<1>(frameRateSystemBase.system).get());
			std::get<1>(frameRateSystemBase.system)->Begin();
			float frameTime = 1.f;
			frameRateSystem->TargetFrameTime(frameTime);
			auto now = std::chrono::steady_clock::now();
			std::get<1>(frameRateSystemBase.system)->Tick();
			auto timeDiff = std::chrono::steady_clock::now() - now;
			Assert::IsFalse(timeDiff >= std::chrono::duration<float>(frameTime));
			std::get<1>(frameRateSystemBase.system)->Tick();
			timeDiff = std::chrono::steady_clock::now() - now;
			Assert::IsTrue(timeDiff >= std::chrono::duration<float>(frameTime));
			std::get<1>(frameRateSystemBase.system)->End();
		}

		TEST_METHOD(GetSetFrameTimeRate)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams(), PonyEngine::Time::FrameRateSystemParams{});
			auto frameRateSystemBase = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto frameRateSystem = dynamic_cast<PonyEngine::Time::IFrameRateSystem*>(std::get<1>(frameRateSystemBase.system).get());

			Assert::AreEqual(0.f, frameRateSystem->TargetFrameTime());

			frameRateSystem->TargetFrameTime(0.16f);
			Assert::AreEqual(0.16f, frameRateSystem->TargetFrameTime());

			frameRateSystem->TargetFrameTime(0.f);
			Assert::AreEqual(0.f, frameRateSystem->TargetFrameTime());
		}
	};
}
