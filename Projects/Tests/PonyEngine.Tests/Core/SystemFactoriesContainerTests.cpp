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
	TEST_CLASS(SystemFactoriesContainerTests)
	{
		class EmptyFactory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::SystemData Create(const PonyEngine::Core::SystemParams& params) override
			{
				return PonyEngine::Core::SystemData{.system = PonyEngine::Core::SystemUniquePtr(nullptr, PonyEngine::Core::SystemDeleter(*this))};
			}

			virtual void Destroy(PonyEngine::Core::ISystem*) noexcept override
			{
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

		TEST_METHOD(ConstructorTest)
		{
			auto factory = EmptyFactory();
			auto defaultContainer = PonyEngine::Core::SystemFactoriesContainer();
			defaultContainer.AddSystemFactory(factory);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(*defaultContainer.Begin()));

			const auto copiedContainer = defaultContainer;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(*copiedContainer.Begin()));

			const auto movedContainer = std::move(defaultContainer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(*movedContainer.Begin()));
		}

		TEST_METHOD(AddFactoryTest)
		{
			auto factory = EmptyFactory();
			auto anotherFactory = EmptyFactory();
			auto container = PonyEngine::Core::SystemFactoriesContainer();
			container.AddSystemFactory(factory);
			container.AddSystemFactory(anotherFactory);

			auto it = container.begin();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(*it));

			++it;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&anotherFactory), reinterpret_cast<std::uintptr_t>(*it));

			++it;
			Assert::IsTrue(it == container.end());
		}

		TEST_METHOD(AssignmentTest)
		{
			auto factory = EmptyFactory();
			auto defaultContainer = PonyEngine::Core::SystemFactoriesContainer();
			defaultContainer.AddSystemFactory(factory);

			auto copiedContainer = PonyEngine::Core::SystemFactoriesContainer();
			copiedContainer = defaultContainer;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(*copiedContainer.begin()));

			auto movedContainer = PonyEngine::Core::SystemFactoriesContainer();
			movedContainer = std::move(defaultContainer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(*movedContainer.begin()));
		}
	};
}
