/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.Time.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(FrameRateSystemFactoryTests)
	{
		class Application : public PonyEngine::Core::IApplication
		{
		public:
			PonyEngine::Log::ILogger* logger;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& Logger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

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
				logger{&logger}
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

		TEST_METHOD(CreateTest)
		{
			auto application = Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			Assert::IsNotNull(factory.systemFactory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = EmptyLogger();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto inputSystem = factory.systemFactory->Create(engine, systemParams);
			Assert::IsNotNull(inputSystem.system.get());
		}

		TEST_METHOD(GetSystemNameTest)
		{
			auto application = Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			Assert::AreEqual("PonyEngine::Time::FrameRateSystem", factory.systemFactory->SystemName());
		}

		TEST_METHOD(GetNameTest)
		{
			auto application = Application();
			auto factory = PonyEngine::Time::CreateFrameRateSystemFactory(application, PonyEngine::Time::FrameRateSystemFactoryParams());
			Assert::AreEqual("PonyEngine::Time::FrameRateSystemFactory", factory.systemFactory->Name());
		}
	};
}