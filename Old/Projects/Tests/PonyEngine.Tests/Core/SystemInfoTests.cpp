/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <memory>
#include <typeinfo>
#include <variant>

import Mocks;

import PonyEngine.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(SystemInfoTests)
	{
		TEST_METHOD(InfoTest)
		{
			const auto info = PonyEngine::Core::SystemInfo<Mocks::System, Mocks::ISystemInterface>();
			Assert::IsTrue(typeid(Mocks::System) == info.SystemType());
			Assert::IsFalse(info.IsTickable());
			Assert::AreEqual(std::size_t{1}, info.InterfaceCount());

			const auto tickableInfo = PonyEngine::Core::SystemInfo<Mocks::TickableSystem>();
			Assert::IsTrue(typeid(Mocks::TickableSystem) == tickableInfo.SystemType());
			Assert::IsTrue(tickableInfo.IsTickable());
			Assert::AreEqual(std::size_t{0}, tickableInfo.InterfaceCount());
		}

		TEST_METHOD(CreateDataTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;

			const auto info = PonyEngine::Core::SystemInfo<Mocks::System, Mocks::ISystemInterface>();
			const auto data = info.CreateSystemData(std::make_shared<Mocks::System>(engine, PonyEngine::Core::SystemParams{}));
			Assert::AreEqual(std::size_t{0}, data.system.index());
			Assert::IsTrue(typeid(Mocks::System) == typeid(*std::get<0>(data.system)));
			Assert::AreEqual(std::size_t{1}, data.publicInterfaces.Count());
			Assert::IsTrue(typeid(Mocks::ISystemInterface) == data.publicInterfaces[0].first);
		}
	};
}
