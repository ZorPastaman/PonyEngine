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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(ObjectInterfacesTests)
	{
		class IInterface
		{
		};

		class Class : public IInterface
		{
		};

		class IInterface1
		{
		};

		class Class1 : public IInterface1
		{
		};

		TEST_METHOD(ConstructorsTest)
		{
			auto classObject = Class();
			auto defaultInterfaces = PonyEngine::Core::ObjectInterfaces();
			defaultInterfaces.AddInterfacesDeduced<IInterface>(classObject);
			Assert::IsTrue(typeid(IInterface) == defaultInterfaces.Begin()->first.get());

			const auto copiedInterfaces = defaultInterfaces;
			Assert::IsTrue(typeid(IInterface) == copiedInterfaces.Begin()->first.get());

			const auto movedInterfaces = std::move(defaultInterfaces);
			Assert::IsTrue(typeid(IInterface) == movedInterfaces.Begin()->first.get());
		}

		TEST_METHOD(AddInterfacesViaPointerTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterface(typeid(IInterface), static_cast<IInterface*>(&classObject));
			interfaces.AddInterface(typeid(IInterface1), static_cast<IInterface1*>(&class1Object));
			interfaces.AddInterface(typeid(Class1), &class1Object);

			auto it = interfaces.begin();
			Assert::IsTrue(typeid(IInterface) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(IInterface1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(Class1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(it == interfaces.end());
		}

		TEST_METHOD(AddInterfaceTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterface<IInterface, Class>(classObject);
			interfaces.AddInterface<IInterface1, Class1>(class1Object);
			interfaces.AddInterface<Class1, Class1>(class1Object);

			auto it = interfaces.Begin();
			Assert::IsTrue(typeid(IInterface) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(IInterface1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(Class1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(it == interfaces.End());
		}

		TEST_METHOD(AddInterfacesTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterfaces<Class, IInterface>(classObject);
			interfaces.AddInterfaces<Class1, IInterface1, Class1>(class1Object);

			auto it = interfaces.Begin();
			Assert::IsTrue(typeid(IInterface) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(IInterface1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(Class1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(it == interfaces.End());
		}

		TEST_METHOD(AddInterfacesDeducedTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddInterfacesDeduced<IInterface>(classObject);
			interfaces.AddInterfacesDeduced<IInterface1, Class1>(class1Object);

			auto it = interfaces.Begin();
			Assert::IsTrue(typeid(IInterface) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(IInterface1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(typeid(Class1) == it->first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(it->second));

			++it;
			Assert::IsTrue(it == interfaces.End());
		}

		TEST_METHOD(AssignmentTest)
		{
			auto classObject = Class();
			auto defaultInterfaces = PonyEngine::Core::ObjectInterfaces();
			defaultInterfaces.AddInterfacesDeduced<IInterface>(classObject);
			Assert::IsTrue(typeid(IInterface) == defaultInterfaces.Begin()->first.get());

			auto copiedInterfaces = PonyEngine::Core::ObjectInterfaces();
			copiedInterfaces = defaultInterfaces;
			Assert::IsTrue(typeid(IInterface) == copiedInterfaces.Begin()->first.get());

			auto movedInterfaces = PonyEngine::Core::ObjectInterfaces();
			movedInterfaces = std::move(defaultInterfaces);
			Assert::IsTrue(typeid(IInterface) == movedInterfaces.Begin()->first.get());
		}
	};
}
