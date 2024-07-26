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
			interfaces.AddObjectInterface<IInterface>(system);

			auto copiedInterfaces = interfaces;
			auto copiedIterator = copiedInterfaces.GetObjectInterfaces();
			auto interface = *copiedIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(copiedIterator.IsEnd());
			Assert::IsTrue((++copiedIterator).IsEnd());

			auto movedInterfaces = std::move(interfaces);
			auto movedIterator = movedInterfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterface(typeid(IInterface), static_cast<IInterface*>(&system));
			interfaces.AddObjectInterface(typeid(IBaseInterface), static_cast<IBaseInterface*>(&system));
			auto it = interfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterface<IInterface>(system);
			interfaces.AddObjectInterface<IBaseInterface>(system);
			it = interfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterfaces<EmptySystem, IInterface, IBaseInterface>(system);
			it = interfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterfacesDeduced<IInterface, IBaseInterface>(system);
			it = interfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterface<IInterface>(system);

			auto otherInterfaces = PonyEngine::Core::ObjectInterfaces();
			otherInterfaces = interfaces;
			auto otherIterator = otherInterfaces.GetObjectInterfaces();
			auto interface = *otherIterator;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&system)), reinterpret_cast<std::uintptr_t>(interface.second));
			Assert::IsFalse(otherIterator.IsEnd());
			Assert::IsTrue((++otherIterator).IsEnd());

			auto anotherInterfaces = PonyEngine::Core::ObjectInterfaces();
			anotherInterfaces = std::move(interfaces);
			auto anotherIterator = anotherInterfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterface<IInterface>(system);
			auto iterator = interfaces.GetObjectInterfaces();

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
			interfaces.AddObjectInterfacesDeduced<IInterface, IBaseInterface>(system);

			auto iterator = interfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterfacesDeduced<IInterface, IBaseInterface>(system);
			auto iterator = interfaces.GetObjectInterfaces();

			auto otherInterfaces = PonyEngine::Core::ObjectInterfaces();
			auto copiedIterator = otherInterfaces.GetObjectInterfaces();
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

			auto movedIterator = otherInterfaces.GetObjectInterfaces();
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
			interfaces.AddObjectInterfacesDeduced<IInterface, IBaseInterface>(system);
			auto iterator = interfaces.GetObjectInterfaces();

			auto copiedIterator = iterator;
			Assert::IsTrue(iterator == copiedIterator);
			Assert::IsFalse(iterator != copiedIterator);

			++iterator;
			Assert::IsFalse(iterator == copiedIterator);
			Assert::IsTrue(iterator != copiedIterator);
		}
	};
}
