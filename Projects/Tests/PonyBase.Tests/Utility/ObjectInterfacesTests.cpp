/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <typeinfo>

import PonyBase.Utility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
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
			auto defaultInterfaces = PonyBase::Utility::ObjectInterfaces();
			defaultInterfaces.AddInterfacesDeduced<IInterface>(classObject);
			Assert::IsTrue(typeid(IInterface) == defaultInterfaces.Span()[0].first.get());

			const auto copiedInterfaces = defaultInterfaces;
			Assert::IsTrue(typeid(IInterface) == copiedInterfaces.Span()[0].first.get());

			const auto movedInterfaces = std::move(defaultInterfaces);
			Assert::IsTrue(typeid(IInterface) == movedInterfaces.Span()[0].first.get());
		}

		TEST_METHOD(AddInterfacesViaPointerTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyBase::Utility::ObjectInterfaces();
			interfaces.AddInterface(typeid(IInterface), static_cast<IInterface*>(&classObject));
			interfaces.AddInterface(typeid(IInterface1), static_cast<IInterface1*>(&class1Object));
			interfaces.AddInterface(typeid(Class1), &class1Object);

			auto span = interfaces.Span();
			Assert::AreEqual(std::size_t{3}, span.size());

			Assert::IsTrue(typeid(IInterface) == span[0].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(span[0].second));

			Assert::IsTrue(typeid(IInterface1) == span[1].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(span[1].second));

			Assert::IsTrue(typeid(Class1) == span[2].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(span[2].second));
		}

		TEST_METHOD(AddInterfaceTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyBase::Utility::ObjectInterfaces();
			interfaces.AddInterface<IInterface, Class>(classObject);
			interfaces.AddInterface<IInterface1, Class1>(class1Object);
			interfaces.AddInterface<Class1, Class1>(class1Object);

			auto span = interfaces.Span();
			Assert::AreEqual(std::size_t{3}, span.size());

			Assert::IsTrue(typeid(IInterface) == span[0].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(span[0].second));

			Assert::IsTrue(typeid(IInterface1) == span[1].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(span[1].second));

			Assert::IsTrue(typeid(Class1) == span[2].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(span[2].second));
		}

		TEST_METHOD(AddInterfacesTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyBase::Utility::ObjectInterfaces();
			interfaces.AddInterfaces<Class, IInterface>(classObject);
			interfaces.AddInterfaces<Class1, IInterface1, Class1>(class1Object);

			auto span = interfaces.Span();
			Assert::AreEqual(std::size_t{3}, span.size());

			Assert::IsTrue(typeid(IInterface) == span[0].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(span[0].second));

			Assert::IsTrue(typeid(IInterface1) == span[1].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(span[1].second));

			Assert::IsTrue(typeid(Class1) == span[2].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(span[2].second));
		}

		TEST_METHOD(AddInterfacesDeducedTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyBase::Utility::ObjectInterfaces();
			interfaces.AddInterfacesDeduced<IInterface>(classObject);
			interfaces.AddInterfacesDeduced<IInterface1, Class1>(class1Object);

			auto span = interfaces.Span();
			Assert::AreEqual(std::size_t{3}, span.size());

			Assert::IsTrue(typeid(IInterface) == span[0].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(&classObject)), reinterpret_cast<std::uintptr_t>(span[0].second));

			Assert::IsTrue(typeid(IInterface1) == span[1].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface1*>(&class1Object)), reinterpret_cast<std::uintptr_t>(span[1].second));

			Assert::IsTrue(typeid(Class1) == span[2].first.get());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&class1Object), reinterpret_cast<std::uintptr_t>(span[2].second));
		}

		TEST_METHOD(CountTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyBase::Utility::ObjectInterfaces();
			interfaces.AddInterfacesDeduced<IInterface>(classObject);
			interfaces.AddInterfacesDeduced<IInterface1, Class1>(class1Object);

			Assert::AreEqual(std::size_t{3}, interfaces.Count());
		}

		TEST_METHOD(AccessOperatorTest)
		{
			auto classObject = Class();
			auto class1Object = Class1();
			auto interfaces = PonyBase::Utility::ObjectInterfaces();
			interfaces.AddInterfacesDeduced<IInterface>(classObject);
			interfaces.AddInterfacesDeduced<IInterface1, Class1>(class1Object);

			Assert::IsTrue(interfaces.Span()[0].first.get() == interfaces[0].first.get());
			Assert::IsTrue(interfaces.Span()[0].second == interfaces[0].second);
			Assert::IsTrue(interfaces.Span()[1].first.get() == interfaces[1].first.get());
			Assert::IsTrue(interfaces.Span()[1].second == interfaces[1].second);
			Assert::IsTrue(interfaces.Span()[2].first.get() == interfaces[2].first.get());
			Assert::IsTrue(interfaces.Span()[2].second == interfaces[2].second);
		}

		TEST_METHOD(AssignmentTest)
		{
			auto classObject = Class();
			auto defaultInterfaces = PonyBase::Utility::ObjectInterfaces();
			defaultInterfaces.AddInterfacesDeduced<IInterface>(classObject);
			Assert::IsTrue(typeid(IInterface) == defaultInterfaces.Span()[0].first.get());

			auto copiedInterfaces = PonyBase::Utility::ObjectInterfaces();
			copiedInterfaces = defaultInterfaces;
			Assert::IsTrue(typeid(IInterface) == copiedInterfaces.Span()[0].first.get());

			auto movedInterfaces = PonyBase::Utility::ObjectInterfaces();
			movedInterfaces = std::move(defaultInterfaces);
			Assert::IsTrue(typeid(IInterface) == movedInterfaces.Span()[0].first.get());
		}
	};
}
