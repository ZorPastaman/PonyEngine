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

import PonyEngine.Core;
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
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Log(PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override
			{
			}
			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger*) override
			{
			}
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger*) override
			{
			}
		};

		class EmptyTimeManager : public PonyEngine::Core::ITimeManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::size_t GetFrameCount() const noexcept override
			{
				return 0;
			}

			[[nodiscard("Pure function")]]
			virtual float GetTargetFrameTime() const noexcept override
			{
				return 0.f;
			}

			virtual void SetTargetFrameTime(float) noexcept override
			{
			}
		};

		class EmptySystemManager : public PonyEngine::Core::ISystemManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info&) const noexcept override
			{
				return nullptr;
			}
		};

		class EmptyEngine : public PonyEngine::Core::IAdvancedEngine
		{
			EmptyLogger* logger;
			mutable EmptyTimeManager timeManager;
			mutable EmptySystemManager systemManager;

		public:
			explicit EmptyEngine(EmptyLogger& logger) noexcept :
				logger{ &logger }
			{
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& GetLogger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ITimeManager& GetTimeManager() const noexcept override
			{
				return timeManager;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystemManager& GetSystemManager() const noexcept override
			{
				return systemManager;
			}

			[[nodiscard("Pure function")]]
			virtual bool GetIsRunning() const noexcept override
			{
				return true;
			}

			[[nodiscard("Pure function")]]
			virtual int GetExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Tick() override
			{
			}
		};

		TEST_METHOD(TickTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			auto inputSystemInfo = factory->Create(engine);
			bool gotInput = false;
			std::function<void()> func = [&]() { gotInput = true; };
			auto inputSystemBase = std::move(inputSystemInfo.System());
			inputSystemBase->Begin();
			auto inputSystem = dynamic_cast<PonyEngine::Input::IInputSystem*>(inputSystemBase.get());
			auto message = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true};
			auto event = PonyEngine::Input::Event{.expectedMessage = message};
			auto handle = inputSystem->RegisterAction(event, func);
			auto inputObserver = dynamic_cast<PonyEngine::Input::IKeyboardObserver*>(inputSystem);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true});
			inputSystemBase->Tick();
			Assert::IsTrue(gotInput);
			gotInput = false;
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = false});
			inputSystemBase->Tick();
			Assert::IsFalse(gotInput);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::W, .isDown = true});
			inputSystemBase->Tick();
			Assert::IsFalse(gotInput);
			inputSystem->UnregisterAction(handle);
			inputObserver->Observe(PonyEngine::Input::KeyboardMessage{ .keyCode = PonyEngine::Input::KeyboardKeyCode::H, .isDown = true });
			inputSystemBase->Tick();
			Assert::IsFalse(gotInput);
			inputSystemBase->End();
		}
	};
}
