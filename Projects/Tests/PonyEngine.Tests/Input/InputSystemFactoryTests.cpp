/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Core.Factory;
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

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger*) override
			{
			}
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger*) override
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
				logger{ &logger }
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

		TEST_METHOD(CreateTest)
		{
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			Assert::IsNotNull(factory.get());
		}

		TEST_METHOD(CreateSystemTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			const auto factory = PonyEngine::Input::CreateInputSystemFactory();
			const auto factoryParams = PonyEngine::Core::SystemParams{.engine = &engine};
			auto inputSystem = factory->Create(factoryParams);
			Assert::IsNotNull(inputSystem.system.get());
		}

		TEST_METHOD(GetSystemNameTest)
		{
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			Assert::AreEqual("PonyEngine::Input::InputSystem", factory->SystemName());
		}

		TEST_METHOD(GetNameTest)
		{
			auto factory = PonyEngine::Input::CreateInputSystemFactory();
			Assert::AreEqual("PonyEngine::Input::InputSystemFactory", factory->Name());
		}
	};
}