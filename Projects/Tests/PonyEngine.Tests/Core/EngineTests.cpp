/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstddef>;
import <cstdint>;
import <functional>;
import <exception>;

import PonyEngine.Core;
import PonyEngine.Core.Factory;
import PonyEngine.Core.Implementation;
import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Log(PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override { }
			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override { }

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger*) override { }
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger*) override { }
		};

		class EmptySystem final : public PonyEngine::Core::ISystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Begin() override { }
			virtual void End() override { }

			virtual void Tick() override { }
		};

		class EmptySystemFactory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			PonyEngine::Core::ISystem* createdSystem = nullptr;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::SystemInfo Create(PonyEngine::Core::IEngine&) override
			{
				const auto emptySystem = new EmptySystem();
				createdSystem = emptySystem;

				return PonyEngine::Core::SystemInfo::Create<EmptySystem, EmptySystem>(*emptySystem, *this, true);
			}
			virtual void Destroy(PonyEngine::Core::ISystem* const system) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptySystem*>(system));
				delete static_cast<EmptySystem*>(system);
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetSystemName() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(CreateTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			const auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsNotNull(engine.get());
		}

		TEST_METHOD(GetFrameCountTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			const auto engine = PonyEngine::Core::CreateEngine(params);
			
			for (std::size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, engine->GetTimeManager().GetFrameCount());
				engine->Tick();
				Assert::AreEqual(i + 1, engine->GetTimeManager().GetFrameCount());
			}
		}

		TEST_METHOD(GetLoggerTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			const auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&logger), reinterpret_cast<std::uintptr_t>(&(engine->GetLogger())));
		}

		TEST_METHOD(FindSystemTest)
		{
			EmptyLogger logger;
			EmptySystemFactory systemFactory;
			auto params = PonyEngine::Core::EngineParams(logger);
			params.AddSystemFactory(systemFactory);
			const auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine->GetSystemManager().FindSystem(typeid(EmptySystem))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine->GetSystemManager().FindSystem<EmptySystem>()));
		}

		TEST_METHOD(ExitTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsTrue(engine->IsRunning());
			engine->Stop();
			Assert::IsFalse(engine->IsRunning());
			Assert::AreEqual(0, engine->GetExitCode());
			engine.reset();
			engine = PonyEngine::Core::CreateEngine(params);
			engine->Stop(100);
			Assert::AreEqual(100, engine->GetExitCode());
		}
	};
} 
