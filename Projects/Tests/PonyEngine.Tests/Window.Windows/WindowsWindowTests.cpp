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
import PonyEngine.Input;
import PonyEngine.Log;
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

		class EmptyTimeManager : public PonyEngine::Core::ITimeManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::size_t FrameCount() const noexcept override
			{
				return 0;
			}

			[[nodiscard("Pure function")]]
			virtual float TargetFrameTime() const noexcept override
			{
				return 0.f;
			}

			virtual void TargetFrameTime(float) noexcept override
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
				logger{&logger}
			{
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& Logger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ITimeManager& TimeManager() const noexcept override
			{
				return timeManager;
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

		TEST_METHOD(GetInterfacesTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			auto interfaces = window->PublicInterfaces();

			auto it = interfaces.Interfaces();
			auto windowInterface = *it;
			Assert::IsTrue(windowInterface.first.get() == typeid(PonyEngine::Window::IWindow));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Window::IWindow*>(window.get())), reinterpret_cast<std::uintptr_t>(windowInterface.second));

			++it;
			windowInterface = *it;
			Assert::IsTrue(windowInterface.first.get() == typeid(PonyEngine::Window::IWindowsWindow));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get())), reinterpret_cast<std::uintptr_t>(windowInterface.second));

			++it;
			windowInterface = *it;
			Assert::IsTrue(windowInterface.first.get() == typeid(PonyEngine::Input::IKeyboardProvider));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IKeyboardProvider*>(window.get())), reinterpret_cast<std::uintptr_t>(windowInterface.second));
		}

		TEST_METHOD(GetIsTickableTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			Assert::IsTrue(window->IsTickable());
		}

		TEST_METHOD(GetSetTitleTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			const wchar_t* title = L"Test title";
			windowsWindow->Title(title);
			wchar_t gotTitle[64];
			GetWindowTextW(windowsWindow->WindowHandle(), gotTitle, 64);
			Assert::AreEqual(title, gotTitle);
			Assert::AreEqual(title, windowsWindow->Title());
		}

		TEST_METHOD(GetNameTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			Assert::AreEqual("PonyEngine::Window::WindowsWindow", windowsWindow->Name());
		}

		TEST_METHOD(ShowHideWindowTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			windowsWindow->ShowWindow();
			Assert::IsTrue(IsWindowVisible(windowsWindow->WindowHandle()));
			Assert::IsTrue(windowsWindow->IsVisible());
			windowsWindow->HideWindow();
			Assert::IsFalse(IsWindowVisible(windowsWindow->WindowHandle()));
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
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			Assert::AreEqual(title.c_str(), windowsWindow->Title());
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
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			RECT rect;
			GetWindowRect(windowsWindow->WindowHandle(), &rect);
			Assert::AreEqual(64L, rect.left);
			Assert::AreEqual(32L, rect.top);
			Assert::AreEqual(64L + 320L, rect.right);
			Assert::AreEqual(32L + 240L, rect.bottom);
		}

		TEST_METHOD(DestroyMessageTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			PostMessageW(windowsWindow->WindowHandle(), WM_DESTROY, 0, 0);
			window->Tick();
			Assert::AreEqual(0, engine.stopCode);
		}

		TEST_METHOD(InputMessageTest)
		{
			auto logger = EmptyLogger();
			auto engine = EmptyEngine(logger);
			auto classParams = PonyEngine::Window::WindowsClassParams();
			classParams.name = L"Pony Engine Test";
			auto factory = PonyEngine::Window::CreateWindowsWindowFactory(logger, classParams);
			auto window = factory->Create(engine);
			auto windowsWindow = dynamic_cast<PonyEngine::Window::IWindowsWindow*>(window.get());
			auto keyboardObserver = KeyboardObserver();
			auto keyboardProvider = dynamic_cast<PonyEngine::Input::IKeyboardProvider*>(window.get());
			keyboardProvider->AddKeyboardObserver(&keyboardObserver);
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYDOWN, 0, LPARAM{1310721});
			window->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::T, .isDown = true});
			PostMessageW(windowsWindow->WindowHandle(), WM_KEYUP, 0, LPARAM{3080193});
			window->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::V, .isDown = false});
			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYDOWN, 0, LPARAM{540540929});
			window->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::LeftAlt, .isDown = true});
			PostMessageW(windowsWindow->WindowHandle(), WM_SYSKEYUP, 0, LPARAM{557318145});
			window->Tick();
			Assert::IsTrue(keyboardObserver.lastMessage == PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::RightAlt, .isDown = false});
		}
	};
}
