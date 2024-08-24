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
			virtual const char* Name() const noexcept override { return ""; }

			virtual void Log(PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override { }
			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override { }

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger&) override { }
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger&) override { }
		};

		class EmptySystem final : public PonyEngine::Core::ISystem, public PonyEngine::Core::ITickableSystem
		{
		public:
			bool begun = false;
			bool* ended = nullptr;
			bool ticked = false;

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override { return ""; }

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
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Begin() override
			{
			}
			virtual void End() override
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
			virtual PonyEngine::Core::SystemData Create(const PonyEngine::Core::SystemParams&) override
			{
				createdSystem = new EmptySystem();
				const auto deleter = PonyEngine::Core::SystemDeleter(*this);
				auto interfaces = PonyEngine::Core::ObjectInterfaces();
				interfaces.AddInterfacesDeduced<EmptySystem>(*createdSystem);

				return PonyEngine::Core::SystemData
				{
					.system = PonyEngine::Core::SystemUniquePtr(createdSystem, deleter),
					.tickableSystem = createdSystem,
					.publicInterfaces = interfaces
				};
			}
			virtual void Destroy(PonyEngine::Core::ISystem* const system) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptySystem*>(system));
				delete static_cast<EmptySystem*>(system);
				systemDestroyed = true;
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			[[nodiscard("Pure function")]]
			virtual const char* SystemName() const noexcept override
			{
				return "";
			}
		};

		class EmptySystem1Factory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			EmptySystem1* createdSystem = nullptr;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::SystemData Create(const PonyEngine::Core::SystemParams&) override
			{
				createdSystem = new EmptySystem1();
				const auto deleter = PonyEngine::Core::SystemDeleter(*this);
				auto interfaces = PonyEngine::Core::ObjectInterfaces();
				interfaces.AddInterfacesDeduced<EmptySystem1Base>(*createdSystem);

				return PonyEngine::Core::SystemData
				{
					.system = PonyEngine::Core::SystemUniquePtr(createdSystem, deleter),
					.publicInterfaces = interfaces
				};
			}
			virtual void Destroy(PonyEngine::Core::ISystem* const system) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptySystem1*>(system));
				delete static_cast<EmptySystem1*>(system);
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			[[nodiscard("Pure function")]]
			virtual const char* SystemName() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(CreateTest)
		{
			auto logger = EmptyLogger();
			const auto params = PonyEngine::Core::EngineParams{.logger = &logger};
			const auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsNotNull(engine.engine.get());
			Assert::IsNotNull(engine.tickableEngine);
		}

		TEST_METHOD(GetFrameCountTest)
		{
			auto logger = EmptyLogger();
			const auto params = PonyEngine::Core::EngineParams{ .logger = &logger };
			const auto engine = PonyEngine::Core::CreateEngine(params);

			for (std::size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, engine.engine->FrameCount());
				engine.tickableEngine->Tick();
				Assert::AreEqual(i + 1, engine.engine->FrameCount());
			}
		}

		TEST_METHOD(GetLoggerTest)
		{
			auto logger = EmptyLogger();
			const auto params = PonyEngine::Core::EngineParams{.logger = &logger};
			const auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&logger), reinterpret_cast<std::uintptr_t>(&engine.engine->Logger()));
		}

		TEST_METHOD(ExitTest)
		{
			auto logger = EmptyLogger();
			const auto params = PonyEngine::Core::EngineParams{.logger = &logger};
			auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsTrue(engine.engine->IsRunning());
			engine.engine->Stop();
			Assert::IsFalse(engine.engine->IsRunning());
			Assert::AreEqual(0, engine.engine->ExitCode());
			engine.engine.reset();
			engine = PonyEngine::Core::CreateEngine(params);
			engine.engine->Stop(100);
			Assert::AreEqual(100, engine.engine->ExitCode());
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = EmptyLogger();
			auto params = PonyEngine::Core::EngineParams{ .logger = &logger };
			auto engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual("PonyEngine::Core::Engine", engine.engine->Name());
		}

		TEST_METHOD(SystemTickTest)
		{
			auto logger = EmptyLogger();
			EmptySystemFactory systemFactory;
			auto params = PonyEngine::Core::EngineParams{.logger = &logger};
			params.systemFactories.AddSystemFactory(systemFactory);
			auto engine = PonyEngine::Core::CreateEngine(params);

			Assert::IsTrue(systemFactory.createdSystem->begun);

			Assert::IsFalse(systemFactory.createdSystem->ticked);

			engine.tickableEngine->Tick();
			Assert::IsTrue(systemFactory.createdSystem->ticked);

			systemFactory.createdSystem->ticked = false;
			engine.tickableEngine->Tick();
			Assert::IsTrue(systemFactory.createdSystem->ticked);

			bool ended = false;
			systemFactory.createdSystem->ended = &ended;
			engine.engine.reset();
			Assert::IsTrue(ended);
			Assert::IsTrue(systemFactory.systemDestroyed);
		}

		TEST_METHOD(FindSystemTest)
		{
			auto logger = EmptyLogger();
			auto systemFactory = EmptySystemFactory();
			auto system1Factory = EmptySystem1Factory();
			auto params = PonyEngine::Core::EngineParams{.logger = &logger};
			params.systemFactories.AddSystemFactory(systemFactory);
			params.systemFactories.AddSystemFactory(system1Factory);
			const auto engine = PonyEngine::Core::CreateEngine(params);

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem(typeid(EmptySystem))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem<EmptySystem>()));

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<EmptySystem1Base*>(system1Factory.createdSystem)), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem(typeid(EmptySystem1Base))));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<EmptySystem1Base*>(system1Factory.createdSystem)), reinterpret_cast<std::uintptr_t>(engine.engine->SystemManager().FindSystem<EmptySystem1Base>()));

			Assert::IsNull(engine.engine->SystemManager().FindSystem(typeid(EmptySystem1)));
			Assert::IsNull(engine.engine->SystemManager().FindSystem<EmptySystem1>());

			Assert::IsNull(engine.engine->SystemManager().FindSystem(typeid(PonyEngine::Core::ISystem)));
			Assert::IsNull(engine.engine->SystemManager().FindSystem<PonyEngine::Core::ISystem>());
		}
	};
} 
