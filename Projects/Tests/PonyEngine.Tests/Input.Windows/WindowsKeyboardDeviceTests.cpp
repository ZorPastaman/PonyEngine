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
#include <optional>
#include <span>
#include <vector>

#include "PonyBase/Core/Windows/Framework.h"

import Mocks;

import PonyEngine.Input.Windows.Impl;
import PonyEngine.Window.Windows;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(WindowsKeyboardDeviceTests)
	{
		class WindowsWindowTitleBar final : public PonyEngine::Window::Windows::ITitleBar
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::string_view MainTitle() const noexcept override { return ""; }
			virtual void MainTitle(std::string_view) override {}

			[[nodiscard("Pure function")]]
			virtual std::string_view SecondaryTitle() const noexcept override { return ""; }
			virtual void SecondaryTitle(std::string_view) override {}
		};

		class MessagePump final : public PonyEngine::Window::Windows::IMessagePump
		{
		public:
			std::size_t version = 0;
			PonyEngine::Window::Windows::IMessageObserver* addedObserver;
			std::vector<UINT> observerMessageTypes;

			virtual void AddMessageObserver(PonyEngine::Window::Windows::IMessageObserver& observer, std::span<const UINT> messageTypes) override
			{
				++version;
				addedObserver = &observer;
				observerMessageTypes.assign(messageTypes.begin(), messageTypes.end());
			}

			virtual void RemoveMessageObserver(PonyEngine::Window::Windows::IMessageObserver&) noexcept override
			{
				++version;
				addedObserver = nullptr;
			}
		};

		class RawInputManager final : public PonyEngine::Window::Windows::IRawInputManager
		{
		public:
			virtual void AddRawInputObserver(PonyEngine::Window::Windows::IRawInputObserver&, std::span<const DWORD>) override {}
			virtual void RemoveRawInputObserver(PonyEngine::Window::Windows::IRawInputObserver&) noexcept override {}
		};

		class Cursor final : public PonyEngine::Window::Windows::ICursor
		{
			std::optional<PonyMath::Shape::Rect<float>> rect;

		public:
			[[nodiscard("Pure function")]]
			virtual PonyMath::Core::Vector2<std::int32_t> CursorPosition() const override { return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero; }
			virtual void CursorPosition(const PonyMath::Core::Vector2<std::int32_t>&) override {}

			[[nodiscard("Pure function")]]
			virtual bool IsVisible() const noexcept override { return false; }
			virtual void IsVisible(bool) override {}

			[[nodiscard("Pure function")]]
			virtual const std::optional<PonyMath::Shape::Rect<float>>& ClippingRect() const noexcept override { return rect; }
			virtual void ClippingRect(const std::optional<PonyMath::Shape::Rect<float>>&) override {}
		};

		class WindowsWindowSystem final : public PonyEngine::Window::Windows::IWindowSystem
		{
		public:
			WindowsWindowTitleBar titleBar;
			class MessagePump messagePump;
			class RawInputManager rawInputManager;
			class Cursor cursor;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::Windows::ITitleBar& TitleBar() noexcept override { return titleBar; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::Windows::ITitleBar& TitleBar() const noexcept override { return titleBar; }

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
			virtual PonyEngine::Window::Windows::ICursor& Cursor() noexcept override { return cursor; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::Windows::ICursor& Cursor() const noexcept override { return cursor; }

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::Windows::IMessagePump& MessagePump() noexcept override { return messagePump; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::Windows::IMessagePump& MessagePump() const noexcept override { return messagePump; }

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::Windows::IRawInputManager& RawInputManager() noexcept override { return rawInputManager; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::Windows::IRawInputManager& RawInputManager() const noexcept override { return rawInputManager; }

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
			dynamic_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::Windows::IWindowSystem), static_cast<PonyEngine::Window::Windows::IWindowSystem*>(&window));
			auto inputSystem = Mocks::InputSystem();
			inputSystem.engine = &engine;
			auto factory = PonyEngine::Input::Windows::CreateKeyboardDeviceFactory(application, PonyEngine::Input::Windows::KeyboardDeviceFactoryParams{}, PonyEngine::Input::Windows::KeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::DeviceParams{});

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
			dynamic_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::Windows::IWindowSystem), static_cast<PonyEngine::Window::Windows::IWindowSystem*>(&window));
			auto inputSystem = Mocks::InputSystem();
			inputSystem.engine = &engine;
			auto factory = PonyEngine::Input::Windows::CreateKeyboardDeviceFactory(application, PonyEngine::Input::Windows::KeyboardDeviceFactoryParams{}, PonyEngine::Input::Windows::KeyboardDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::DeviceParams{});

			device.inputDevice->Begin();

			window.messagePump.addedObserver->Observe(WM_KEYDOWN, 0, LPARAM{3014657});
			Assert::AreEqual(std::size_t{1}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::C), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().inputValue);

			window.messagePump.addedObserver->Observe(WM_KEYDOWN, 0, LPARAM{3014657 | (1 << 30)});
			Assert::AreEqual(std::size_t{1}, inputSystem.events.size());

			window.messagePump.addedObserver->Observe(WM_KEYUP, 0, LPARAM{2293761 | (1 << 30)});
			Assert::AreEqual(std::size_t{2}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::H), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().inputValue);

			window.messagePump.addedObserver->Observe(WM_SYSKEYUP, 0, LPARAM{3014657 | (1 << 30)});
			Assert::AreEqual(std::size_t{3}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::C), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().inputValue);

			window.messagePump.addedObserver->Observe(WM_SYSKEYDOWN, 0, LPARAM{2293761});
			Assert::AreEqual(std::size_t{4}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::H), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().inputValue);

			device.inputDevice->End();
		}
	};
}
