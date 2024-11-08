/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string_view>
#include <variant>
#include <vector>

#include "Mocks/Engine.h"
#include "Mocks/Logger.h"

import PonyDebug.Log;

import PonyEngine.Core.Factory;
import PonyEngine.Input.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputSystemTests)
	{
		class KeyboardProvider final : public PonyEngine::Input::IKeyboardProvider
		{
		public:
			std::vector<PonyEngine::Input::IKeyboardObserver*> observers;
			std::size_t version;

			virtual void AddKeyboardObserver(PonyEngine::Input::IKeyboardObserver& keyboardObserver) override
			{
				observers.push_back(&keyboardObserver);
				++version;
			}

			virtual void RemoveKeyboardObserver(PonyEngine::Input::IKeyboardObserver& keyboardObserver) override
			{
				if (const auto position = std::ranges::find(observers, &keyboardObserver); position != observers.cend())
				{
					observers.erase(position);
					++version;
				}
			}

			[[nodiscard("Pure function")]]
			virtual std::string_view Name() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(BeginEndTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto keyboardProvider = KeyboardProvider();
			
			static_cast<Core::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Input::IKeyboardProvider), static_cast<PonyEngine::Input::IKeyboardProvider*>(&keyboardProvider));
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			constexpr auto systemParams = PonyEngine::Core::EngineSystemParams();
			auto inputSystem = factory.systemFactory->Create(engine, systemParams);
			Assert::AreEqual(std::size_t{0}, keyboardProvider.version);
			std::get<1>(inputSystem.system)->Begin();
			Assert::AreEqual(std::size_t{1}, keyboardProvider.version);
			Assert::AreEqual(std::size_t{1}, keyboardProvider.observers.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IKeyboardObserver*>(std::get<1>(inputSystem.system).Get())), reinterpret_cast<std::uintptr_t>(keyboardProvider.observers[0]));
			std::get<1>(inputSystem.system)->End();
			Assert::AreEqual(std::size_t{2}, keyboardProvider.version);
			Assert::AreEqual(std::size_t{0}, keyboardProvider.observers.size());
		}

		TEST_METHOD(TickTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			auto inputSystemBase = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			bool gotInput = false;
			std::function<void()> func = [&]{ gotInput = true; };
			std::get<1>(inputSystemBase.system)->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(std::get<1>(inputSystemBase.system).Get());
			auto message = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true};
			auto event = PonyEngine::Input::Event{.expectedMessage = message};
			auto handle = inputSystem->RegisterAction(event, func);
			auto inputObserver = dynamic_cast<PonyEngine::Input::IKeyboardObserver*>(inputSystem);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true});
			std::get<1>(inputSystemBase.system)->Tick();
			Assert::IsTrue(gotInput);
			gotInput = false;
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = false});
			std::get<1>(inputSystemBase.system)->Tick();
			Assert::IsFalse(gotInput);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::W, .isDown = true});
			std::get<1>(inputSystemBase.system)->Tick();
			Assert::IsFalse(gotInput);
			inputSystem->UnregisterAction(handle);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true});
			std::get<1>(inputSystemBase.system)->Tick();
			Assert::IsFalse(gotInput);
			std::get<1>(inputSystemBase.system)->End();
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			auto factory = PonyEngine::Input::CreateInputSystemFactory(application, PonyEngine::Input::InputSystemFactoryParams(), PonyEngine::Input::InputSystemParams{});
			auto inputSystemBase = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams());
			Assert::AreEqual(std::string_view("PonyEngine::Input::InputSystem"), std::get<1>(inputSystemBase.system)->Name());
		}
	};
}
