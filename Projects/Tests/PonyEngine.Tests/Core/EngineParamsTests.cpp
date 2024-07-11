/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstdint>;
import <exception>;

import PonyEngine.Core;
import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.Window;
import PonyEngine.Window.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineParamsTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Log(PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override { }
			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override { }

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger*) override { }
			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger*) override { }
		};

		class EmptyWindow final : public PonyEngine::Window::IWindow
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			[[nodiscard("Pure function")]]
			virtual const wchar_t* GetTitle() const noexcept override
			{
				return L"";
			}
			virtual void SetTitle(const wchar_t*) override
			{
			}

			virtual void AddKeyboardMessageObserver(PonyEngine::Window::IKeyboardObserver*) override
			{
			}
			virtual void RemoveKeyboardMessageObserver(PonyEngine::Window::IKeyboardObserver*) override
			{
			}

			virtual void ShowWindow() override
			{
			}

			virtual void Tick() override
			{
			}
		};

		class EmptyWindowFactory final : public PonyEngine::Window::IWindowFactory
		{
		public:
			PonyEngine::Window::IWindow* createdWindow = nullptr;

			[[nodiscard("Pure function")]]
			virtual const char* GetWindowName() const noexcept override
			{
				return "";
			}

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
			virtual const wchar_t* GetTitle() const noexcept override
			{
				return L"";
			}
			virtual void SetTitle(const wchar_t*) noexcept override
			{
			}
		};

		class EmptySystem final : public PonyEngine::Core::ISystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Begin() override
			{
			}
			virtual void End() override
			{
			}

			virtual bool IsTickable() const noexcept override
			{
				return true;
			}
			virtual void Tick() override
			{
			}
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
			virtual const char* GetSystemName() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(ContructorTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams engineParams(&logger);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Log::ILogger*>(&logger)), reinterpret_cast<std::uintptr_t>(&engineParams.GetLogger()));
		}

		TEST_METHOD(GetWindowFactoryTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams engineParams(&logger);
			EmptyWindowFactory windowFactory;
			engineParams.SetWindowFactory(&windowFactory);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Window::IWindowFactory*>(&windowFactory)), reinterpret_cast<std::uintptr_t>(engineParams.GetWindowFactory()));
		}

		TEST_METHOD(GetSystemFactoriesTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams engineParams(&logger);
			EmptySystemFactory factory0;
			EmptySystemFactory factory1;
			EmptySystemFactory factory2;
			engineParams.AddSystemFactory(&factory0);
			engineParams.AddSystemFactory(&factory1);
			engineParams.AddSystemFactory(&factory2);

			PonyEngine::Core::EngineParams::SystemFactoriesIterator it = engineParams.GetSystemFactories();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemFactory*>(&factory0)), reinterpret_cast<std::uintptr_t>(*it));
			Assert::IsFalse(it.IsEnd());
			PonyEngine::Core::EngineParams::SystemFactoriesIterator incrementedIt = ++it;
			Assert::IsTrue(incrementedIt == it);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemFactory*>(&factory1)), reinterpret_cast<std::uintptr_t>(*it));
			Assert::IsFalse(it.IsEnd());
			PonyEngine::Core::EngineParams::SystemFactoriesIterator postIncrementedIt = it++;
			Assert::IsTrue(incrementedIt == postIncrementedIt);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemFactory*>(&factory2)), reinterpret_cast<std::uintptr_t>(*it));
			Assert::IsFalse(it.IsEnd());
			Assert::IsTrue((++it).IsEnd());
		}
	};
}
