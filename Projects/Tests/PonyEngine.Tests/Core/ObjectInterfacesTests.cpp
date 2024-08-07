/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstdint>;

import PonyEngine.Core.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(ObjectInterfacesTests)
	{
		class IBaseInterface
		{
		};

		class EmptySystemBase : public PonyEngine::Core::ISystem, public IBaseInterface
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

			virtual void Tick() override
			{
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ObjectInterfaces PublicInterfaces() noexcept override
			{
				return PonyEngine::Core::ObjectInterfaces();
			}

			[[nodiscard("Pure function")]]
			virtual bool IsTickable() const noexcept override
			{
				return false;
			}
		};

		class IInterface
		{
		};

		class EmptySystem final : public EmptySystemBase, public IInterface
		{
		};

		TEST_METHOD(ConstructorTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterface<IInterface>(system);

			auto copiedInterfaces = interfaces;
			auto copiedIterator = copiedInterfaces.Interfaces();
			auto interface = *copiedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(copiedIterator.IsEnd());
			Assert::IsTrue((++copiedIterator).IsEnd());

			auto movedInterfaces = std::move(interfaces);
			auto movedIterator = movedInterfaces.Interfaces();
			interface = *movedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(movedIterator.IsEnd());
			Assert::IsTrue((++movedIterator).IsEnd());
		}

		TEST_METHOD(GetAddObjectInterfacesTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterface(typeid(IInterface), static_cast<IInterface*>(&system));
			interfaces.AddInterface(typeid(IBaseInterface), static_cast<IBaseInterface*>(&system));
			auto it = interfaces.Interfaces();
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IBaseInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsTrue(it.IsEnd());

			interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterface<IInterface>(system);
			interfaces.AddInterface<IBaseInterface>(system);
			it = interfaces.Interfaces();
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IBaseInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsTrue(it.IsEnd());

			interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterfaces<EmptySystem, IInterface, IBaseInterface>(system);
			it = interfaces.Interfaces();
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IBaseInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsTrue(it.IsEnd());

			interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterfacesDeduced<IInterface, IBaseInterface>(system);
			it = interfaces.Interfaces();
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue(typeid(IBaseInterface) == (*it).first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>((*it).second));
			++it;
			Assert::IsTrue(it.IsEnd());
		}

		TEST_METHOD(AssignmentTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterface<IInterface>(system);

			auto otherInterfaces = PonyEngine::Core::ObjectInterfaces();
			otherInterfaces = interfaces;
			auto otherIterator = otherInterfaces.Interfaces();
			auto interface = *otherIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(otherIterator.IsEnd());
			Assert::IsTrue((++otherIterator).IsEnd());

			auto anotherInterfaces = PonyEngine::Core::ObjectInterfaces();
			anotherInterfaces = std::move(interfaces);
			auto anotherIterator = anotherInterfaces.Interfaces();
			interface = *anotherIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(anotherIterator.IsEnd());
			Assert::IsTrue((++anotherIterator).IsEnd());
		}

		TEST_METHOD(IteratorConstructorTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterface<IInterface>(system);
			auto iterator = interfaces.Interfaces();

			auto copiedIterator = iterator;
			auto interface = *copiedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(copiedIterator.IsEnd());
			Assert::IsTrue((++copiedIterator).IsEnd());

			auto movedIterator = std::move(iterator);
			interface = *movedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(movedIterator.IsEnd());
			Assert::IsTrue((++movedIterator).IsEnd());
		}

		TEST_METHOD(IterateTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterfacesDeduced<IInterface, IBaseInterface>(system);

			auto iterator = interfaces.Interfaces();
			auto interface = *iterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(iterator.IsEnd());

			auto anotherIterator = ++iterator;
			interface = *iterator;
			Assert::IsTrue(typeid(IBaseInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(iterator.IsEnd());
			interface = *anotherIterator;
			Assert::IsTrue(typeid(IBaseInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(anotherIterator.IsEnd());

			anotherIterator = iterator++;
			Assert::IsTrue(iterator.IsEnd());
			interface = *anotherIterator;
			Assert::IsTrue(typeid(IBaseInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(anotherIterator.IsEnd());
		}

		TEST_METHOD(IteratorAssignmentsTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterfacesDeduced<IInterface, IBaseInterface>(system);
			auto iterator = interfaces.Interfaces();

			auto otherInterfaces = PonyEngine::Core::ObjectInterfaces();
			auto copiedIterator = otherInterfaces.Interfaces();
			copiedIterator = iterator;
			auto interface = *copiedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++copiedIterator;
			interface = *copiedIterator;
			Assert::IsTrue(typeid(IBaseInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++copiedIterator;
			Assert::IsTrue(copiedIterator.IsEnd());

			auto movedIterator = otherInterfaces.Interfaces();
			movedIterator = std::move(iterator);
			interface = *movedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++movedIterator;
			interface = *movedIterator;
			Assert::IsTrue(typeid(IBaseInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IBaseInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++movedIterator;
			Assert::IsTrue(movedIterator.IsEnd());
		}

		TEST_METHOD(IteratorEqualTest)
		{
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			auto system = EmptySystem();
			interfaces.AddInterfacesDeduced<IInterface, IBaseInterface>(system);
			auto iterator = interfaces.Interfaces();

			auto copiedIterator = iterator;
			Assert::IsTrue(iterator == copiedIterator);
			Assert::IsFalse(iterator != copiedIterator);

			++iterator;
			Assert::IsFalse(iterator == copiedIterator);
			Assert::IsTrue(iterator != copiedIterator);
		}
	};
}
