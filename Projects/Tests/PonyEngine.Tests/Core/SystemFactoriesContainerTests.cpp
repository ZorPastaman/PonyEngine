/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "Mocks/SystemFactory.h"

import PonyEngine.Core.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(SystemFactoriesContainerTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			auto factory = SystemFactory();
			auto defaultContainer = PonyEngine::Core::SystemFactoriesContainer();
			defaultContainer.AddSystemFactory(factory);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(defaultContainer.Begin()->first));

			const auto copiedContainer = defaultContainer;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(copiedContainer.Begin()->first));

			const auto movedContainer = std::move(defaultContainer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(movedContainer.Begin()->first));
		}

		TEST_METHOD(AddFactoryTest)
		{
			auto factory = SystemFactory();
			auto anotherFactory = SystemFactory();
			auto container = PonyEngine::Core::SystemFactoriesContainer();
			container.AddSystemFactory(factory, 2);
			container.AddSystemFactory(anotherFactory, 1);

			auto it = container.begin();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(it->first));
			Assert::AreEqual(2, it->second);

			++it;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&anotherFactory), reinterpret_cast<std::uintptr_t>(it->first));
			Assert::AreEqual(1, it->second);

			++it;
			Assert::IsTrue(it == container.end());
		}

		TEST_METHOD(AssignmentTest)
		{
			auto factory = SystemFactory();
			auto defaultContainer = PonyEngine::Core::SystemFactoriesContainer();
			defaultContainer.AddSystemFactory(factory);

			auto copiedContainer = PonyEngine::Core::SystemFactoriesContainer();
			copiedContainer = defaultContainer;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(copiedContainer.begin()->first));

			auto movedContainer = PonyEngine::Core::SystemFactoriesContainer();
			movedContainer = std::move(defaultContainer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&factory), reinterpret_cast<std::uintptr_t>(movedContainer.begin()->first));
		}
	};
}
