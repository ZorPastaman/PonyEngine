/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import Mocks;

import PonyEngine.Input.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(WindowsKeyboardDeviceFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto application = Mocks::Application();
			auto factory = PonyEngine::Input::Windows::CreateKeyboardDeviceFactory(application, PonyEngine::Input::Windows::KeyboardDeviceFactoryParams{}, PonyEngine::Input::Windows::KeyboardDeviceParams{});
			Assert::IsNotNull(factory.inputDeviceFactory.get());
		}

		TEST_METHOD(CreateFactoryTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			auto inputSystem = Mocks::InputSystem();
			inputSystem.engine = &engine;
			auto factory = PonyEngine::Input::Windows::CreateKeyboardDeviceFactory(application, PonyEngine::Input::Windows::KeyboardDeviceFactoryParams{}, PonyEngine::Input::Windows::KeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::DeviceParams{});
			Assert::IsNotNull(device.inputDevice.get());
		}

		TEST_METHOD(DeviceTypeTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			auto inputSystem = Mocks::InputSystem();
			inputSystem.engine = &engine;
			auto factory = PonyEngine::Input::Windows::CreateKeyboardDeviceFactory(application, PonyEngine::Input::Windows::KeyboardDeviceFactoryParams{}, PonyEngine::Input::Windows::KeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::DeviceParams{});
			Assert::IsTrue(typeid(*device.inputDevice) == factory.inputDeviceFactory->DeviceType());
		}
	};
}
