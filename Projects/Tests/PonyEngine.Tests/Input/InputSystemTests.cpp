/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstddef>;
import <functional>;

import PonyEngine.Core.Factory;
import PonyEngine.Input.Implementation;
import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputSystemTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Log(PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override
			{
			}
			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}
		};

		class EmptySystemManager : public PonyEngine::Core::ISystemManager
		{
		public:
			PonyEngine::Input::IKeyboardProvider* keyboardProvider = nullptr;

			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override
			{
				if (typeInfo == typeid(PonyEngine::Input::IKeyboardProvider))
				{
					return keyboardProvider;
				}

				return nullptr;
			}
		};

		class EmptyEngine : public PonyEngine::Core::IEngine, public PonyEngine::Core::ITickableEngine
		{
		public:
			EmptyLogger* logger;
			mutable EmptySystemManager systemManager;

			explicit EmptyEngine(EmptyLogger& logger) noexcept :
				logger{&logger}
			{
			}

			[[nodiscard("Pure function")]]
			virtual std::size_t FrameCount() const noexcept override
			{
				return 0;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& Logger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystemManager& SystemManager() const noexcept override
			{
				return systemManager;
			}

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override
			{
				return true;
			}

			[[nodiscard("Pure function")]]
			virtual int ExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Tick() override
			{
			}
		};

		class KeyboardProvider final : public PonyEngine::Input::IKeyboardProvider
		{
		public:
			PonyEngine::Input::IKeyboardObserver* expectedObserver;

			virtual void AddKeyboardObserver(PonyEngine::Input::IKeyboardObserver* keyboardObserver) override
			{
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedObserver), reinterpret_cast<std::uintptr_t>(keyboardObserver));
			}

			virtual void RemoveKeyboardObserver(PonyEngine::Input::IKeyboardObserver* keyboardObserver) override
			{
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedObserver), reinterpret_cast<std::uintptr_t>(keyboardObserver));
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(BeginEndTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto keyboardProvider = KeyboardProvider();
			engine.systemManager.keyboardProvider = &keyboardProvider;
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			const auto systemParams = PonyEngine::Core::SystemParams{.engine = &engine};
			auto inputSystemBase = factory->Create(systemParams);
			keyboardProvider.expectedObserver = dynamic_cast<PonyEngine::Input::IKeyboardObserver*>(inputSystemBase.system.get());
			inputSystemBase.system->Begin();
			inputSystemBase.system->End();

			engine.systemManager.keyboardProvider = nullptr;
			inputSystemBase = factory->Create(systemParams);
			inputSystemBase.system->Begin();
			inputSystemBase.system->End();
		}

		TEST_METHOD(TickTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			const auto systemParams = PonyEngine::Core::SystemParams{.engine = &engine};
			auto inputSystemBase = factory->Create(systemParams);
			bool gotInput = false;
			std::function<void()> func = [&]{ gotInput = true; };
			inputSystemBase.system->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(inputSystemBase.system.get());
			auto message = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true};
			auto event = PonyEngine::Input::Event{.expectedMessage = message};
			auto handle = inputSystem->RegisterAction(event, func);
			auto inputObserver = dynamic_cast<PonyEngine::Input::IKeyboardObserver*>(inputSystem);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true});
			inputSystemBase.tickableSystem->Tick();
			Assert::IsTrue(gotInput);
			gotInput = false;
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = false});
			inputSystemBase.tickableSystem->Tick();
			Assert::IsFalse(gotInput);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::W, .isDown = true});
			inputSystemBase.tickableSystem->Tick();
			Assert::IsFalse(gotInput);
			inputSystem->UnregisterAction(handle);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true});
			inputSystemBase.tickableSystem->Tick();
			Assert::IsFalse(gotInput);
			inputSystemBase.system->End();
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			const auto systemParams = PonyEngine::Core::SystemParams{.engine = &engine};
			auto inputSystemBase = factory->Create(systemParams);
			Assert::AreEqual("PonyEngine::Input::InputSystem", inputSystemBase.system->Name());
		}
	};
}
