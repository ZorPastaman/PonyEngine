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
import <exception>;

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
			bool begun = false;
			bool* ended = nullptr;
			bool ticked = false;

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Begin() override
			{
				begun = true;
			}

			virtual void End() override
			{
				if (ended)
				{
					*ended = true;
				}
			}

			virtual void Tick() override
			{
				ticked = true;
			}
		};

		class EmptySystem1Base : public PonyEngine::Core::ISystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Begin() override
			{
			}
			virtual void End() override
			{
			}

			virtual void Tick() override
			{
			}
		};

		class EmptySystem1 final : public EmptySystem1Base
		{
		};

		class EmptySystemFactory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			EmptySystem* createdSystem = nullptr;
			bool systemDestroyed = false;

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
				systemDestroyed = true;
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

		class EmptySystem1Factory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			EmptySystem1* createdSystem = nullptr;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::SystemInfo Create(PonyEngine::Core::IEngine&) override
			{
				const auto emptySystem = new EmptySystem1();
				createdSystem = emptySystem;

				return PonyEngine::Core::SystemInfo::Create<EmptySystem1, EmptySystem1Base>(*emptySystem, *this, true);
			}
			virtual void Destroy(PonyEngine::Core::ISystem* const system) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptySystem1*>(system));
				delete static_cast<EmptySystem1*>(system);
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

		TEST_METHOD(SystemTickTest)
		{
			EmptyLogger logger;
			EmptySystemFactory systemFactory;
			auto params = PonyEngine::Core::EngineParams(logger);
			params.AddSystemFactory(systemFactory);
			auto engine = PonyEngine::Core::CreateEngine(params);

			Assert::IsTrue(systemFactory.createdSystem->begun);

			Assert::IsFalse(systemFactory.createdSystem->ticked);

			engine->Tick();
			Assert::IsTrue(systemFactory.createdSystem->ticked);

			systemFactory.createdSystem->ticked = false;
			engine->Tick();
			Assert::IsTrue(systemFactory.createdSystem->ticked);

			bool ended = false;
			systemFactory.createdSystem->ended = &ended;
			engine.reset();
			Assert::IsTrue(ended);
			Assert::IsTrue(systemFactory.systemDestroyed);
		}

		TEST_METHOD(GetLoggerTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			const auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&logger), reinterpret_cast<std::uintptr_t>(&(engine->GetLogger())));
		}

		TEST_METHOD(ExitTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsTrue(engine->GetIsRunning());
			engine->Stop();
			Assert::IsFalse(engine->GetIsRunning());
			Assert::AreEqual(0, engine->GetExitCode());
			engine.reset();
			engine = PonyEngine::Core::CreateEngine(params);
			engine->Stop(100);
			Assert::AreEqual(100, engine->GetExitCode());
		}

		TEST_METHOD(GetNameTest)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual("PonyEngine::Core::Engine", engine->GetName());
		}

		TEST_METHOD(FindSystemTest)
		{
			EmptyLogger logger;
			EmptySystemFactory systemFactory;
			EmptySystem1Factory system1Factory;
			auto params = PonyEngine::Core::EngineParams(logger);
			params.AddSystemFactory(systemFactory);
			params.AddSystemFactory(system1Factory);
			const auto engine = PonyEngine::Core::CreateEngine(params);

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine->GetSystemManager().FindSystem(typeid(EmptySystem))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine->GetSystemManager().FindSystem<EmptySystem>()));

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<EmptySystem1Base*>(system1Factory.createdSystem)), reinterpret_cast<std::uintptr_t>(engine->GetSystemManager().FindSystem(typeid(EmptySystem1Base))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<EmptySystem1Base*>(system1Factory.createdSystem)), reinterpret_cast<std::uintptr_t>(engine->GetSystemManager().FindSystem<EmptySystem1Base>()));

			Assert::IsNull(engine->GetSystemManager().FindSystem(typeid(EmptySystem1)));
			Assert::IsNull(engine->GetSystemManager().FindSystem<EmptySystem1>());

			Assert::IsNull(engine->GetSystemManager().FindSystem(typeid(PonyEngine::Core::ISystem)));
			Assert::IsNull(engine->GetSystemManager().FindSystem<PonyEngine::Core::ISystem>());
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

		TEST_METHOD(GetSetFrameTimeRate)
		{
			EmptyLogger logger;
			const auto params = PonyEngine::Core::EngineParams(logger);
			const auto engine = PonyEngine::Core::CreateEngine(params);

			Assert::AreEqual(0.f, engine->GetTimeManager().GetTargetFrameTime());
			Assert::AreEqual(0.f, engine->GetTimeManager().GetTargetFrameRate());

			engine->GetTimeManager().SetTargetFrameTime(0.16f);
			Assert::AreEqual(0.16f, engine->GetTimeManager().GetTargetFrameTime());
			Assert::AreEqual(1.f / 0.16f, engine->GetTimeManager().GetTargetFrameRate());

			engine->GetTimeManager().SetTargetFrameTime(0.f);
			Assert::AreEqual(0.f, engine->GetTimeManager().GetTargetFrameTime());
			Assert::AreEqual(0.f, engine->GetTimeManager().GetTargetFrameRate());

			engine->GetTimeManager().SetTargetFrameRate(90.f);
			Assert::AreEqual(1.f / 90.f, engine->GetTimeManager().GetTargetFrameTime());
			Assert::AreEqual(90.f, engine->GetTimeManager().GetTargetFrameRate());

			engine->GetTimeManager().SetTargetFrameRate(0.f);
			Assert::AreEqual(0.f, engine->GetTimeManager().GetTargetFrameTime());
			Assert::AreEqual(0.f, engine->GetTimeManager().GetTargetFrameRate());
		}
	};
} 
