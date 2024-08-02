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
import PonyEngine.Log;
import PonyEngine.Window.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowFactoryTests)
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
			int stopCode = 123;

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

			virtual void Stop(const int exitCode) noexcept override
			{
				stopCode = exitCode;
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
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			Assert::IsNotNull(window.get());
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			Assert::AreEqual("PonyEngine::Window::WindowsWindowFactory", factory->GetName());
		}

		TEST_METHOD(GetSystemName)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			Assert::AreEqual("PonyEngine::Window::WindowsWindow", factory->GetSystemName());
		}
	};
}
