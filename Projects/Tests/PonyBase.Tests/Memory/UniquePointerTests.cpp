/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <utility>

#include "Mocks/Base.h"
#include "Mocks/Derived.h"
#include "Mocks/DerivedWithParams.h"

import PonyBase.Memory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Memory
{
	TEST_CLASS(UniquePointerTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			const auto defaultPointer = PonyBase::Memory::UniquePointer<Derived>();
			Assert::IsNull(defaultPointer.Get());

			auto pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			Derived* object = pointer.Get();
			auto movedPointer = std::move(pointer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(object), reinterpret_cast<std::uintptr_t>(movedPointer.Get()));
			Assert::IsNull(pointer.Get());

			const auto basePointer = PonyBase::Memory::UniquePointer<Base>(std::move(movedPointer));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(object), reinterpret_cast<std::uintptr_t>(basePointer.Get()));
			Assert::IsNull(movedPointer.Get());
		}

		TEST_METHOD(DestructorTest)
		{
			auto pointerOnStack = PonyBase::Memory::UniquePointer<Derived>::Create();
			bool destructedDerived = false;
			bool destructedBase = false;
			pointerOnStack->SetOnDerivedDestructed(&destructedDerived);
			pointerOnStack->SetOnBaseDestructed(&destructedBase);
			const auto pointer = new PonyBase::Memory::UniquePointer<Base>(std::move(pointerOnStack));
			delete pointer;
			Assert::IsTrue(destructedDerived);
			Assert::IsTrue(destructedBase);
		}

		TEST_METHOD(CreateTest)
		{
			const auto pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			Assert::IsNotNull(pointer.Get());

			const auto paramPointer = PonyBase::Memory::UniquePointer<DerivedWithParams>::Create(3, true);
			Assert::AreEqual(3, paramPointer->GetIParam());
			Assert::AreEqual(true, paramPointer->GetBParam());
		}

		TEST_METHOD(GetTest)
		{
			auto pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			Assert::IsNotNull(pointer.Get());

			pointer.Reset();
			Assert::IsNull(pointer.Get());
		}

		TEST_METHOD(ResetTest)
		{
			auto pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			bool destructedDerived = false;
			bool destructedBase = false;
			pointer->SetOnDerivedDestructed(&destructedDerived);
			pointer->SetOnBaseDestructed(&destructedBase);
			auto basePointer = PonyBase::Memory::UniquePointer<Base>(std::move(pointer));
			basePointer.Reset();
			Assert::IsTrue(destructedDerived);
			Assert::IsTrue(destructedBase);
		}

		TEST_METHOD(BoolOperatorTest)
		{
			auto pointer = PonyBase::Memory::UniquePointer<Derived>();
			Assert::IsFalse(static_cast<bool>(pointer));

			pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			Assert::IsTrue(static_cast<bool>(pointer));
		}

		TEST_METHOD(AccessOperatorTest)
		{
			auto pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(pointer.Get()), reinterpret_cast<std::uintptr_t>(&*pointer));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(pointer.Get()), reinterpret_cast<std::uintptr_t>(pointer.operator->()));
		}

		TEST_METHOD(AssignmentOperatorTest)
		{
			auto pointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			Derived* const object = pointer.Get();

			auto movedPointer = PonyBase::Memory::UniquePointer<Derived>::Create();
			bool destructedDerived = false;
			bool destructedBase = false;
			movedPointer->SetOnDerivedDestructed(&destructedDerived);
			movedPointer->SetOnBaseDestructed(&destructedBase);
			movedPointer = std::move(pointer);
			Assert::IsTrue(destructedDerived);
			Assert::IsTrue(destructedBase);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(object), reinterpret_cast<std::uintptr_t>(movedPointer.Get()));

			auto basePointer = PonyBase::Memory::UniquePointer<Base>::Create();
			destructedBase = false;
			basePointer->SetOnBaseDestructed(&destructedBase);
			basePointer = std::move(movedPointer);
			Assert::IsTrue(destructedBase);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(object), reinterpret_cast<std::uintptr_t>(basePointer.Get()));
		}
	};
}
