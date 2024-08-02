/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"


import PonyEngine.Core;
import PonyEngine.Input.Implementation;
import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputSystemFactoryTests)
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

		class EmptyEngine : public PonyEngine::Core::IAdvancedEngine
		{
		public:
			EmptyLogger* logger;
			mutable EmptyTimeManager timeManager;
			mutable EmptySystemManager systemManager;

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

		TEST_METHOD(CreateTest)
		{
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			Assert::IsNotNull(factory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			auto inputSystem = factory->Create(engine);
			Assert::IsNotNull(inputSystem.get());
		}

		TEST_METHOD(GetSystemNameTest)
		{
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			Assert::AreEqual("PonyEngine::Input::InputSystem", factory->GetSystemName());
		}

		TEST_METHOD(GetNameTest)
		{
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			Assert::AreEqual("PonyEngine::Input::InputSystemFactory", factory->GetName());
		}
	};
}