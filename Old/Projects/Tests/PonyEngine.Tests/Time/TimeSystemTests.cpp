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
#include <cstdint>
#include <thread>
#include <variant>

import Mocks;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Time.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(TimeSystemTests)
	{
		TEST_METHOD(TickTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			constexpr auto params = PonyEngine::Time::TimeSystemParams{.deltaTimeCap = 10.f, .timeScale = 0.5f, .framePeriod = 1.f / 100.f};
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), params);

			std::chrono::time_point<std::chrono::steady_clock> beforeCreateTime = std::chrono::steady_clock::now();
			auto timeSystemData = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto timeSystem = dynamic_cast<PonyEngine::Time::ITimeSystem*>(std::get<1>(timeSystemData.system).get());

			std::this_thread::sleep_for(std::chrono::seconds(3ULL));
			std::get<1>(timeSystemData.system)->Tick();
			std::chrono::time_point<std::chrono::steady_clock> afterTickTime = std::chrono::steady_clock::now();

			Assert::IsTrue(std::chrono::duration<double>(afterTickTime - beforeCreateTime).count() >= timeSystem->RealTime());
			Assert::IsTrue(3. <= timeSystem->RealTime());
			Assert::AreEqual(std::chrono::duration<double>(timeSystem->ThisFrameTimePoint() - timeSystem->EngineStartTimePoint()).count(), timeSystem->RealTime(), 0.000001);
			Assert::AreEqual(timeSystem->RealTime(), timeSystem->VirtualTime() * 2.f, 0.000001);
			Assert::AreEqual(timeSystem->RealTime(), timeSystem->UnscaledVirtualTime(), 0.000001);
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->RealTime() / params.framePeriod), timeSystem->RealFrameCount());
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->VirtualTime() / params.framePeriod), timeSystem->VirtualFrameCount());
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->UnscaledVirtualTime() / params.framePeriod), timeSystem->UnscaledVirtualFrameCount());
			Assert::AreEqual(timeSystem->RealTime(), static_cast<double>(timeSystem->RealDeltaTime()), 0.000001);
			Assert::AreEqual(timeSystem->VirtualTime(), static_cast<double>(timeSystem->VirtualDeltaTime()), 0.000001);
			Assert::AreEqual(timeSystem->UnscaledVirtualTime(), static_cast<double>(timeSystem->UnscaledVirtualDeltaTime()), 0.000001);
			Assert::AreEqual(timeSystem->RealFrameCount(), static_cast<std::uint64_t>(timeSystem->RealDeltaFrame()));
			Assert::AreEqual(timeSystem->VirtualFrameCount(), static_cast<std::uint64_t>(timeSystem->VirtualDeltaFrame()));
			Assert::AreEqual(timeSystem->UnscaledVirtualFrameCount(), static_cast<std::uint64_t>(timeSystem->UnscaledVirtualDeltaFrame()));
			Assert::IsTrue(beforeCreateTime <= timeSystem->EngineStartTimePoint() && afterTickTime >= timeSystem->EngineStartTimePoint());
			Assert::IsTrue(timeSystem->EngineStartTimePoint() == timeSystem->PrevFrameTimePoint());
			Assert::IsTrue(beforeCreateTime + std::chrono::duration<double>(std::chrono::seconds(3ULL)) < timeSystem->ThisFrameTimePoint());

			std::chrono::time_point<std::chrono::steady_clock> prevTickTime = afterTickTime;
			std::chrono::time_point<std::chrono::steady_clock> prevTimePoint = timeSystem->ThisFrameTimePoint();
			const std::chrono::time_point<std::chrono::steady_clock> engineStartTime = timeSystem->EngineStartTimePoint();
			std::uint32_t realDeltaFrame = timeSystem->RealDeltaFrame();
			std::uint32_t virtualDeltaFrame = timeSystem->VirtualDeltaFrame();
			std::uint32_t unscaledVirtualDeltaFrame = timeSystem->UnscaledVirtualDeltaFrame();
			std::this_thread::sleep_for(std::chrono::seconds(4ULL));
			std::get<1>(timeSystemData.system)->Tick();
			afterTickTime = std::chrono::steady_clock::now();

			Assert::IsTrue(std::chrono::duration<double>(afterTickTime - beforeCreateTime).count() >= timeSystem->RealTime());
			Assert::IsTrue(7. <= timeSystem->RealTime());
			Assert::AreEqual(std::chrono::duration<double>(timeSystem->ThisFrameTimePoint() - timeSystem->EngineStartTimePoint()).count(), timeSystem->RealTime(), 0.000001);
			Assert::AreEqual(timeSystem->RealTime(), timeSystem->VirtualTime() * 2.f, 0.000001);
			Assert::AreEqual(timeSystem->RealTime(), timeSystem->UnscaledVirtualTime(), 0.000001);
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->RealTime() / params.framePeriod), timeSystem->RealFrameCount());
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->VirtualTime() / params.framePeriod), timeSystem->VirtualFrameCount());
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->UnscaledVirtualTime() / params.framePeriod), timeSystem->UnscaledVirtualFrameCount());
			Assert::IsTrue(4.f < timeSystem->RealDeltaTime());
			Assert::IsTrue(2.f < timeSystem->VirtualDeltaTime());
			Assert::IsTrue(4.f < timeSystem->UnscaledVirtualDeltaTime());
			Assert::AreEqual(static_cast<std::uint32_t>(timeSystem->RealTime() / params.framePeriod) - realDeltaFrame, timeSystem->RealDeltaFrame());
			Assert::AreEqual(static_cast<std::uint32_t>(timeSystem->VirtualTime() / params.framePeriod) - virtualDeltaFrame, timeSystem->VirtualDeltaFrame());
			Assert::AreEqual(static_cast<std::uint32_t>(timeSystem->UnscaledVirtualTime() / params.framePeriod) - unscaledVirtualDeltaFrame, timeSystem->UnscaledVirtualDeltaFrame());
			Assert::IsTrue(engineStartTime == timeSystem->EngineStartTimePoint());
			Assert::IsTrue(prevTimePoint == timeSystem->PrevFrameTimePoint());
			Assert::IsTrue(prevTimePoint + std::chrono::duration<double>(std::chrono::seconds(4ULL)) < timeSystem->ThisFrameTimePoint());

			prevTickTime = afterTickTime;
			prevTimePoint = timeSystem->ThisFrameTimePoint();
			realDeltaFrame += timeSystem->RealDeltaFrame();
			virtualDeltaFrame += timeSystem->VirtualDeltaFrame();
			unscaledVirtualDeltaFrame += timeSystem->UnscaledVirtualDeltaFrame();
			const double prevVirtualTime = timeSystem->VirtualTime();
			const double prevUnscaledVirtualTime = timeSystem->UnscaledVirtualTime();
			std::this_thread::sleep_for(std::chrono::seconds(20ULL));
			std::get<1>(timeSystemData.system)->Tick();
			afterTickTime = std::chrono::steady_clock::now();

			Assert::IsTrue(std::chrono::duration<double>(afterTickTime - beforeCreateTime).count() >= timeSystem->RealTime());
			Assert::IsTrue(27. <= timeSystem->RealTime());
			Assert::AreEqual(std::chrono::duration<double>(timeSystem->ThisFrameTimePoint() - timeSystem->EngineStartTimePoint()).count(), timeSystem->RealTime(), 0.000001);
			Assert::AreEqual(prevVirtualTime + 5., timeSystem->VirtualTime(), 0.000001);
			Assert::AreEqual(prevUnscaledVirtualTime + 10., timeSystem->UnscaledVirtualTime(), 0.000001);
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->RealTime() / params.framePeriod), timeSystem->RealFrameCount());
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->VirtualTime() / params.framePeriod), timeSystem->VirtualFrameCount());
			Assert::AreEqual(static_cast<std::uint64_t>(timeSystem->UnscaledVirtualTime() / params.framePeriod), timeSystem->UnscaledVirtualFrameCount());
			Assert::IsTrue(20.f < timeSystem->RealDeltaTime());
			Assert::AreEqual(5.f, timeSystem->VirtualDeltaTime(), 0.000001f);
			Assert::AreEqual(10.f, timeSystem->UnscaledVirtualDeltaTime());
			Assert::AreEqual(static_cast<std::uint32_t>(timeSystem->RealTime() / params.framePeriod) - realDeltaFrame, timeSystem->RealDeltaFrame());
			Assert::AreEqual(static_cast<std::uint32_t>(timeSystem->VirtualTime() / params.framePeriod) - virtualDeltaFrame, timeSystem->VirtualDeltaFrame());
			Assert::AreEqual(static_cast<std::uint32_t>(timeSystem->UnscaledVirtualTime() / params.framePeriod) - unscaledVirtualDeltaFrame, timeSystem->UnscaledVirtualDeltaFrame());
			Assert::IsTrue(engineStartTime == timeSystem->EngineStartTimePoint());
			Assert::IsTrue(prevTimePoint == timeSystem->PrevFrameTimePoint());
			Assert::IsTrue(prevTimePoint + std::chrono::duration<double>(std::chrono::seconds(20ULL)) < timeSystem->ThisFrameTimePoint());
		}

		TEST_METHOD(DeltaTimeCapTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			constexpr auto params = PonyEngine::Time::TimeSystemParams{.deltaTimeCap = 10.f, .timeScale = 0.5f, .framePeriod = 1.f / 100.f};
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), params);
			auto timeSystemData = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto timeSystem = dynamic_cast<PonyEngine::Time::ITimeSystem*>(std::get<1>(timeSystemData.system).get());
			Assert::AreEqual(params.deltaTimeCap, timeSystem->DeltaTimeCap());
			timeSystem->DeltaTimeCap(5.f);
			Assert::AreEqual(5.f, timeSystem->DeltaTimeCap());
		}

		TEST_METHOD(TimeScaleTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			constexpr auto params = PonyEngine::Time::TimeSystemParams{.deltaTimeCap = 10.f, .timeScale = 0.5f, .framePeriod = 1.f / 100.f};
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), params);
			auto timeSystemData = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto timeSystem = dynamic_cast<PonyEngine::Time::ITimeSystem*>(std::get<1>(timeSystemData.system).get());
			Assert::AreEqual(params.timeScale, timeSystem->TimeScale());
			timeSystem->TimeScale(2.f);
			Assert::AreEqual(2.f, timeSystem->TimeScale());
		}

		TEST_METHOD(FramePeriodTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			constexpr auto params = PonyEngine::Time::TimeSystemParams{ .deltaTimeCap = 10.f, .timeScale = 0.5f, .framePeriod = 1.f / 100.f };
			auto factory = PonyEngine::Time::CreateTimeSystemFactory(application, PonyEngine::Time::TimeSystemFactoryParams(), params);
			auto timeSystemData = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			auto timeSystem = dynamic_cast<PonyEngine::Time::ITimeSystem*>(std::get<1>(timeSystemData.system).get());
			Assert::AreEqual(params.framePeriod, timeSystem->FramePeriod());
			timeSystem->FramePeriod(3.f);
			Assert::AreEqual(3.f, timeSystem->FramePeriod());
		}
	};
}
