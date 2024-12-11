/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <span>
#include <vector>

#include "PonyBase/Core/Windows/Framework.h"

#include "Mocks/Engine.h"
#include "Mocks/InputSystem.h"
#include "Mocks/Logger.h"

import PonyEngine.Input.Windows.Impl;
import PonyEngine.Window.Windows;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(WindowsKeyboardDeviceTests)
	{
		class WindowsWindowSystem final : public PonyEngine::Window::IWindowsWindowSystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::string_view MainTitle() const noexcept override { return ""; }
			virtual void MainTitle(std::string_view title) override {}

			[[nodiscard("Pure function")]]
			virtual std::string_view SecondaryTitle() const noexcept override { return ""; }
			virtual void SecondaryTitle(std::string_view title) override {}

			[[nodiscard("Pure function")]]
			virtual bool IsVisible() const noexcept override { return false; }
			virtual void ShowWindow() override {}
			virtual void HideWindow() override {}

			[[nodiscard("Pure function")]]
			virtual PonyMath::Core::Vector2<std::int32_t> Position() const noexcept override { return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero; }
			[[nodiscard("Pure function")]]
			virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept override { return PonyMath::Utility::Resolution<std::uint32_t>(100u, 100u); }
			[[nodiscard("Pure function")]]
			virtual HWND WindowHandle() const noexcept override { return nullptr; }

			virtual void AddMessageObserver(PonyEngine::Window::IWindowsMessageObserver& observer, std::span<const UINT> messageTypes) override
			{
				++version;
				addedObserver = &observer;
				observerMessageTypes.assign(messageTypes.begin(), messageTypes.end());
			}

			virtual void RemoveMessageObserver(PonyEngine::Window::IWindowsMessageObserver& observer) noexcept override
			{
				++version;
				addedObserver = nullptr;
			}

			virtual void AddRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver& observer, std::span<const DWORD> rawInputTypes) override {}
			virtual void RemoveRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver& observer) noexcept override {}

			std::size_t version = 0;
			PonyEngine::Window::IWindowsMessageObserver* addedObserver;
			std::vector<UINT> observerMessageTypes;
		};

		TEST_METHOD(SubscriptionTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			auto window = WindowsWindowSystem();
			dynamic_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), static_cast<PonyEngine::Window::IWindowsWindowSystem*>(&window));
			auto inputSystem = Mocks::InputSystem();
			inputSystem.engine = &engine;
			auto factory = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory(application, PonyEngine::Input::WindowsKeyboardDeviceFactoryParams{}, PonyEngine::Input::WindowsKeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::InputDeviceParams{});

			device.inputDevice->Begin();

			Assert::AreEqual(std::size_t{1}, window.version);
			Assert::IsNotNull(window.addedObserver);
			Assert::AreEqual(std::size_t{4}, window.observerMessageTypes.size());
			Assert::AreEqual(UINT{WM_KEYDOWN}, window.observerMessageTypes[0]);
			Assert::AreEqual(UINT{WM_KEYUP}, window.observerMessageTypes[1]);
			Assert::AreEqual(UINT{WM_SYSKEYDOWN}, window.observerMessageTypes[2]);
			Assert::AreEqual(UINT{WM_SYSKEYUP}, window.observerMessageTypes[3]);

			device.inputDevice->End();

			Assert::AreEqual(std::size_t{2}, window.version);
			Assert::IsNull(window.addedObserver);
		}

		TEST_METHOD(ObserveTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			auto window = WindowsWindowSystem();
			dynamic_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), static_cast<PonyEngine::Window::IWindowsWindowSystem*>(&window));
			auto inputSystem = Mocks::InputSystem();
			inputSystem.engine = &engine;
			auto factory = PonyEngine::Input::CreateWindowsKeyboardDeviceFactory(application, PonyEngine::Input::WindowsKeyboardDeviceFactoryParams{}, PonyEngine::Input::WindowsKeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::InputDeviceParams{});

			device.inputDevice->Begin();

			window.addedObserver->Observe(WM_KEYDOWN, 0, LPARAM{3014657});
			Assert::AreEqual(std::size_t{1}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::C), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);

			window.addedObserver->Observe(WM_KEYDOWN, 0, LPARAM{3014657 | (1 << 30)});
			Assert::AreEqual(std::size_t{1}, inputSystem.events.size());

			window.addedObserver->Observe(WM_KEYUP, 0, LPARAM{2293761 | (1 << 30)});
			Assert::AreEqual(std::size_t{2}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::H), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedObserver->Observe(WM_SYSKEYUP, 0, LPARAM{3014657 | (1 << 30)});
			Assert::AreEqual(std::size_t{3}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::C), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedObserver->Observe(WM_SYSKEYDOWN, 0, LPARAM{2293761});
			Assert::AreEqual(std::size_t{4}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::H), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);

			device.inputDevice->End();
		}
	};
}
