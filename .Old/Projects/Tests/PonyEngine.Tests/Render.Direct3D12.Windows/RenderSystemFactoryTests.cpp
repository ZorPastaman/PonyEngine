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
#include <cstdint>
#include <memory>
#include <variant>

import Mocks;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Utility;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows.Impl;
import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Render
{
	TEST_CLASS(RenderSystemFactoryTests)
	{
		TEST_METHOD(CreateTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto windowFactory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)});
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::Windows::IWindowSystem), dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::Direct3D12::Windows::CreateRenderSystemFactory(application, PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryParams{}, PonyEngine::Render::Direct3D12::Windows::RenderSystemParams{});
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});

			auto renderSystem = std::get<1>(system.system).get();
			Assert::IsNotNull(renderSystem);
			Assert::AreEqual(std::size_t{3}, system.publicInterfaces.Count());

			Assert::IsTrue(typeid(PonyEngine::Render::IRenderSystem) == system.publicInterfaces[0].first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)), reinterpret_cast<std::uintptr_t>(system.publicInterfaces[0].second));

			Assert::IsTrue(typeid(PonyEngine::Render::Direct3D12::IRenderSystem) == system.publicInterfaces[1].first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Render::Direct3D12::IRenderSystem*>(renderSystem)), reinterpret_cast<std::uintptr_t>(system.publicInterfaces[1].second));

			Assert::IsTrue(typeid(PonyEngine::Render::Direct3D12::Windows::IRenderSystem) == system.publicInterfaces[2].first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Render::Direct3D12::Windows::IRenderSystem*>(renderSystem)), reinterpret_cast<std::uintptr_t>(system.publicInterfaces[2].second));
		}

		TEST_METHOD(SystemInfoTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::Windows::ClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto windowFactory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, PonyEngine::Window::Windows::WindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass)});
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::Windows::IWindowSystem), dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::Direct3D12::Windows::CreateRenderSystemFactory(application, PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryParams{}, PonyEngine::Render::Direct3D12::Windows::RenderSystemParams{});
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();
			const PonyEngine::Core::ISystemInfo& info = renderFactory.systemFactory->SystemInfo();
			Assert::IsTrue(typeid(*renderSystem) == info.SystemType());
			Assert::IsTrue(info.IsTickable());
			Assert::AreEqual(std::size_t{3}, info.InterfaceCount());
		}
	};
}
