/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <exception>;

import PonyEngine.Core;
import PonyEngine.Core.Factory;
import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineParamsTests)
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

		class EmptySystemFactory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			PonyEngine::Core::ISystem* createdSystem = nullptr;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::SystemInfo Create(PonyEngine::Core::IEngine&) override
			{
				const auto emptySystem = new EmptySystem();
				createdSystem = emptySystem;

				return PonyEngine::Core::SystemInfo::Create<EmptySystem>(*emptySystem, *this, true);
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

		TEST_METHOD(ContructorTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Log::ILogger*>(&logger)), reinterpret_cast<std::uintptr_t>(&engineParams.GetLogger()));

			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);
			const auto copiedParams = engineParams;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Log::ILogger*>(&logger)), reinterpret_cast<std::uintptr_t>(&copiedParams.GetLogger()));
			auto factories = copiedParams.GetSystemFactories();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*factories));
			++factories;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*factories));

			const auto movedParams = std::move(engineParams);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Log::ILogger*>(&logger)), reinterpret_cast<std::uintptr_t>(&movedParams.GetLogger()));
			factories = movedParams.GetSystemFactories();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*factories));
			++factories;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*factories));
		}

		TEST_METHOD(GetSystemFactoriesTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			EmptySystemFactory factory2;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);
			engineParams.AddSystemFactory(factory2);

			PonyEngine::Core::EngineParams::SystemFactoriesIterator it = engineParams.GetSystemFactories();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemFactory*>(&factory0)), reinterpret_cast<std::uintptr_t>(&*it));
			Assert::IsFalse(it.IsEnd());
			PonyEngine::Core::EngineParams::SystemFactoriesIterator incrementedIt = ++it;
			Assert::IsTrue(incrementedIt == it);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemFactory*>(&factory1)), reinterpret_cast<std::uintptr_t>(&*it));
			Assert::IsFalse(it.IsEnd());
			PonyEngine::Core::EngineParams::SystemFactoriesIterator postIncrementedIt = it++;
			Assert::IsTrue(incrementedIt == postIncrementedIt);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemFactory*>(&factory2)), reinterpret_cast<std::uintptr_t>(&*it));
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue((++it).IsEnd());
		}

		TEST_METHOD(AssignmentTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);

			EmptyLogger otherLogger;
			auto otherParams = PonyEngine::Core::EngineParams(otherLogger);
			EmptySystemFactory factory2;
			EmptySystemFactory factory3;
			otherParams.AddSystemFactory(factory2);
			otherParams.AddSystemFactory(factory3);

			auto anotherParams = otherParams;

			otherParams = engineParams;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Log::ILogger*>(&logger)), reinterpret_cast<std::uintptr_t>(&otherParams.GetLogger()));
			auto factories = otherParams.GetSystemFactories();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*factories));
			++factories;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*factories));

			otherParams = std::move(anotherParams);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Log::ILogger*>(&otherLogger)), reinterpret_cast<std::uintptr_t>(&otherParams.GetLogger()));
			factories = otherParams.GetSystemFactories();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory2), reinterpret_cast<std::uintptr_t>(&*factories));
			++factories;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory3), reinterpret_cast<std::uintptr_t>(&*factories));
		}

		TEST_METHOD(IteratorTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			Assert::IsTrue(engineParams.GetSystemFactories().IsEnd());

			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);
			auto factories = engineParams.GetSystemFactories();
			Assert::IsFalse(factories.IsEnd());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*factories));
			auto anotherFactories = ++factories;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*factories));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*anotherFactories));
			anotherFactories = factories++;
			Assert::IsTrue(factories.IsEnd());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*anotherFactories));
		}

		TEST_METHOD(IteratorConstructorTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);
			auto iterator = engineParams.GetSystemFactories();

			auto copiedIterator = iterator;
			Assert::IsFalse(copiedIterator.IsEnd());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*copiedIterator));
			++copiedIterator;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*copiedIterator));
			++copiedIterator;
			Assert::IsTrue(copiedIterator.IsEnd());

			auto movedIterator = std::move(iterator);
			Assert::IsFalse(movedIterator.IsEnd());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*movedIterator));
			++movedIterator;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*movedIterator));
			++movedIterator;
			Assert::IsTrue(movedIterator.IsEnd());
		}

		TEST_METHOD(IteratorAssignmentTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);
			auto iterator = engineParams.GetSystemFactories();

			EmptyLogger otherLogger;
			auto otherParams = PonyEngine::Core::EngineParams(otherLogger);
			EmptySystemFactory factory2;
			EmptySystemFactory factory3;
			otherParams.AddSystemFactory(factory2);
			otherParams.AddSystemFactory(factory3);
			auto otherIterator = otherParams.GetSystemFactories();

			otherIterator = iterator;
			Assert::IsFalse(otherIterator.IsEnd());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*otherIterator));
			++otherIterator;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*otherIterator));
			++otherIterator;
			Assert::IsTrue(otherIterator.IsEnd());

			auto anotherIterator = otherParams.GetSystemFactories();
			anotherIterator = std::move(iterator);
			Assert::IsFalse(anotherIterator.IsEnd());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory0), reinterpret_cast<std::uintptr_t>(&*anotherIterator));
			++anotherIterator;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory1), reinterpret_cast<std::uintptr_t>(&*anotherIterator));
			++anotherIterator;
			Assert::IsTrue(anotherIterator.IsEnd());
		}

		TEST_METHOD(IteratorEqualTest)
		{
			EmptyLogger logger;
			auto engineParams = PonyEngine::Core::EngineParams(logger);
			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			engineParams.AddSystemFactory(factory0);
			engineParams.AddSystemFactory(factory1);

			auto iterator = engineParams.GetSystemFactories();
			auto otherIterator = iterator;
			Assert::IsTrue(iterator == otherIterator);
			Assert::IsFalse(iterator != otherIterator);

			++iterator;
			Assert::IsFalse(iterator == otherIterator);
			Assert::IsTrue(iterator != otherIterator);
		}
	};
}
