/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "Platform/Windows/Framework.h"

import <cstddef>;
import <type_traits>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Core.Implementation;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Window;
import PonyEngine.Window.Windows;
import PonyEngine.Window.Windows.Factories;
import PonyEngine.Window.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsWindowTests)
	{
		class TestKeyboardObserver final : public PonyEngine::Window::IKeyboardObserver
		{
		public:
			PonyEngine::Window::KeyboardKeyCode expectedKeyCode;
			bool expectedDown;
			bool expectedMessages;
			std::size_t count = 0;

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Observe(const PonyEngine::Window::KeyboardMessage& keyboardMessage) override
			{
				Assert::IsTrue(expectedMessages);
				Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(expectedKeyCode), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(keyboardMessage.GetKeyCode()));
				Assert::AreEqual(expectedDown, keyboardMessage.GetIsDown());
				++count;
			}
		};

		TEST_METHOD(CreateTest)
		{
			PonyEngine::Debug::Log::ILogger* const logger = PonyEngine::Debug::Log::CreateLogger();
			const PonyEngine::Window::WindowClassParams windowParams(L"Params");
			PonyEngine::Window::IWindowsWindowFactory* const factory = PonyEngine::Window::CreateWindowsWindowFactory(*logger, windowParams);
			PonyEngine::Core::EngineParams engineParams(*logger);
			engineParams.windowFactory = factory;
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(engineParams);

			Assert::IsNotNull(engine->GetWindow());

			PonyEngine::Core::DestroyEngine(engine);
			PonyEngine::Window::DestroyWindowsWindowFactory(factory);
			PonyEngine::Debug::Log::DestroyLogger(logger);
		}

		TEST_METHOD(TitleTest)
		{
			const wchar_t* const windowTitle = L"Title";
			PonyEngine::Debug::Log::ILogger* const logger = PonyEngine::Debug::Log::CreateLogger();
			const PonyEngine::Window::WindowClassParams windowParams(L"Params");
			PonyEngine::Window::IWindowsWindowFactory* const factory = PonyEngine::Window::CreateWindowsWindowFactory(*logger, windowParams);
			factory->SetTitle(windowTitle);
			Assert::AreEqual(windowTitle, factory->GetTitle().c_str());
			PonyEngine::Core::EngineParams engineParams(*logger);
			engineParams.windowFactory = factory;
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(engineParams);

			Assert::AreEqual(windowTitle, engine->GetWindow()->GetTitle().c_str());

			const wchar_t* const anotherWindowTitle = L"New Title";
			engine->GetWindow()->SetTitle(anotherWindowTitle);
			Assert::AreEqual(anotherWindowTitle, engine->GetWindow()->GetTitle().c_str());

			PonyEngine::Core::DestroyEngine(engine);
			PonyEngine::Window::DestroyWindowsWindowFactory(factory);
			PonyEngine::Debug::Log::DestroyLogger(logger);
		}

		TEST_METHOD(KeyboardMessageObserverTest)
		{
			PonyEngine::Debug::Log::ILogger* const logger = PonyEngine::Debug::Log::CreateLogger();
			const PonyEngine::Window::WindowClassParams windowParams(L"Params");
			PonyEngine::Window::IWindowsWindowFactory* const factory = PonyEngine::Window::CreateWindowsWindowFactory(*logger, windowParams);
			PonyEngine::Core::EngineParams engineParams(*logger);
			engineParams.windowFactory = factory;
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(engineParams);
			TestKeyboardObserver observer;

			observer.expectedKeyCode = PonyEngine::Window::KeyboardKeyCode::F;
			observer.expectedDown = true;
			observer.expectedMessages = true;
			engine->GetWindow()->AddKeyboardMessageObserver(&observer);
			PostMessage(static_cast<PonyEngine::Window::IWindowsWindow*>(engine->GetWindow())->GetWindowHandle(), WM_KEYDOWN, static_cast<WPARAM>('F'), 0);
			engine->Tick();
			Assert::AreEqual(std::size_t{1}, observer.count);

			observer.expectedKeyCode = PonyEngine::Window::KeyboardKeyCode::H;
			observer.expectedDown = false;
			PostMessage(static_cast<PonyEngine::Window::IWindowsWindow*>(engine->GetWindow())->GetWindowHandle(), WM_KEYUP, static_cast<WPARAM>('H'), 0);
			engine->Tick();
			Assert::AreEqual(std::size_t{2}, observer.count);

			observer.expectedKeyCode = PonyEngine::Window::KeyboardKeyCode::Enter;
			observer.expectedDown = true;
			PostMessage(static_cast<PonyEngine::Window::IWindowsWindow*>(engine->GetWindow())->GetWindowHandle(), WM_KEYDOWN, static_cast<WPARAM>(13), 0);
			engine->Tick();
			Assert::AreEqual(std::size_t{3}, observer.count);

			observer.expectedKeyCode = PonyEngine::Window::KeyboardKeyCode::Enter;
			observer.expectedDown = false;
			PostMessage(static_cast<PonyEngine::Window::IWindowsWindow*>(engine->GetWindow())->GetWindowHandle(), WM_KEYUP, static_cast<WPARAM>(13), 0);
			engine->Tick();
			Assert::AreEqual(std::size_t{4}, observer.count);

			engine->GetWindow()->RemoveKeyboardMessageObserver(&observer);
			observer.expectedMessages = false;
			PostMessage(static_cast<PonyEngine::Window::IWindowsWindow*>(engine->GetWindow())->GetWindowHandle(), WM_KEYUP, static_cast<WPARAM>(13), 0);
			engine->Tick();
			Assert::AreEqual(std::size_t{ 4 }, observer.count);

			PonyEngine::Core::DestroyEngine(engine);
			PonyEngine::Window::DestroyWindowsWindowFactory(factory);
			PonyEngine::Debug::Log::DestroyLogger(logger);
		}
	};
}
