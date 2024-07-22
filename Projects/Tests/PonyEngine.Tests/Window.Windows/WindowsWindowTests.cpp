/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "PonyEngine/Platform/Windows/Framework.h"

import PonyEngine.Core;
import PonyEngine.Log;
import PonyEngine.Window;
import PonyEngine.Window.Factory;
import PonyEngine.Window.Windows;
import PonyEngine.Window.Windows.Factory;
import PonyEngine.Window.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowTests)
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

			virtual void SetTargetFrameTime(float frameTime) noexcept override
			{
			}
		};

		class EmptySystemManager : public PonyEngine::Core::ISystemManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override
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
				logger{&logger}
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
			virtual bool IsRunning() const noexcept override
			{
				return true;
			}

			[[nodiscard("Pure function")]]
			virtual int GetExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int exitCode) noexcept override
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
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			Assert::IsNotNull(window.get());
		}

		TEST_METHOD(IsWindowAliveTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			Assert::IsTrue(windowsWindow->IsWindowAlive());
			window->Tick();
			Assert::IsTrue(windowsWindow->IsWindowAlive());
			PostMessage(windowsWindow->GetWindowHandle(), WM_DESTROY, 0, 0);
			window->Tick();
			Assert::IsFalse(windowsWindow->IsWindowAlive());
		}

		TEST_METHOD(GetSetTitleTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			const wchar_t* title = L"Test title";
			windowsWindow->SetTitle(title);
			wchar_t gotTitle[64];
			GetWindowText(windowsWindow->GetWindowHandle(), gotTitle, 64);
			Assert::AreEqual(title, gotTitle);
			Assert::AreEqual(title, windowsWindow->GetTitle());
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			Assert::AreEqual("PonyEngine::Window::WindowsWindow", windowsWindow->GetName());
		}

		TEST_METHOD(ShowHideWindowTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			windowsWindow->ShowWindow();
			Assert::IsTrue(IsWindowVisible(windowsWindow->GetWindowHandle()));
			Assert::IsTrue(windowsWindow->IsVisible());
			windowsWindow->HideWindow();
			Assert::IsFalse(IsWindowVisible(windowsWindow->GetWindowHandle()));
			Assert::IsFalse(windowsWindow->IsVisible());
		}

		TEST_METHOD(CreateTitleTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			std::wstring title = L"Test title";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			factory->NextWindowParams().title = title;
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			Assert::AreEqual(title.c_str(), windowsWindow->GetTitle());
		}

		TEST_METHOD(WindowRectTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto& params = factory->NextWindowParams();
			params.horizontalPosition = 64;
			params.verticalPosition = 32;
			params.width = 320;
			params.height = 240;
			auto windowInfo = factory->Create(engine);
			auto window = std::move(windowInfo.System());
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			RECT rect;
			GetWindowRect(windowsWindow->GetWindowHandle(), &rect);
			Assert::AreEqual(64L, rect.left);
			Assert::AreEqual(32L, rect.top);
			Assert::AreEqual(64L + 320L, rect.right);
			Assert::AreEqual(32L + 240L, rect.bottom);
		}
	};
}
