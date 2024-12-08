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

#include "Mocks/Application.h"
#include "Mocks/InputDeviceFactory.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"

import PonyEngine.Input.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputSystemTests)
	{
		TEST_METHOD(BoolBindTest)
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
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::H}
			};
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams{}, params);
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			std::get<1>(system.system)->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(std::get<1>(system.system).get());
			Assert::AreEqual(std::size_t{1}, deviceFactory->version);

			std::size_t tVal = 0;
			std::size_t fVal = 0;
			auto handle = inputSystem->Bind("Mock", std::function<void(bool)>([&](const bool input) { tVal += input; fVal += !input; }));
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{1}, tVal);
			Assert::AreEqual(std::size_t{0}, fVal);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = 0.1f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{1}, tVal);
			Assert::AreEqual(std::size_t{1}, fVal);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = -0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, tVal);
			Assert::AreEqual(std::size_t{1}, fVal);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = -0.1f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, tVal);
			Assert::AreEqual(std::size_t{2}, fVal);

			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, tVal);
			Assert::AreEqual(std::size_t{2}, fVal);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::A, .value = -0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, tVal);
			Assert::AreEqual(std::size_t{2}, fVal);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::A, .value = -0.1f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, tVal);
			Assert::AreEqual(std::size_t{2}, fVal);

			const auto weakHandle = std::weak_ptr(handle);
			handle.reset();
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, tVal);
			Assert::AreEqual(std::size_t{2}, fVal);
			Assert::IsTrue(weakHandle.expired());

			std::get<1>(system.system)->End();
		}

		TEST_METHOD(BoolBindMagnitudeTest)
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
				PonyEngine::Input::InputBindingValue{.inputCode = PonyEngine::Input::InputCode::H}
			};
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams{}, params);
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			std::get<1>(system.system)->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(std::get<1>(system.system).get());

			std::size_t tVal = 0;
			std::size_t fVal = 0;
			auto handle = inputSystem->Bind("Mock", std::function<void(bool)>([&](const bool input) { tVal += input; fVal += !input; }), 1.f);
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{0}, tVal);
			Assert::AreEqual(std::size_t{1}, fVal);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{ .inputCode = PonyEngine::Input::InputCode::H, .value = 1.3f });
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{1}, tVal);
			Assert::AreEqual(std::size_t{1}, fVal);

			std::get<1>(system.system)->End();
		}

		TEST_METHOD(FloatBindTest)
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
			auto handle = inputSystem->Bind("Mock", std::function<void(float)>([&](const float input) { ++version; value = input; }));
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{1}, version);
			Assert::AreEqual(0.3f, value);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = -0.1f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, version);
			Assert::AreEqual(-0.1f, value);

			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::A, .value = -0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, version);

			const auto weakHandle = std::weak_ptr(handle);
			handle.reset();
			deviceFactory->inputDevice->AddInput(PonyEngine::Input::InputEvent{.inputCode = PonyEngine::Input::InputCode::H, .value = 0.3f});
			std::get<1>(system.system)->Tick();
			Assert::AreEqual(std::size_t{2}, version);
			Assert::IsTrue(weakHandle.expired());

			std::get<1>(system.system)->End();
		}
	};
}
