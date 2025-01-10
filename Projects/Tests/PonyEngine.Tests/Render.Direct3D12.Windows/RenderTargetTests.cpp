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

import PonyMath.Color;
import PonyMath.Core;

import PonyEngine.Render.Direct3D12.Windows.Impl;
import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Render
{
	TEST_CLASS(RenderTargetTests)
	{
		TEST_METHOD(ClearColorTest)
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
			auto windowFactory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, PonyEngine::Window::Windows::WindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::Windows::IWindowSystem), dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::Direct3D12::Windows::CreateRenderSystemFactory(application, PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryParams{}, PonyEngine::Render::Direct3D12::Windows::RenderSystemParams{});
			auto renderSystem = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto& renderTarget = dynamic_cast<PonyEngine::Render::IRenderSystem*>(std::get<1>(renderSystem.system).get())->RenderTarget();

			auto expectedColor = PonyMath::Color::RGBA<float>(0.2f, 0.95f, 0.7f, 0.98f);
			renderTarget.ClearColor(expectedColor);
			Assert::IsTrue(expectedColor == renderTarget.ClearColor());
		}
	};
}
