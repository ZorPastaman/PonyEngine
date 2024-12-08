/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"
#include "Mocks/InputSystem.h"

import PonyEngine.Input.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(WindowsKeyboardDeviceFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto application = Mocks::Application();
			auto factory = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory(application, PonyEngine::Input::WindowsKeyboardDeviceFactoryParams{}, PonyEngine::Input::WindowsKeyboardDeviceParams{});
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
			auto factory = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory(application, PonyEngine::Input::WindowsKeyboardDeviceFactoryParams{}, PonyEngine::Input::WindowsKeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::InputDeviceParams{});
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
			auto factory = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory(application, PonyEngine::Input::WindowsKeyboardDeviceFactoryParams{}, PonyEngine::Input::WindowsKeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::InputDeviceParams{});
			Assert::IsTrue(typeid(*device.inputDevice) == factory.inputDeviceFactory->DeviceType());
		}
	};
}
