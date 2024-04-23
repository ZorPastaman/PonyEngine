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
import <cstdint>;
import <functional>;
import <exception>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Core.Implementation;
import PonyEngine.Debug.Log;
import PonyEngine.Window;
import PonyEngine.Window.Factories;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineTests)
	{
		class EmptyLogger final : public PonyEngine::Debug::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Log(PonyEngine::Debug::Log::LogType, const PonyEngine::Debug::Log::LogInput&) noexcept override { }
			virtual void LogException(const std::exception&, const PonyEngine::Debug::Log::LogInput&) noexcept override { }

			virtual void AddSubLogger(PonyEngine::Debug::Log::ISubLogger*) override { }
			virtual void RemoveSubLogger(PonyEngine::Debug::Log::ISubLogger*) override { }
		};

		class EmptyWindow final : public PonyEngine::Window::IWindow
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			[[nodiscard("Pure function")]]
			virtual const wchar_t* GetTitle() const noexcept override { return L""; }
			virtual void SetTitle(const wchar_t*) override { }

			virtual void AddKeyboardMessageObserver(PonyEngine::Window::IKeyboardObserver*) override { }
			virtual void RemoveKeyboardMessageObserver(PonyEngine::Window::IKeyboardObserver*) override { }

			virtual void ShowWindow() override { }

			virtual void Tick() override { }
		};

		class EmptyWindowFactory final : public PonyEngine::Window::IWindowFactory
		{
		public:
			PonyEngine::Window::IWindow* createdWindow = nullptr;

			[[nodiscard("Pure function")]]
			virtual const char* GetWindowName() const noexcept override { return ""; }

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindow* Create(PonyEngine::Core::IEngine&) override
			{
				createdWindow = new EmptyWindow();
				return createdWindow;
			}
			virtual void Destroy(PonyEngine::Window::IWindow* const window) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptyWindow*>(window));
				delete static_cast<EmptyWindow*>(window);
			}

			[[nodiscard("Pure function")]]
			virtual const wchar_t* GetTitle() const noexcept override { return L""; }
			virtual void SetTitle(const wchar_t*) noexcept override { }
		};

		class EmptySystem final : public PonyEngine::Core::ISystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Begin() override { }
			virtual void End() override { }

			virtual bool IsTickable() const noexcept override { return true; }
			virtual void Tick() override { }
		};

		class EmptySystemFactory final : public PonyEngine::Core::ISystemFactory
		{
		public:
			PonyEngine::Core::ISystem* createdSystem = nullptr;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystem* Create(PonyEngine::Core::IEngine&) override
			{
				createdSystem = new EmptySystem();
				return createdSystem;
			}
			virtual void Destroy(PonyEngine::Core::ISystem* const system) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptySystem*>(system));
				delete static_cast<EmptySystem*>(system);
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetSystemName() const noexcept override { return ""; }
		};

		TEST_METHOD(CreateTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams params(&logger);
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsNotNull(engine);
			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(GetFrameCountTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams params(&logger);
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(params);
			
			for (std::size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, engine->GetFrameCount());
				engine->Tick();
				Assert::AreEqual(i + 1, engine->GetFrameCount());
			}

			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(GetLoggerTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams params(&logger);
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&logger), reinterpret_cast<std::uintptr_t>(&(engine->GetLogger())));
			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(GetWindowTest)
		{
			EmptyLogger logger;
			EmptyWindowFactory windowFactory;
			PonyEngine::Core::EngineParams params(&logger);
			params.SetWindowFactory(&windowFactory);
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(windowFactory.createdWindow), reinterpret_cast<std::uintptr_t>(engine->GetWindow()));
			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(FindSystemTest)
		{
			EmptyLogger logger;
			EmptySystemFactory systemFactory;
			PonyEngine::Core::EngineParams params(&logger);
			params.AddSystemFactory(&systemFactory);
			PonyEngine::Core::IEngine* const engine = PonyEngine::Core::CreateEngine(params);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine->FindSystem([](const PonyEngine::Core::ISystem* const system) { return dynamic_cast<const EmptySystem*>(system) != nullptr; })));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(systemFactory.createdSystem), reinterpret_cast<std::uintptr_t>(engine->FindSystem<EmptySystem>()));
			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(ExitTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams params(&logger);
			PonyEngine::Core::IEngine* engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsTrue(engine->IsRunning());
			engine->Stop();
			Assert::IsFalse(engine->IsRunning());
			Assert::AreEqual(0, engine->GetExitCode());
			PonyEngine::Core::DestroyEngine(engine);
			engine = PonyEngine::Core::CreateEngine(params);
			engine->Stop(100);
			Assert::AreEqual(100, engine->GetExitCode());
			PonyEngine::Core::DestroyEngine(engine);
		}
	};
}
