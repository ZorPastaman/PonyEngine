/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "PonyBase/Core/Windows/Framework.h"

#include <cstddef>
#include <exception>
#include <string>
#include <typeinfo>

import PonyMath.Core;

import PonyDebug.Log;

import PonyEngine.Core.Factory;
import PonyEngine.Input;
import PonyEngine.Screen;
import PonyEngine.Window.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowTests)
	{
		class Application : public PonyEngine::Core::IApplication
		{
		public:
			PonyDebug::Log::ILogger* logger;

			[[nodiscard("Pure function")]]
			virtual PonyDebug::Log::ILogger& Logger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class EmptyLogger final : public PonyDebug::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Log(PonyDebug::Log::LogType, const PonyDebug::Log::LogInput&) noexcept override
			{
			}
			virtual void LogException(const std::exception&, const PonyDebug::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyDebug::Log::ISubLogger&) override
			{
			}
			virtual void RemoveSubLogger(PonyDebug::Log::ISubLogger&) override
			{
			}
		};

		class EmptySystemManager : public PonyEngine::Core::ISystemManager
		{
		public:
			PonyEngine::Screen::IScreenSystem* screenSystem = nullptr;

			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override
			{
				return typeInfo == typeid(PonyEngine::Screen::IScreenSystem) ? screenSystem : nullptr;
			}
		};

		class EmptyEngine : public PonyEngine::Core::IEngine, public PonyEngine::Core::ITickableEngine
		{
			EmptyLogger* logger;

		public:
			mutable EmptySystemManager systemManager;

			int stopCode = 123;

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
			virtual PonyDebug::Log::ILogger& Logger() const noexcept override
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

			virtual void Stop(const int exitCode) noexcept override
			{
				stopCode = exitCode;
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

		class KeyboardObserver final : public PonyEngine::Input::IKeyboardObserver
		{
		public:
			PonyEngine::Input::KeyboardMessage lastMessage;

			virtual void Observe(const PonyEngine::Input::KeyboardMessage& keyboardMessage) override
			{
				lastMessage = keyboardMessage;
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class ScreenSystem final : public PonyEngine::Screen::IScreenSystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual PonyEngine::Screen::Resolution<unsigned int> DisplayResolution() const noexcept override
			{
				return PonyEngine::Screen::Resolution<unsigned int>(static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN)), static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN)));
			}
		};

		TEST_METHOD(GetSetTitleTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			window.system->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			const wchar_t* title = L"Test title";
			windowsWindow->MainTitle(title);
			wchar_t gotTitle[64];
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(title, gotTitle);
			Assert::AreEqual(title, windowsWindow->MainTitle());
			window.system->End();
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			Assert::AreEqual("PonyEngine::Window::WindowsWindowSystem", windowsWindow->Name());
		}

		TEST_METHOD(ShowHideWindowTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			window.system->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			windowsWindow->ShowWindow();
			Assert::IsTrue(IsWindowVisible(windowsWindow->WindowHandle()));
			Assert::IsTrue(windowsWindow->IsVisible());
			windowsWindow->HideWindow();
			Assert::IsFalse(IsWindowVisible(windowsWindow->WindowHandle()));
			Assert::IsFalse(windowsWindow->IsVisible());
			window.system->End();
		}

		TEST_METHOD(CreateTitleTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			std::wstring title = L"Test title";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			auto windowParams = PonyEngine::Window::WindowsWindowParams();
			windowParams.title = title;
			factory.windowSystemFactory->WindowSystemParams().title = title;
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			Assert::AreEqual(title.c_str(), windowsWindow->MainTitle());
		}

		TEST_METHOD(WindowRectTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			window.system->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			RECT rect;
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(0L, rect.left);
			Assert::AreEqual(0L, rect.top);
			Assert::AreEqual(static_cast<LONG>(GetSystemMetrics(SM_CXSCREEN)), rect.right);
			Assert::AreEqual(static_cast<LONG>(GetSystemMetrics(SM_CYSCREEN)), rect.bottom);
			window.system->End();
		}

		TEST_METHOD(DestroyMessageTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			window.system->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			PostMessageW(windowsWindow->WindowHandle(), WM_DESTROY, 0, 0);
			window.tickableSystem->Tick();
			Assert::AreEqual(0, engine.stopCode);
			window.system->End();
		}

		TEST_METHOD(InputMessageTest)
		{
			auto logger = EmptyLogger();
			auto screenSystem = ScreenSystem();
			auto application = Application();
			application.logger = &logger;
			auto engine = EmptyEngine(logger);
			engine.systemManager.screenSystem = &screenSystem;
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{.windowsClassParams = classParams});
			const auto systemParams = PonyEngine::Core::SystemParams();
			auto window = factory.systemFactory->Create(engine, systemParams);
			window.system->Begin();
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(window.system.get());
			auto keyboardObserver = KeyboardObserver();
			auto keyboardProvider = dynamic_cast<PonyEngine::Input::IKeyboardProvider*>(window.system.get());
			keyboardProvider->AddKeyboardObserver(keyboardObserver);
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYDOWN, 0, LPARAM{1310721});
			window.tickableSystem->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::T, .isDown = true});
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYUP, 0, LPARAM{3080193});
			window.tickableSystem->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::V, .isDown = false});
			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYDOWN, 0, LPARAM{540540929});
			window.tickableSystem->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::LeftAlt, .isDown = true});
			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYUP, 0, LPARAM{557318145});
			window.tickableSystem->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::RightAlt, .isDown = false});
			window.system->End();
		}
	};
}
