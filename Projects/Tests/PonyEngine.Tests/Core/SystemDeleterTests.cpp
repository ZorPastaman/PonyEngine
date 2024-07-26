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
	TEST_CLASS(SystemDeleterTests)
	{
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
			bool deleted = false;

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
				deleted = true;
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

		TEST_METHOD(ConstructorTest)
		{
			auto factory = EmptySystemFactory();
			auto deleter = PonyEngine::Core::SystemDeleter(factory);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&deleter.GetSystemDestroyer()));

			const auto copiedDeleter = deleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&copiedDeleter.GetSystemDestroyer()));

			const auto movedDeleter = std::move(deleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&movedDeleter.GetSystemDestroyer()));
		}

		TEST_METHOD(DeleteTest)
		{
			auto factory = EmptySystemFactory();
			const auto system = new EmptySystem();
			const auto deleter = PonyEngine::Core::SystemDeleter(factory);
			deleter(system);
			Assert::IsTrue(factory.deleted);
		}

		TEST_METHOD(AssignmentTest)
		{
			auto factory = EmptySystemFactory();
			auto deleter = PonyEngine::Core::SystemDeleter(factory);
			auto otherFactory = EmptySystemFactory();
			auto otherDeleter = PonyEngine::Core::SystemDeleter(otherFactory);

			otherDeleter = deleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&otherDeleter.GetSystemDestroyer()));

			otherDeleter = std::move(deleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&otherDeleter.GetSystemDestroyer()));
		}
	};
}
