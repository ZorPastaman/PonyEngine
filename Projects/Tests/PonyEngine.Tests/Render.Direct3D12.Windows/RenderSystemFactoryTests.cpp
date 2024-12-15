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

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"
#include "Mocks/ScreenSystem.h"

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;
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
			const auto classParams = PonyEngine::Window::WindowsClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});

			auto renderSystem = std::get<1>(system.system).get();
			Assert::IsNotNull(renderSystem);
			Assert::AreEqual(std::size_t{3}, system.publicInterfaces.Count());

			Assert::IsTrue(typeid(PonyEngine::Render::IRenderSystem) == system.publicInterfaces[0].first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)), reinterpret_cast<std::uintptr_t>(system.publicInterfaces[0].second));

			Assert::IsTrue(typeid(PonyEngine::Render::IDirect3D12RenderSystem) == system.publicInterfaces[1].first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Render::IDirect3D12RenderSystem*>(renderSystem)), reinterpret_cast<std::uintptr_t>(system.publicInterfaces[1].second));

			Assert::IsTrue(typeid(PonyEngine::Render::IWindowsDirect3D12RenderSystem) == system.publicInterfaces[2].first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(dynamic_cast<PonyEngine::Render::IWindowsDirect3D12RenderSystem*>(renderSystem)), reinterpret_cast<std::uintptr_t>(system.publicInterfaces[2].second));
		}

		TEST_METHOD(SystemTypeTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();

			Assert::IsTrue(typeid(*renderSystem) == renderFactory.systemFactory->SystemType());
		}

		TEST_METHOD(DefaultResolutionTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();

			Assert::IsTrue(static_cast<PonyMath::Core::Vector2<std::uint32_t>>(dynamic_cast<PonyEngine::Window::IWindowSystem*>(std::get<1>(window.system).get())->WindowClientRect().Size()) == static_cast<PonyMath::Core::Vector2<std::uint32_t>>(dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)->RenderTarget().Resolution()));
		}

		TEST_METHOD(CustomResolutionTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto params = PonyEngine::Render::WindowsDirect3D12RenderSystemParams{};
			params.renderTargetParams.resolution = PonyMath::Utility::Resolution<std::uint32_t>(1280u, 720u);
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, params);
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();

			Assert::IsTrue(params.renderTargetParams.resolution == dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)->RenderTarget().Resolution());
		}

		TEST_METHOD(ClearColorTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto params = PonyEngine::Render::WindowsDirect3D12RenderSystemParams{};
			params.renderTargetParams.clearColor = PonyMath::Color::RGBA<float>(0.6f, 0.7f, 0.9f, 0.956f);
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, params);
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();

			Assert::IsTrue(params.renderTargetParams.clearColor == dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)->RenderTarget().ClearColor());
		}

		TEST_METHOD(ViewMatrixTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto params = PonyEngine::Render::WindowsDirect3D12RenderSystemParams{};
			params.renderViewParams.viewMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(2.f, -6.f, 7.f), PonyMath::Core::Vector3<float>(1.f, -0.9f, -1.f), PonyMath::Core::Vector3<float>(0.8f, 0.7f, 3.f));
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, params);
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();

			Assert::IsTrue(params.renderViewParams.viewMatrix == dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)->RenderView().ViewMatrix());
		}

		TEST_METHOD(ProjectionMatrixTest)
		{
			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto params = PonyEngine::Render::WindowsDirect3D12RenderSystemParams{};
			params.renderViewParams.projectionMatrix = PonyMath::Core::PerspectiveMatrix(55.f, 1.67f, 1.f, 1000.f);
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, params);
			auto system = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto renderSystem = std::get<1>(system.system).get();

			Assert::IsTrue(params.renderViewParams.projectionMatrix == dynamic_cast<PonyEngine::Render::IRenderSystem*>(renderSystem)->RenderView().ProjectionMatrix());
		}
	};
}
