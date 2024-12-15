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
		class WindowsWindowTitleBar final : public PonyEngine::Window::IWindowsWindowTitleBar
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::string_view MainTitle() const noexcept override { return ""; }
			virtual void MainTitle(std::string_view) override {}

			[[nodiscard("Pure function")]]
			virtual std::string_view SecondaryTitle() const noexcept override { return ""; }
			virtual void SecondaryTitle(std::string_view) override {}
		};

		class MessagePump final : public PonyEngine::Window::IWindowsMessagePump
		{
		public:
			std::size_t version = 0;
			PonyEngine::Window::IWindowsMessageObserver* addedObserver;
			std::vector<UINT> observerMessageTypes;

			virtual void AddMessageObserver(PonyEngine::Window::IWindowsMessageObserver& observer, std::span<const UINT> messageTypes) override
			{
				++version;
				addedObserver = &observer;
				observerMessageTypes.assign(messageTypes.begin(), messageTypes.end());
			}

			virtual void RemoveMessageObserver(PonyEngine::Window::IWindowsMessageObserver&) noexcept override
			{
				++version;
				addedObserver = nullptr;
			}
		};

		class RawInputManager final : public PonyEngine::Window::IWindowsRawInputManager
		{
		public:
			virtual void AddRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver&, std::span<const DWORD>) override {}
			virtual void RemoveRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver&) noexcept override {}
		};

		class Cursor final : public PonyEngine::Window::IWindowsCursor
		{
		public:
			[[nodiscard("Pure function")]]
			virtual PonyMath::Core::Vector2<std::int32_t> CursorPosition() const override { return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero; }
			virtual void CursorPosition(const PonyMath::Core::Vector2<std::int32_t>&) override {}

			[[nodiscard("Pure function")]]
			virtual bool IsVisible() const noexcept override { return false; }
			virtual void IsVisible(bool) override {}

			[[nodiscard("Pure function")]]
			virtual std::optional<PonyMath::Shape::Rect<float>> ClippingRect() const override { return std::nullopt; }
			virtual void ClippingRect(const std::optional<PonyMath::Shape::Rect<float>>& clippingRect) override {}
		};

		class WindowsWindowSystem final : public PonyEngine::Window::IWindowsWindowSystem
		{
		public:
			WindowsWindowTitleBar titleBar;
			class MessagePump messagePump;
			class RawInputManager rawInputManager;
			class Cursor cursor;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsWindowTitleBar& TitleBar() noexcept override { return titleBar; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsWindowTitleBar& TitleBar() const noexcept override { return titleBar; }

			[[nodiscard("Pure function")]]
			virtual bool IsVisible() const noexcept override { return false; }
			virtual void ShowWindow() override {}
			virtual void HideWindow() override {}

			[[nodiscard("Pure function")]]
			virtual PonyMath::Shape::Rect<std::int32_t> WindowRect() const noexcept override
			{
				return PonyMath::Shape::Rect<std::int32_t>(PonyMath::Core::Vector2<std::int32_t>(10, 10), PonyMath::Core::Vector2<std::int32_t>(100, 100));
			}
			[[nodiscard("Pure function")]]
			virtual PonyMath::Shape::Rect<std::int32_t> WindowClientRect() const noexcept override
			{
				return PonyMath::Shape::Rect<std::int32_t>(PonyMath::Core::Vector2<std::int32_t>(10, 10), PonyMath::Core::Vector2<std::int32_t>(100, 100));
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsCursor& Cursor() noexcept override { return cursor; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsCursor& Cursor() const noexcept override { return cursor; }

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsMessagePump& MessagePump() noexcept override { return messagePump; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsMessagePump& MessagePump() const noexcept override { return messagePump; }

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsRawInputManager& RawInputManager() noexcept override { return rawInputManager; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsRawInputManager& RawInputManager() const noexcept override { return rawInputManager; }

			[[nodiscard("Pure function")]]
			virtual HWND WindowHandle() const noexcept override { return nullptr; }

			[[nodiscard("Pure function")]]
			virtual PonyMath::Core::Vector2<std::int32_t> ClientToScreen(const PonyMath::Core::Vector2<std::int32_t>&) const override { return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero; }
			[[nodiscard("Pure function")]]
			virtual PonyMath::Core::Vector2<std::int32_t> ScreenToClient(const PonyMath::Core::Vector2<std::int32_t>&) const override { return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero; }
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

			Assert::AreEqual(std::size_t{1}, window.messagePump.version);
			Assert::IsNotNull(window.messagePump.addedObserver);
			Assert::AreEqual(std::size_t{4}, window.messagePump.observerMessageTypes.size());
			Assert::AreEqual(UINT{WM_KEYDOWN}, window.messagePump.observerMessageTypes[0]);
			Assert::AreEqual(UINT{WM_KEYUP}, window.messagePump.observerMessageTypes[1]);
			Assert::AreEqual(UINT{WM_SYSKEYDOWN}, window.messagePump.observerMessageTypes[2]);
			Assert::AreEqual(UINT{WM_SYSKEYUP}, window.messagePump.observerMessageTypes[3]);

			device.inputDevice->End();

			Assert::AreEqual(std::size_t{2}, window.messagePump.version);
			Assert::IsNull(window.messagePump.addedObserver);
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

			window.messagePump.addedObserver->Observe(WM_KEYDOWN, 0, LPARAM{3014657});
			Assert::AreEqual(std::size_t{1}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::C), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);

			window.messagePump.addedObserver->Observe(WM_KEYDOWN, 0, LPARAM{3014657 | (1 << 30)});
			Assert::AreEqual(std::size_t{1}, inputSystem.events.size());

			window.messagePump.addedObserver->Observe(WM_KEYUP, 0, LPARAM{2293761 | (1 << 30)});
			Assert::AreEqual(std::size_t{2}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::H), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.messagePump.addedObserver->Observe(WM_SYSKEYUP, 0, LPARAM{3014657 | (1 << 30)});
			Assert::AreEqual(std::size_t{3}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::C), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.messagePump.addedObserver->Observe(WM_SYSKEYDOWN, 0, LPARAM{2293761});
			Assert::AreEqual(std::size_t{4}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::H), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);

			device.inputDevice->End();
		}
	};
}
