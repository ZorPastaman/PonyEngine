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
	TEST_CLASS(WindowsMouseDeviceTests)
	{
		class WindowsWindowTitleBar final : public PonyEngine::Window::IWindowsWindowTitleBar
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::string_view MainTitle() const noexcept override
			{
				return "";
			}
			virtual void MainTitle(std::string_view) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual std::string_view SecondaryTitle() const noexcept override
			{
				return "";
			}
			virtual void SecondaryTitle(std::string_view) override
			{
			}
		};

		class MessagePump final : public PonyEngine::Window::IWindowsMessagePump
		{
		public:
			std::size_t version = 0;
			PonyEngine::Window::IWindowsMessageObserver* addedMessageObserver;
			std::vector<UINT> observerMessageTypes;

			virtual void AddMessageObserver(PonyEngine::Window::IWindowsMessageObserver& observer, std::span<const UINT> messageTypes) override
			{
				++version;
				addedMessageObserver = &observer;
				observerMessageTypes.assign(messageTypes.begin(), messageTypes.end());
			}

			virtual void RemoveMessageObserver(PonyEngine::Window::IWindowsMessageObserver&) noexcept override
			{
				++version;
				addedMessageObserver = nullptr;
			}
		};

		class RawInputManager final : public PonyEngine::Window::IWindowsRawInputManager
		{
		public:
			std::size_t version = 0;
			PonyEngine::Window::IWindowsRawInputObserver* addedRawObserver;
			std::vector<DWORD> observerRawTypes;

			virtual void AddRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver& observer, std::span<const DWORD> rawInputTypes) override
			{
				++version;
				addedRawObserver = &observer;
				observerRawTypes.assign(rawInputTypes.begin(), rawInputTypes.end());
			}

			virtual void RemoveRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver&) noexcept override
			{
				++version;
				addedRawObserver = nullptr;
			}
		};

		class Cursor final : public PonyEngine::Window::IWindowsCursor
		{
		public:
			[[nodiscard("Pure function")]]
			virtual PonyMath::Core::Vector2<std::int32_t> CursorPosition() const override
			{
				return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero;
			}
			virtual void CursorPosition(const PonyMath::Core::Vector2<std::int32_t>&) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual bool IsVisible() const noexcept override
			{
				return false;
			}
			virtual void IsVisible(bool) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual std::optional<PonyMath::Shape::Rect<float>> ClippingRect() const noexcept override { return std::nullopt; }
			virtual void ClippingRect(const std::optional<PonyMath::Shape::Rect<float>>&) override {}
		};

		class WindowsWindowSystem final : public PonyEngine::Window::IWindowsWindowSystem
		{
		public:
			WindowsWindowTitleBar titleBar;
			class MessagePump messagePump;
			class RawInputManager rawInputManager;
			class Cursor cursor;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsWindowTitleBar& TitleBar() noexcept override
			{
				return titleBar;
			}

			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsWindowTitleBar& TitleBar() const noexcept override
			{
				return titleBar;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsCursor& Cursor() noexcept override { return cursor; }
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsCursor& Cursor() const noexcept override { return cursor; }

			[[nodiscard("Pure function")]]
			virtual bool IsVisible() const noexcept override
			{
				return false;
			}
			virtual void ShowWindow() override
			{
			}
			virtual void HideWindow() override
			{
			}

			[[nodiscard("Pure function")]]
			virtual HWND WindowHandle() const noexcept override
			{
				return nullptr;
			}

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
			virtual PonyEngine::Window::IWindowsMessagePump& MessagePump() noexcept override
			{
				return messagePump;
			}
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsMessagePump& MessagePump() const noexcept override
			{
				return messagePump;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Window::IWindowsRawInputManager& RawInputManager() noexcept override
			{
				return rawInputManager;
			}
			[[nodiscard("Pure function")]]
			virtual const PonyEngine::Window::IWindowsRawInputManager& RawInputManager() const noexcept override
			{
				return rawInputManager;
			}

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
			auto factory = PonyEngine::Input::CreateWindowsMouseDeviceFactory(application, PonyEngine::Input::WindowsMouseDeviceFactoryParams{}, PonyEngine::Input::WindowsMouseDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::InputDeviceParams{});

			device.inputDevice->Begin();

			Assert::AreEqual(std::size_t{1}, window.messagePump.version);
			Assert::IsNotNull(window.messagePump.addedMessageObserver);
			Assert::AreEqual(std::size_t{10}, window.messagePump.observerMessageTypes.size());
			Assert::AreEqual(UINT{WM_MOUSEMOVE}, window.messagePump.observerMessageTypes[0]);
			Assert::AreEqual(UINT{WM_LBUTTONDOWN}, window.messagePump.observerMessageTypes[1]);
			Assert::AreEqual(UINT{WM_LBUTTONUP}, window.messagePump.observerMessageTypes[2]);
			Assert::AreEqual(UINT{WM_RBUTTONDOWN}, window.messagePump.observerMessageTypes[3]);
			Assert::AreEqual(UINT{WM_RBUTTONUP}, window.messagePump.observerMessageTypes[4]);
			Assert::AreEqual(UINT{WM_MBUTTONDOWN}, window.messagePump.observerMessageTypes[5]);
			Assert::AreEqual(UINT{WM_MBUTTONUP}, window.messagePump.observerMessageTypes[6]);
			Assert::AreEqual(UINT{WM_XBUTTONDOWN}, window.messagePump.observerMessageTypes[7]);
			Assert::AreEqual(UINT{WM_XBUTTONUP}, window.messagePump.observerMessageTypes[8]);
			Assert::AreEqual(UINT{WM_MOUSEWHEEL}, window.messagePump.observerMessageTypes[9]);
			Assert::AreEqual(std::size_t{1}, window.rawInputManager.version);
			Assert::IsNotNull(window.rawInputManager.addedRawObserver);
			Assert::AreEqual(DWORD{RIM_TYPEMOUSE}, window.rawInputManager.observerRawTypes[0]);

			device.inputDevice->End();

			Assert::AreEqual(std::size_t{2}, window.messagePump.version);
			Assert::IsNull(window.messagePump.addedMessageObserver);
			Assert::AreEqual(std::size_t{ 2 }, window.rawInputManager.version);
			Assert::IsNull(window.rawInputManager.addedRawObserver);
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
			auto factory = PonyEngine::Input::CreateWindowsMouseDeviceFactory(application, PonyEngine::Input::WindowsMouseDeviceFactoryParams{}, PonyEngine::Input::WindowsMouseDeviceParams{});
			auto device = factory.inputDeviceFactory->CreateDevice(inputSystem, PonyEngine::Input::InputDeviceParams{});

			device.inputDevice->Begin();

			window.messagePump.addedMessageObserver->Observe(WM_MOUSEMOVE, 0, LPARAM{DWORD{32} + (DWORD{46} << 16)});
			Assert::AreEqual(std::size_t{2}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events[0].first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseXPosition), static_cast<std::uint32_t>(inputSystem.events[0].second.inputCode));
			Assert::AreEqual(32.f, inputSystem.events[0].second.inputValue);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events[1].first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseYPosition), static_cast<std::uint32_t>(inputSystem.events[1].second.inputCode));
			Assert::AreEqual(46.f, inputSystem.events[1].second.inputValue);

			window.messagePump.addedMessageObserver->Observe(WM_LBUTTONDOWN, 0, 0);
			Assert::AreEqual(std::size_t{3}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseLeftButton), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().second.inputValue);
			window.messagePump.addedMessageObserver->Observe(WM_LBUTTONUP, 0, 0);
			Assert::AreEqual(std::size_t{4}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseLeftButton), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().second.inputValue);

			window.messagePump.addedMessageObserver->Observe(WM_RBUTTONDOWN, 0, 0);
			Assert::AreEqual(std::size_t{5}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseRightButton), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().second.inputValue);
			window.messagePump.addedMessageObserver->Observe(WM_RBUTTONUP, 0, 0);
			Assert::AreEqual(std::size_t{6}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseRightButton), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().second.inputValue);

			window.messagePump.addedMessageObserver->Observe(WM_MBUTTONDOWN, 0, 0);
			Assert::AreEqual(std::size_t{7}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseMiddleButton), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().second.inputValue);
			window.messagePump.addedMessageObserver->Observe(WM_MBUTTONUP, 0, 0);
			Assert::AreEqual(std::size_t{8}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseMiddleButton), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().second.inputValue);

			window.messagePump.addedMessageObserver->Observe(WM_XBUTTONDOWN, 1 << 16, 0);
			Assert::AreEqual(std::size_t{9}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton4), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().second.inputValue);
			window.messagePump.addedMessageObserver->Observe(WM_XBUTTONUP, 1 << 16, 0);
			Assert::AreEqual(std::size_t{10}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton4), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().second.inputValue);

			window.messagePump.addedMessageObserver->Observe(WM_XBUTTONDOWN, 2 << 16, 0);
			Assert::AreEqual(std::size_t{11}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton5), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().second.inputValue);
			window.messagePump.addedMessageObserver->Observe(WM_XBUTTONUP, 2 << 16, 0);
			Assert::AreEqual(std::size_t{12}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton5), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().second.inputValue);

			window.messagePump.addedMessageObserver->Observe(WM_MOUSEWHEEL, 120 << 16, 0);
			Assert::AreEqual(std::size_t{13}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseWheel), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().second.inputValue);
			window.messagePump.addedMessageObserver->Observe(WM_MOUSEWHEEL, static_cast<WPARAM>(-240 << 16), 0);
			Assert::AreEqual(std::size_t{14}, inputSystem.events.size());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Input::IInputDevice*>(device.inputDevice.get())), reinterpret_cast<std::uintptr_t>(inputSystem.events.back().first));
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseWheel), static_cast<std::uint32_t>(inputSystem.events.back().second.inputCode));
			Assert::AreEqual(-2.f, inputSystem.events.back().second.inputValue);

			device.inputDevice->End();
		}
	};
}