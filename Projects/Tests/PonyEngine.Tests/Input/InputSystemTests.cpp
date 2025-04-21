/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <functional>
#include <memory>
#include <variant>
#include <vector>

import Mocks;

import PonyEngine.Input.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputSystemTests)
	{
		TEST_METHOD(CreateReceiverTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			const auto deviceFactory = std::make_shared<Mocks::InputDeviceFactory>();
			auto params = PonyEngine::Input::InputSystemParams{};
			params.inputDeviceFactories.push_back(deviceFactory);
			params.inputBindings["Mock"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{ .inputCode = PonyEngine::Input::InputCode::H }
			};
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams{}, params);
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			std::get<1>(system.system)->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(std::get<1>(system.system).get());
			Assert::AreEqual(std::size_t{1}, deviceFactory->version);

			std::size_t version = 0;
			float value = 0;
			auto receiver = inputSystem->CreateReceiver("Mock");
			receiver->Action(std::function<void(float)>([&](const float input) { ++version; value = input; }));
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{1}, version);
			Assert::AreEqual(0.3f, value);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = -0.1f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, version);
			Assert::AreEqual(-0.1f, value);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::A, .inputValue = -0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, version);

			const auto weakHandle = std::weak_ptr(receiver);
			receiver.reset();
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, version);
			Assert::IsTrue(weakHandle.expired());

			std::get<1>(system.system)->End();
		}

		TEST_METHOD(GetStateTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			const auto deviceFactory = std::make_shared<Mocks::InputDeviceFactory>();
			auto params = PonyEngine::Input::InputSystemParams{};
			params.inputDeviceFactories.push_back(deviceFactory);
			params.inputBindings["Mock"] = std::vector<PonyEngine::Input::InputBindingValue>
			{
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::H }
			};
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams{}, params);
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			std::get<1>(system.system)->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(std::get<1>(system.system).get());
			Assert::AreEqual(std::size_t{1}, deviceFactory->version);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(0.3f, inputSystem->State("Mock"));

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.5f, .inputType = PonyEngine::Input::InputType::Delta});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(0.8, static_cast<double>(inputSystem->State("Mock")), 0.001);

			std::get<1>(system.system)->Tick();
			Assert::AreEqual(0.3f, inputSystem->State("Mock"));

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.f});
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.6f, .inputType = PonyEngine::Input::InputType::Delta});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(0.6f, inputSystem->State("Mock"));

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{ .inputCode = PonyEngine::Input::InputCode::H, .inputValue = 0.6f, .inputType = PonyEngine::Input::InputType::Delta });
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{ .inputCode = PonyEngine::Input::InputCode::H, .inputValue = -0.3f, .inputType = PonyEngine::Input::InputType::Delta });
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(0.3, static_cast<double>(inputSystem->State("Mock")), 0.001);

			std::get<1>(system.system)->End();
		}
	};
}
