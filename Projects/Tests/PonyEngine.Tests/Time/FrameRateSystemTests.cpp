/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <chrono>;
import <cstddef>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.Time.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(FrameRateSystemTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Log(PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override
			{
			}
			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}
		};

		class EmptySystemManager : public PonyEngine::Core::ISystemManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info&) const noexcept override
			{
				return nullptr;
			}
		};

		class EmptyEngine : public PonyEngine::Core::IEngine, public PonyEngine::Core::ITickableEngine
		{
		public:
			EmptyLogger* logger;
			mutable EmptySystemManager systemManager;

			explicit EmptyEngine(EmptyLogger& logger) noexcept :
				logger{ &logger }
			{
			}

			[[nodiscard("Pure function")]]
			virtual std::size_t FrameCount() const noexcept override
			{
				return 0;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& Logger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystemManager& SystemManager() const noexcept override
			{
				return systemManager;
			}

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override
			{
				return true;
			}

			[[nodiscard("Pure function")]]
			virtual int ExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Tick() override
			{
			}
		};

		TEST_METHOD(TickTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory();
			const auto systemParams = PonyEngine::Core::SystemParams{.engine = engine};
			auto frameRateSystemBase = factory->Create(systemParams);
			auto frameRateSystem = dynamic_cast<PonyEngine::Time::IFrameRateSystem*>(frameRateSystemBase.system.get());
			frameRateSystemBase.system->Begin();
			float frameTime = 5.f;
			frameRateSystem->TargetFrameTime(frameTime);
			auto now = std::chrono::steady_clock::now();
			frameRateSystemBase.tickableSystem->Tick();
			auto timeDiff = std::chrono::steady_clock::now() - now;
			Assert::IsFalse(timeDiff >= std::chrono::duration<float>(frameTime));
			frameRateSystemBase.tickableSystem->Tick();
			timeDiff = std::chrono::steady_clock::now() - now;
			Assert::IsTrue(timeDiff >= std::chrono::duration<float>(frameTime));
			frameRateSystemBase.system->End();
		}

		TEST_METHOD(GetSetFrameTimeRate)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory();
			const auto systemParams = PonyEngine::Core::SystemParams{.engine = engine};
			auto frameRateSystemBase = factory->Create(systemParams);
			auto frameRateSystem = dynamic_cast<PonyEngine::Time::IFrameRateSystem*>(frameRateSystemBase.system.get());

			Assert::AreEqual(0.f, frameRateSystem->TargetFrameTime());
			Assert::AreEqual(0.f, frameRateSystem->TargetFrameRate());

			frameRateSystem->TargetFrameTime(0.16f);
			Assert::AreEqual(0.16f, frameRateSystem->TargetFrameTime());
			Assert::AreEqual(1.f / 0.16f, frameRateSystem->TargetFrameRate());

			frameRateSystem->TargetFrameTime(0.f);
			Assert::AreEqual(0.f, frameRateSystem->TargetFrameTime());
			Assert::AreEqual(0.f, frameRateSystem->TargetFrameRate());

			frameRateSystem->TargetFrameRate(90.f);
			Assert::AreEqual(1.f / 90.f, frameRateSystem->TargetFrameTime());
			Assert::AreEqual(90.f, frameRateSystem->TargetFrameRate());

			frameRateSystem->TargetFrameRate(0.f);
			Assert::AreEqual(0.f, frameRateSystem->TargetFrameTime());
			Assert::AreEqual(0.f, frameRateSystem->TargetFrameRate());
		}
	};
}
