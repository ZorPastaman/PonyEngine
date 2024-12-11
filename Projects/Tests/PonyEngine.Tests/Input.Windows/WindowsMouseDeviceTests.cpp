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
		class WindowsWindowSystem final : public PonyEngine::Window::IWindowsWindowSystem
		{
		public:
			[[nodiscard("Pure function")]]
			virtual std::string_view MainTitle() const noexcept override
			{
				return "";
			}
			virtual void MainTitle(std::string_view title) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual std::string_view SecondaryTitle() const noexcept override
			{
				return "";
			}
			virtual void SecondaryTitle(std::string_view title) override
			{
			}

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
			virtual PonyMath::Core::Vector2<std::int32_t> Position() const noexcept override
			{
				return PonyMath::Core::Vector2<std::int32_t>::Predefined::Zero;
			}
			[[nodiscard("Pure function")]]
			virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept override
			{
				return PonyMath::Utility::Resolution<std::uint32_t>(100u, 100u);
			}
			[[nodiscard("Pure function")]]
			virtual HWND WindowHandle() const noexcept override
			{
				return nullptr;
			}

			virtual void AddMessageObserver(PonyEngine::Window::IWindowsMessageObserver& observer, std::span<const UINT> messageTypes) override
			{
				++version;
				addedMessageObserver = &observer;
				observerMessageTypes.assign(messageTypes.begin(), messageTypes.end());
			}

			virtual void RemoveMessageObserver(PonyEngine::Window::IWindowsMessageObserver& observer) noexcept override
			{
				++version;
				addedMessageObserver = nullptr;
			}

			virtual void AddRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver& observer, std::span<const DWORD> rawInputTypes) override
			{
				++version;
				addedRawObserver = &observer;
				observerRawTypes.assign(rawInputTypes.begin(), rawInputTypes.end());
			}

			virtual void RemoveRawInputObserver(PonyEngine::Window::IWindowsRawInputObserver& observer) noexcept override
			{
				++version;
				addedRawObserver = nullptr;
			}

			std::size_t version = 0;
			PonyEngine::Window::IWindowsMessageObserver* addedMessageObserver;
			std::vector<UINT> observerMessageTypes;
			PonyEngine::Window::IWindowsRawInputObserver* addedRawObserver;
			std::vector<DWORD> observerRawTypes;
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

			Assert::AreEqual(std::size_t{2}, window.version);
			Assert::IsNotNull(window.addedMessageObserver);
			Assert::AreEqual(std::size_t{10}, window.observerMessageTypes.size());
			Assert::AreEqual(UINT{WM_MOUSEMOVE}, window.observerMessageTypes[0]);
			Assert::AreEqual(UINT{WM_LBUTTONDOWN}, window.observerMessageTypes[1]);
			Assert::AreEqual(UINT{WM_LBUTTONUP}, window.observerMessageTypes[2]);
			Assert::AreEqual(UINT{WM_RBUTTONDOWN}, window.observerMessageTypes[3]);
			Assert::AreEqual(UINT{WM_RBUTTONUP}, window.observerMessageTypes[4]);
			Assert::AreEqual(UINT{WM_MBUTTONDOWN}, window.observerMessageTypes[5]);
			Assert::AreEqual(UINT{WM_MBUTTONUP}, window.observerMessageTypes[6]);
			Assert::AreEqual(UINT{WM_XBUTTONDOWN}, window.observerMessageTypes[7]);
			Assert::AreEqual(UINT{WM_XBUTTONUP}, window.observerMessageTypes[8]);
			Assert::AreEqual(UINT{WM_MOUSEWHEEL}, window.observerMessageTypes[9]);
			Assert::IsNotNull(window.addedRawObserver);
			Assert::AreEqual(DWORD{RIM_TYPEMOUSE}, window.observerRawTypes[0]);

			device.inputDevice->End();

			Assert::AreEqual(std::size_t{4}, window.version);
			Assert::IsNull(window.addedMessageObserver);
			Assert::IsNull(window.addedRawObserver);
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

			window.addedMessageObserver->Observe(WM_MOUSEMOVE, 0, LPARAM{DWORD{32} + (DWORD{46} << 16)});
			Assert::AreEqual(std::size_t{2}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseXPosition), static_cast<std::uint32_t>(inputSystem.events[0].inputCode));
			Assert::AreEqual(32.f, inputSystem.events[0].value);
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseYPosition), static_cast<std::uint32_t>(inputSystem.events[1].inputCode));
			Assert::AreEqual(46.f, inputSystem.events[1].value);

			window.addedMessageObserver->Observe(WM_LBUTTONDOWN, 0, 0);
			Assert::AreEqual(std::size_t{3}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseLeftButton), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);
			window.addedMessageObserver->Observe(WM_LBUTTONUP, 0, 0);
			Assert::AreEqual(std::size_t{4}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseLeftButton), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedMessageObserver->Observe(WM_RBUTTONDOWN, 0, 0);
			Assert::AreEqual(std::size_t{5}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseRightButton), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);
			window.addedMessageObserver->Observe(WM_RBUTTONUP, 0, 0);
			Assert::AreEqual(std::size_t{6}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseRightButton), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedMessageObserver->Observe(WM_MBUTTONDOWN, 0, 0);
			Assert::AreEqual(std::size_t{7}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseMiddleButton), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);
			window.addedMessageObserver->Observe(WM_MBUTTONUP, 0, 0);
			Assert::AreEqual(std::size_t{8}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseMiddleButton), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedMessageObserver->Observe(WM_XBUTTONDOWN, 1 << 16, 0);
			Assert::AreEqual(std::size_t{9}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton4), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);
			window.addedMessageObserver->Observe(WM_XBUTTONUP, 1 << 16, 0);
			Assert::AreEqual(std::size_t{10}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton4), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedMessageObserver->Observe(WM_XBUTTONDOWN, 2 << 16, 0);
			Assert::AreEqual(std::size_t{11}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton5), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);
			window.addedMessageObserver->Observe(WM_XBUTTONUP, 2 << 16, 0);
			Assert::AreEqual(std::size_t{12}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseButton5), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(0.f, inputSystem.events.back().value);

			window.addedMessageObserver->Observe(WM_MOUSEWHEEL, 120 << 16, 0);
			Assert::AreEqual(std::size_t{13}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseWheel), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(1.f, inputSystem.events.back().value);
			window.addedMessageObserver->Observe(WM_MOUSEWHEEL, -240 << 16, 0);
			Assert::AreEqual(std::size_t{14}, inputSystem.events.size());
			Assert::AreEqual(static_cast<std::uint32_t>(PonyEngine::Input::InputCode::MouseWheel), static_cast<std::uint32_t>(inputSystem.events.back().inputCode));
			Assert::AreEqual(-2.f, inputSystem.events.back().value);

			device.inputDevice->End();
		}
	};
}