/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <memory>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"
#include "Mocks/ScreenSystem.h"

import PonyMath.Core;

import PonyEngine.Render.Direct3D12.Windows.Impl;
import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Render
{
	TEST_CLASS(RenderViewTests)
	{
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
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			auto renderSystem = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto& renderView = dynamic_cast<PonyEngine::Render::IRenderSystem*>(std::get<1>(renderSystem.system).get())->RenderView();

			auto expectedViewMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-3.f, -6.f, 7.f), PonyMath::Core::Vector3<float>(4.f, -1.f, 9.f), PonyMath::Core::Vector3<float>(1.f, 1.5f, 0.7f));
			renderView.ViewMatrix(expectedViewMatrix);
			Assert::IsTrue(expectedViewMatrix == renderView.ViewMatrix());
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
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			auto renderSystem = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto& renderView = dynamic_cast<PonyEngine::Render::IRenderSystem*>(std::get<1>(renderSystem.system).get())->RenderView();

			auto expectedProjectionMatrix = PonyMath::Core::PerspectiveMatrix(50.f, 1.75f, 0.5f, 1100.5f);
			renderView.ProjectionMatrix(expectedProjectionMatrix);
			Assert::IsTrue(expectedProjectionMatrix == renderView.ProjectionMatrix());
		}
	};
}
